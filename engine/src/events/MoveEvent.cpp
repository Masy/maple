//
// Created by masy on 07.07.2023.
//

#include "maple/events/MoveEvent.hpp"

using namespace maple::events;

MoveEvent::MoveEvent(const int offsetX, const int offsetY) : Event(), m_offsetX(offsetX), m_offsetY(offsetY) {}

int MoveEvent::offsetX() const {
	return m_offsetX;
}

int MoveEvent::offsetY() const {
	return m_offsetY;
}
