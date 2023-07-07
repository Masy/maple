//
// Created by masy on 19.06.2023.
//

#pragma once

#include <limits>
#include <map>
#include <typeindex>
#include <functional>
#include "maple/events/Event.hpp"
#include "maple/events/MouseEvent.hpp"


namespace maple::widgets {

	class Window;

	class Widget {
	public:

		static Widget *HOVERED_WIDGET;

	public:

		virtual ~Widget() noexcept;

		[[nodiscard]] Window *window();

		[[nodiscard]] int x() const;

		[[nodiscard]] int y() const;

		void position(int posX, int posY);

		[[nodiscard]] int width() const;

		[[nodiscard]] int height() const;

		void resize(int width, int height);

		[[nodiscard]] bool visible() const;

		virtual void visible(bool visible);

		inline void show() {
			visible(true);
		}

		inline void hide() {
			visible(false);
		}

		[[nodiscard]] bool focused() const;

		virtual void focused(bool focused);

		[[nodiscard]] INTERACT_STATE interactState() const;

		void interactState(INTERACT_STATE newState);

		virtual void onMouseEvent(const std::shared_ptr<events::MouseEvent> &event);

	protected:

		Widget();

	protected:

		Window *m_window = nullptr;
		Widget *m_parent = nullptr;
		int m_posX = 0;
		int m_posY = 0;
		int m_width = 80;
		int m_height = 24;
		int m_minWidth = -1;
		int m_minHeight = -1;
		int m_maxWidth = (std::numeric_limits<int>::max)();
		int m_maxHeight = (std::numeric_limits<int>::max)();
		bool m_visible = true;
		int m_tabIndex = 0;
		bool m_focused = false;
		INTERACT_STATE m_interactState = MAPLE_INTERACT_DEFAULT;

	};

}
