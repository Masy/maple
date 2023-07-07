//
// Created by masy on 19.06.2023.
//

#pragma once

#include <map>
#include <typeindex>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <windows.h>

namespace maple::widgets {
	class Widget;
}

namespace maple::events {

	/**
	 * Struct to extract the type of the second argument of a function.
	 *
	 * This is used for event handlers to get the type of the event that is handled by the function.
	 */
	template <typename>
	struct extractSecondArgument;

	/**
	 * Extracts the type of the second argument of a function.
	 *
	 * @tparam A The type of the functions return value.
	 * @tparam B The type of the functions first parameter.
	 * @tparam C The type of the functions second parameter.
	 */
	template <typename A, typename B, typename C>
	struct extractSecondArgument<A (*)(B, C)> {
		using type = std::remove_reference_t<C>::element_type;
	};

	/**
	 * Extracts the type of the second argument of a std::function.
	 *
	 * @tparam A The type of the std::function's return value.
	 * @tparam B The type of the std::function's first parameter.
	 * @tparam C The type of the std::function's second parameter.
	 */
	template <typename A, typename B, typename C>
	struct extractSecondArgument<std::function<A(B, C)>> {
		using type = std::remove_reference_t<C>::element_type;
	};

	/**
	 * Extracts the type of the second argument of a lambda function.
	 *
	 * @tparam T The type of the lambda function.
	 */
	template <typename T>
	struct extractSecondArgument {
		/**
		 * Extracts the type of the second argument of a constant lambda function.
		 *
		 * @tparam P The type of the captured arguments.
		 * @tparam A The type of the lambda's return value.
		 * @tparam B The type of the lambda's first parameter.
		 * @tparam C The type of the lambda's second parameter.
		 * @param op The captured arguments.
		 * @return a reference to the second parameter of the lambda.
		 */
		template <typename P, typename A, typename B, typename C>
		static C& extractSecondArgumentFromLambda(A (P::* op)(B, C) const);

		/**
		 * Extracts the type of the second argument of a lambda function.
		 *
		 * @tparam P The type of the captured arguments.
		 * @tparam A The type of the lambda's return value.
		 * @tparam B The type of the lambda's first parameter.
		 * @tparam C The type of the lambda's second parameter.
		 * @param op The captured arguments.
		 * @return a reference to the second parameter of the lambda.
		 */
		template <typename P, typename A, typename B, typename C>
		static C& extractSecondArgumentFromLambda(A (P::* op)(B, C));

		using type = std::remove_reference_t<decltype(extractSecondArgumentFromLambda(&T::operator()))>::element_type;
	};

	/**
	 * Type declaration for the type of an extracted second argument of a function.
	 */
	template <typename T>
	using extractSecondArgument_t = typename extractSecondArgument<T>::type;


	class Event : public std::enable_shared_from_this<Event> {
	public:

		typedef std::multimap<std::type_index, std::function<void(widgets::Widget *, const std::shared_ptr<events::Event> &)>> handlerMultiMap_t;


		virtual ~Event() = default;

		void emit(widgets::Widget *widget);

		void emitAsync(widgets::Widget *widget);

		[[nodiscard]] bool cancelled() const;

		void cancelled(bool cancelled);

	public:

		static std::unordered_map<widgets::Widget*, handlerMultiMap_t> eventHandlers;

	private:

		bool m_cancelled = false;
	};

	struct WinEvent {
		std::shared_ptr<Event> event;
		maple::widgets::Widget *widget = nullptr;
		std::pair<Event::handlerMultiMap_t::iterator, Event::handlerMultiMap_t::iterator> handlers;
		std::condition_variable *cv = nullptr;
		bool *finished = nullptr;
	};

	template<typename Widget_t, typename F>
	void connect(Widget_t *widget, F func) {
		static_assert(std::derived_from<Widget_t, maple::widgets::Widget>, "Widget_t must be derived from the widget class");
		static_assert(std::derived_from<extractSecondArgument_t<F>, maple::events::Event>, "Event type of handler must be derived from the event class");

		auto wrapper = [=] (widgets::Widget *widget, const std::shared_ptr<events::Event> &event) {
			func(reinterpret_cast<Widget_t*>(widget), std::reinterpret_pointer_cast<extractSecondArgument_t<F>>(event));
		};
		Event::eventHandlers[(widgets::Widget*) widget].insert({std::type_index(typeid(extractSecondArgument_t<F>)), wrapper});
	}

	template<typename Widget_t, typename Event_t>
	void connect(Widget_t *widget, void (Widget_t::*func)(const std::shared_ptr<Event_t> &)) {
		static_assert(std::derived_from<Widget_t, maple::widgets::Widget>, "Widget_t must be derived from the widget class");
		static_assert(std::derived_from<Event_t, maple::events::Event>, "Event_t must be derived from the event class");

		auto wrapper = [=] (widgets::Widget *widget, const std::shared_ptr<events::Event> &event) {
			(reinterpret_cast<Widget_t*>(widget)->*func)(std::reinterpret_pointer_cast<Event_t>(event));
		};
		Event::eventHandlers[(widgets::Widget*) widget].insert({std::type_index(typeid(Event_t)), wrapper});
	}

	void disconnect(widgets::Widget *widget);

}