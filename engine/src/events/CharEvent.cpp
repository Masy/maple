//
// Created by masy on 04.07.2023.
//

#include "maple/events/CharEvent.hpp"

using namespace maple::events;

CharEvent::CharEvent(const uint32_t codePoint) : Event(), m_codepoint(codePoint) {}

uint32_t CharEvent::codepoint() const {
	return m_codepoint;
}

