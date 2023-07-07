//
// Created by masy on 03.07.2023.
//

#include "maple/events/ActivationEvent.hpp"

using namespace maple::events;

ActivationEvent::ActivationEvent(const bool activated, widgets::Window *otherWindow)
		: Event(), m_activated(activated), m_otherWindow(otherWindow) {}

bool ActivationEvent::activated() const {
	return m_activated;
}

maple::widgets::Window *ActivationEvent::otherWindow() const {
	return m_otherWindow;
}
