//
// Created by masy on 07.07.2023.
//

#include "maple/events/FocusEvent.hpp"

using namespace maple::events;

FocusEvent::FocusEvent(const bool focused) : Event(), m_focused(focused) {}

bool FocusEvent::focused() const {
	return m_focused;
}
