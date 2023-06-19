//
// Created by masy on 18.06.2023.
//


#pragma once

#include <string_view>
#include <thread>
#include "windows.h"

namespace maple::widgets {

	inline constexpr uint32_t WINDOW_STYLE_BORDER = 0x01;
	inline constexpr uint32_t WINDOW_STYLE_RESIZABLE = 0x03;
	inline constexpr uint32_t WINDOW_STYLE_TITLE_BAR = 0x05;
	inline constexpr uint32_t WINDOW_STYLE_MAXIMIZE_BOX = 0x08;
	inline constexpr uint32_t WINDOW_STYLE_MINIMIZE_BOX = 0x10;
	inline constexpr uint32_t WINDOW_STYLE_POPUP = 0x20;
	inline constexpr uint32_t WINDOW_STYLE_MENU = 0x40;
	inline constexpr uint32_t WINDOW_STYLE_DEFAULT = (WINDOW_STYLE_TITLE_BAR | WINDOW_STYLE_RESIZABLE | WINDOW_STYLE_MAXIMIZE_BOX | WINDOW_STYLE_MINIMIZE_BOX);


	class Window {
	public:

		Window(const std::string_view &title, uint32_t style = WINDOW_STYLE_DEFAULT);

//		Window(const std::wstring_view &title, uint32_t style);

		~Window();

		[[nodiscard]] HWND getWinHandle() const;

		void setVisible(bool visible);

		inline void show() {
			setVisible(true);
		}

		inline void hide() {
			setVisible(false);
		}

		void close() const;

	protected:

		std::thread m_eventThread;
		HWND m_handle;
		bool m_isPopup = false;
		int m_width;
		int m_height;
		bool m_visible = false;

	};

}

