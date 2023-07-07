//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::widgets {
	class Window;
}

namespace maple::events {

	class ActivationEvent : public Event {
	public:

		ActivationEvent(bool activated, widgets::Window *otherWindow);

		[[nodiscard]] bool activated() const;

		[[nodiscard]] widgets::Window *otherWindow() const;

	private:

		bool m_activated;
		widgets::Window *m_otherWindow;

	};

}
