//
// Created by masy on 01.07.2023.
//

#include "maple/events/MouseEvent.hpp"

using namespace maple::events;

MouseEvent::MouseEvent(const int x, const int y, const uint32_t mouseButton, const uint32_t modifiers, const KEY_STATE keyState)
	: m_cursorX(x), m_cursorY(y), m_mouseButton(mouseButton), m_modifiers(modifiers), m_keyState(keyState) {
}

int MouseEvent::cursorX() const {
	return m_cursorX;
}

int MouseEvent::cursorY() const {
	return m_cursorY;
}

uint32_t MouseEvent::mouseButton() const {
	return m_mouseButton;
}

uint32_t MouseEvent::modifiers() const {
	return m_modifiers;
}

KEY_STATE MouseEvent::keyState() const {
	return m_keyState;
}