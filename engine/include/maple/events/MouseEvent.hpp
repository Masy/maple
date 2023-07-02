//
// Created by masy on 01.07.2023.
//


#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class MouseEvent : public Event {
	public:

		MouseEvent(int x, int y, uint32_t mouseButton, uint32_t modifier, bool doubleClicked);

		[[nodiscard]] int x() const;

		[[nodiscard]] int y() const;

		[[nodiscard]] uint32_t mouseButton() const;

		[[nodiscard]] uint32_t modifier() const;

		[[nodiscard]] bool doubleClicked() const;

	private:

		int m_posX;
		int m_posY;
		uint32_t m_mouseButton;
		uint32_t m_modifier;
		bool m_doubleClicked;

	};

}
