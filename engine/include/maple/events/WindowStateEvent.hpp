//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"
#include "maple/Maple.hpp"

namespace maple::events {

	class WindowStateEvent : public Event {
	public:

		WindowStateEvent(WINDOW_STATE prevState, WINDOW_STATE newState);

		[[nodiscard]] WINDOW_STATE prevState() const;

		[[nodiscard]] WINDOW_STATE newState() const;

	private:

		WINDOW_STATE m_prevState;
		WINDOW_STATE m_newState;

	};

}
