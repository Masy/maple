//
// Created by masy on 01.07.2023.
//

#include "maple/events/MouseEvent.hpp"

using namespace maple::events;

MouseEvent::MouseEvent(const int x, const int y, const uint32_t mouseButton, const uint32_t modifier, const bool doubleClicked)
	: m_posX(x), m_posY(y), m_mouseButton(mouseButton), m_modifier(modifier), m_doubleClicked(doubleClicked) {
}

int MouseEvent::x() const {
	return m_posX;
}

int MouseEvent::y() const {
	return m_posY;
}

uint32_t MouseEvent::mouseButton() const {
	return m_mouseButton;
}

uint32_t MouseEvent::modifier() const {
	return m_modifier;
}

bool MouseEvent::doubleClicked() const {
	return m_doubleClicked;
}