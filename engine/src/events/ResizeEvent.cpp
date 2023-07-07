//
// Created by masy on 07.07.2023.
//

#include "maple/events/ResizeEvent.hpp"

using namespace maple::events;

ResizeEvent::ResizeEvent(const int deltaWidth, const int deltaHeight)
		: Event(), m_deltaWidth(deltaWidth), m_deltaHeight(deltaHeight) {}

int ResizeEvent::deltaWidth() const {
	return m_deltaWidth;
}

int ResizeEvent::deltaHeight() const {
	return m_deltaHeight;
}
