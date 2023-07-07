//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class ScrollEvent : public Event {
	public:

		ScrollEvent(int cursorX, int cursorY, int offsetX, int offsetY, uint32_t modifiers);

		[[nodiscard]] int cursorX() const;

		[[nodiscard]] int cursorY() const;

		[[nodiscard]] int offsetX() const;

		[[nodiscard]] int offsetY() const;

		[[nodiscard]] uint32_t modifiers() const;

	private:

		int m_cursorX;
		int m_cursorY;
		int m_offsetX;
		int m_offsetY;
		uint32_t m_modifiers;

	};

}
