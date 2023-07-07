//
// Created by masy on 01.07.2023.
//


#pragma once

#include "maple/events/Event.hpp"
#include "maple/Maple.hpp"

namespace maple::events {

	class MouseEvent : public Event {
	public:

		MouseEvent(int cursorX, int cursorY, uint32_t mouseButton, uint32_t modifiers, KEY_STATE state);

		[[nodiscard]] int cursorX() const;

		[[nodiscard]] int cursorY() const;

		[[nodiscard]] uint32_t mouseButton() const;

		[[nodiscard]] uint32_t modifiers() const;

		[[nodiscard]] KEY_STATE keyState() const;

	private:

		int m_cursorX;
		int m_cursorY;
		uint32_t m_mouseButton;
		uint32_t m_modifiers;
		KEY_STATE m_keyState;

	};

}
