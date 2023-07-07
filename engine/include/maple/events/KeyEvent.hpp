//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"
#include "maple/Maple.hpp"

namespace maple::events {

	class KeyEvent : public Event {
	public:

		KeyEvent(uint32_t keyCode, uint32_t modifiers, KEY_STATE state);

		[[nodiscard]] uint32_t keyCode() const;

		[[nodiscard]] uint32_t modifiers() const;

		[[nodiscard]] KEY_STATE keyState() const;

	private:

		uint32_t m_keyCode;
		uint32_t m_modifiers;
		KEY_STATE m_keyState;

	};

}
