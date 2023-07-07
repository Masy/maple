//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class ResizeEvent : public Event {
	public:

		ResizeEvent(int deltaWidth, int deltaHeight);

		[[nodiscard]] int deltaWidth() const;

		[[nodiscard]] int deltaHeight() const;

	private:

		int m_deltaWidth;
		int m_deltaHeight;

	};

}
