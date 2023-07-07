//
// Created by masy on 07.07.2023.
//

#include "maple/events/InteractStateEvent.hpp"

using namespace maple::events;

InteractStateEvent::InteractStateEvent(const INTERACT_STATE prevState, const INTERACT_STATE newState)
		: Event(), m_prevState(prevState), m_newState(newState) {}

INTERACT_STATE InteractStateEvent::prevState() const {
	return m_prevState;
}

INTERACT_STATE InteractStateEvent::newState() const {
	return m_newState;
}
