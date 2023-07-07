//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class CharEvent : public Event {
	public:

		CharEvent(uint32_t codePoint);

		[[nodiscard]] uint32_t codepoint() const;

	private:

		uint32_t m_codepoint;

	};

}
