//
// Created by masy on 03.07.2023.
//

#pragma once

#include <filesystem>
#include <vector>
#include "maple/events/Event.hpp"

namespace maple::events {

	class FileDropEvent : public Event {
	public:

		FileDropEvent(int cursorX, int cursorY, std::vector<std::filesystem::path> &&paths);

		[[nodiscard]] int cursorX() const;

		[[nodiscard]] int cursorY() const;

		[[nodiscard]] const std::vector<std::filesystem::path> &paths() const;

	private:

		int m_cursorX;
		int m_cursorY;
		std::vector<std::filesystem::path> m_paths;

	};

}
