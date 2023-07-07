//
// Created by masy on 03.07.2023.
//

#pragma once

#include "maple/events/Event.hpp"

namespace maple::events {

	class ContentScaleEvent : public Event {
	public:

		ContentScaleEvent(float prevScale, float newScale);

		[[nodiscard]] float prevScale() const;

		[[nodiscard]] float newScale() const;

	private:

		float m_prevScale;
		float m_newScale;

	};

}
