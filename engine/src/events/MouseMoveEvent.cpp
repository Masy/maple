
//
// Created by masy on 07.07.2023.
//

#include "maple/events/MouseMoveEvent.hpp"

using namespace maple::events;

MouseMoveEvent::MouseMoveEvent(const int cursorX, const int cursorY) : Event(), m_cursorX(cursorX), m_cursorY(cursorY) {}

int MouseMoveEvent::cursorX() const {
	return m_cursorX;
}

int MouseMoveEvent::cursorY() const {
	return m_cursorY;
}
