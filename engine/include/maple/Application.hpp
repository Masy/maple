//
// Created by masy on 16.06.2023.
//

#pragma once

#include <map>
#include "windows.h"

#include "maple/widgets/Window.hpp"

namespace maple {

	inline constexpr const WCHAR *CLASS_NAME = L"libmaple_engine.dll";

	class Application {
	public:

		static Application *getInstance();


	private:

		static LRESULT CALLBACK handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:

		Application(int argc, const char **argv);

		void run();

		void stop();

		HINSTANCE getWinInstance() const;

	private:

		inline static Application *INSTANCE = nullptr;
		WNDCLASSW m_windowClass{};
		std::map<HWND, widgets::Window*> m_windows;

	};

}