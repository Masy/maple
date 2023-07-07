//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class MouseHoverEvent : public Event {
	public:

		MouseHoverEvent(int cursorX, int cursorY);

		[[nodiscard]] int cursorX() const;

		[[nodiscard]] int cursorY() const;

	private:

		int m_cursorX;
		int m_cursorY;

	};

}
