//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class DoubleClickEvent : public Event {
	public:

		DoubleClickEvent(int cursorX, int cursorY, uint32_t mouseButton, uint32_t modifiers);

		[[nodiscard]] int cursorX() const;

		[[nodiscard]] int cursorY() const;

		[[nodiscard]] uint32_t mouseButton() const;

		[[nodiscard]] uint32_t modifiers() const;

	private:

		int m_cursorX;
		int m_cursorY;
		uint32_t m_mouseButton;
		uint32_t m_modifiers;

	};

}
