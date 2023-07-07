//
// Created by masy on 07.07.2023.
//

#include "maple/events/ScrollEvent.hpp"

using namespace maple::events;

ScrollEvent::ScrollEvent(const int cursorX, const int cursorY, const int offsetX, const int offsetY, const uint32_t modifiers)
		: Event(), m_cursorX(cursorX), m_cursorY(cursorY), m_offsetX(offsetX), m_offsetY(offsetY), m_modifiers(modifiers) {}


int ScrollEvent::cursorX() const {
	return m_cursorX;
}

int ScrollEvent::cursorY() const {
	return m_cursorY;
}

int ScrollEvent::offsetX() const {
	return m_offsetX;
}

int ScrollEvent::offsetY() const {
	return m_offsetY;
}

uint32_t ScrollEvent::modifiers() const {
	return m_modifiers;
}