//
// Created by masy on 07.07.2023.
//

#include "maple/events/KeyEvent.hpp"

using namespace maple::events;

KeyEvent::KeyEvent(uint32_t keyCode, uint32_t modifiers, KEY_STATE state)
		: Event(), m_keyCode(keyCode), m_modifiers(modifiers), m_keyState(state) {}

uint32_t KeyEvent::keyCode() const {
	return m_keyCode;
}

uint32_t KeyEvent::modifiers() const {
	return m_modifiers;
}

KEY_STATE KeyEvent::keyState() const {
	return m_keyState;
}
