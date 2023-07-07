//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class FocusEvent : public Event {
	public:

		FocusEvent(bool focused);

		[[nodiscard]] bool focused() const;

	private:

		bool m_focused;

	};

}
