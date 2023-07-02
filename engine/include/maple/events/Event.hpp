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

		class Worker {
		public:

			Worker();

			~Worker() noexcept;

			void push_back(const std::function<void()> &wrapper);

			[[nodiscard]] std::thread::id threadId();

		private:

			std::thread m_thread;
			std::mutex m_mutex;
			std::condition_variable m_cv{};
			std::queue<std::function<void()>> m_eventQueue{};
			bool m_working = true;

		};

	public:

		virtual ~Event() = default;

		void emit(widgets::Widget *widget);

		void emitAsync(widgets::Widget *widget);

		[[nodiscard]] bool cancelled() const;

		void cancelled(bool cancelled);

	private:

		static std::unordered_map<widgets::Widget*, std::multimap<std::type_index, std::function<void(widgets::Widget *, const std::shared_ptr<events::Event> &)>>> eventHandlers;

	private:

		bool m_cancelled = false;

		template<typename F>
		friend void connect(widgets::Widget *, F);

		template<typename EventType>
		friend void connect(widgets::Widget *, void (maple::widgets::Widget::*func)(const std::shared_ptr<EventType> &));

		friend void disconnect(widgets::Widget *widget);
	};

	template <typename F>
	void connect(widgets::Widget *widget, F eventHandler) {
		auto wrapper = [=] (widgets::Widget *widget, const std::shared_ptr<events::Event> &event) {
			eventHandler(widget, std::reinterpret_pointer_cast<extractSecondArgument_t<F>>(event));
		};
		Event::eventHandlers[widget].insert({std::type_index(typeid(extractSecondArgument_t<F>)), wrapper});
	}

	template<typename EventType>
	void connect(widgets::Widget *widget, void (maple::widgets::Widget::*func)(const std::shared_ptr<EventType> &)) {
		auto wrapper = [=] (widgets::Widget *widget, const std::shared_ptr<events::Event> &event) {
			(widget->*func)(std::reinterpret_pointer_cast<EventType>(event));
		};
		Event::eventHandlers[widget].insert({std::type_index(typeid(EventType)), wrapper});
	}

	void disconnect(widgets::Widget *widget);

}