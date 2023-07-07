//
// Created by masy on 06.07.2023.
//

#include "maple/events/ContentScaleEvent.hpp"

using namespace maple::events;

ContentScaleEvent::ContentScaleEvent(const float prevScale, const float newScale)
		: Event(), m_prevScale(prevScale), m_newScale(newScale) {}

float ContentScaleEvent::prevScale() const {
	return m_prevScale;
}

float ContentScaleEvent::newScale() const {
	return m_newScale;
}