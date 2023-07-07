//
// Created by masy on 07.07.2023.
//

#include "maple/events/MouseHoverEvent.hpp"

using namespace maple::events;

MouseHoverEvent::MouseHoverEvent(const int cursorX, const int cursorY) : Event(), m_cursorX(cursorX), m_cursorY(cursorY) {}


int MouseHoverEvent::cursorX() const {
	return m_cursorX;
}

int MouseHoverEvent::cursorY() const {
	return m_cursorY;
}