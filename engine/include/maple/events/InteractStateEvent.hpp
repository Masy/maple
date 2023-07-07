//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"
#include "maple/Maple.hpp"

namespace maple::events {

	class InteractStateEvent : public Event {
	public:

		InteractStateEvent(INTERACT_STATE prevState, INTERACT_STATE newState);

		[[nodiscard]] INTERACT_STATE prevState() const;

		[[nodiscard]] INTERACT_STATE newState() const;

	private:

		INTERACT_STATE m_prevState;
		INTERACT_STATE m_newState;

	};

}
