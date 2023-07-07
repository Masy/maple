//
// Created by masy on 07.07.2023.
//

#include "maple/events/WindowStateEvent.hpp"

using namespace maple::events;

WindowStateEvent::WindowStateEvent(const WINDOW_STATE prevState, const WINDOW_STATE newState)
		: Event(), m_prevState(prevState), m_newState(newState) {}

WINDOW_STATE WindowStateEvent::prevState() const {
	return m_prevState;
}

WINDOW_STATE WindowStateEvent::newState() const {
	return m_newState;
}
