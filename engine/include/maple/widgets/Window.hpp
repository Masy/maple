//
// Created by masy on 18.06.2023.
//


#pragma once

#include <string_view>
#include <thread>
#include <deque>
#include <functional>
#include <windows.h>
#include "maple/widgets/Widget.hpp"

namespace maple::widgets {

	inline constexpr uint32_t WINDOW_STYLE_BORDER = 0x01;
	inline constexpr uint32_t WINDOW_STYLE_RESIZABLE = 0x03;
	inline constexpr uint32_t WINDOW_STYLE_TITLE_BAR = 0x05;
	inline constexpr uint32_t WINDOW_STYLE_MAXIMIZE_BOX = 0x08;
	inline constexpr uint32_t WINDOW_STYLE_MINIMIZE_BOX = 0x10;
	inline constexpr uint32_t WINDOW_STYLE_POPUP = 0x20;
	inline constexpr uint32_t WINDOW_STYLE_MENU = 0x40;
	inline constexpr uint32_t WINDOW_STYLE_DEFAULT = (WINDOW_STYLE_TITLE_BAR | WINDOW_STYLE_RESIZABLE | WINDOW_STYLE_MAXIMIZE_BOX | WINDOW_STYLE_MINIMIZE_BOX);


	class Window : public Widget {
	public:

		explicit Window(const std::string_view &title, uint32_t style = WINDOW_STYLE_DEFAULT);

		explicit Window(const std::wstring_view &title, uint32_t style = WINDOW_STYLE_DEFAULT);

		~Window() override;

		[[nodiscard]] HWND getWinHandle() const;

		void visible(bool visible) override;

		void close() const;

		[[nodiscard]] events::Event::Worker *eventWorker() const;

		void onMouseEvent(const std::shared_ptr<events::MouseEvent> &event) override;

	protected:

		events::Event::Worker *m_eventWorker;
		HWND m_handle;
		bool m_isPopup = false;

	};

}

