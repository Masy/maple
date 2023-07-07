//
// Created by masy on 06.07.2023.
//

#include "maple/events/FileDropEvent.hpp"

using namespace maple::events;

FileDropEvent::FileDropEvent(const int cursorX, const int cursorY, std::vector<std::filesystem::path> &&paths)
		: Event(), m_cursorX(cursorX), m_cursorY(cursorY), m_paths(std::move(paths)) {}

int FileDropEvent::cursorX() const {
	return m_cursorX;
}

int FileDropEvent::cursorY() const {
	return m_cursorY;
}

const std::vector<std::filesystem::path> &FileDropEvent::paths() const {
	return m_paths;
}
