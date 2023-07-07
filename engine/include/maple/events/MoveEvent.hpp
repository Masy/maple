//
// Created by masy on 07.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class MoveEvent : public Event {
	public:

		MoveEvent(int offsetX, int offsetY);

		[[nodiscard]] int offsetX() const;

		[[nodiscard]] int offsetY() const;

	private:

		int m_offsetX;
		int m_offsetY;

	};

}
