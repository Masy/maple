//
// Created by masy on 16.06.2023.
//

#pragma once

#include <map>
#include <windows.h>

#include "maple/widgets/Window.hpp"

namespace maple {

	inline constexpr const WCHAR *CLASS_NAME = L"libmaple_engine.dll";

	class Application {
	public:

		static Application *getInstance();

		[[nodiscard]] static uint32_t getModifierBitMask();

	private:

		static LRESULT CALLBACK handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:

		Application(int argc, const char **argv);

		void run();

		void stop();

		[[nodiscard]] HINSTANCE getWinInstance() const;

		[[nodiscard]] uint32_t getEventMessageId() const;

		[[nodiscard]] uint64_t getThreadId() const;

	private:

		inline static Application *INSTANCE = nullptr;
		WNDCLASSW m_windowClass{};
		uint32_t m_eventMsgId = 0;
		uint64_t m_threadId = 0;
		std::map<HWND, widgets::Window*> m_windows;

	};

}