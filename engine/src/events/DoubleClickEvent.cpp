//
// Created by masy on 06.07.2023.
//

#include "maple/events/DoubleClickEvent.hpp"

using namespace maple::events;

DoubleClickEvent::DoubleClickEvent(const int cursorX, const int cursorY, const uint32_t mouseButton, const uint32_t modifiers)
		: Event(), m_cursorX(cursorX), m_cursorY(cursorY), m_mouseButton(mouseButton), m_modifiers(modifiers) {}

int DoubleClickEvent::cursorX() const {
	return m_cursorX;
}

int DoubleClickEvent::cursorY() const {
	return m_cursorY;
}

uint32_t DoubleClickEvent::mouseButton() const {
	return m_mouseButton;
}

uint32_t DoubleClickEvent::modifiers() const {
	return m_modifiers;
}
