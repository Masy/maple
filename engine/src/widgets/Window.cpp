//
// Created by masy on 18.06.2023.
//

#include <string>
#include <stdexcept>
#include "maple/widgets/Window.hpp"
#include "maple/Application.hpp"

maple::widgets::Window::Window(const std::string_view &title, uint32_t style) : maple::widgets::Widget() {
	m_window = this;
	m_visible = false;
	LONG dwStyle = 0;
	LONG exStyle = 0;
	if (style & WINDOW_STYLE_RESIZABLE)
		dwStyle |= WS_THICKFRAME;
	else if (style & WINDOW_STYLE_BORDER)
		dwStyle |= WS_BORDER;

	if (style & WINDOW_STYLE_TITLE_BAR)
		dwStyle |= WS_CAPTION | WS_SYSMENU;
	if (style & WINDOW_STYLE_MAXIMIZE_BOX)
		dwStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
	if (style & WINDOW_STYLE_MINIMIZE_BOX)
		dwStyle |= WS_MINIMIZEBOX | WS_SYSMENU;

	if (style & WINDOW_STYLE_MENU) {
		dwStyle |= WS_POPUP;
		exStyle |= WS_EX_NOACTIVATE;
		m_isPopup = true;
	} else if (style & WINDOW_STYLE_POPUP) {
		dwStyle |= WS_POPUP;
		exStyle |= WS_EX_ACCEPTFILES;
		m_isPopup = true;
	} else {
		exStyle |= WS_EX_ACCEPTFILES;
	}

	m_width = m_isPopup ? 1 : 854;
	m_height = m_isPopup ? 1 : 480;

	RECT clientArea{};
	clientArea.top = 0;
	clientArea.left = 0;
	clientArea.bottom = m_height;
	clientArea.right = m_width;

	if (AdjustWindowRectEx(&clientArea, dwStyle, false, 0) == 0)
		throw std::runtime_error("Failed to calculate size of content area!");

//	m_windowSizeLimits.ptMinTrackSize.x = m_minWidth + (clientArea.right - clientArea.left - 854);
//	m_windowSizeLimits.ptMinTrackSize.y = m_minHeight + (clientArea.bottom - clientArea.top - 480);
//	m_windowSizeLimits.ptMaxTrackSize.x = m_maxWidth;
//	m_windowSizeLimits.ptMaxTrackSize.y = m_maxHeight;

	int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, title.data(), -1, nullptr, 0);
	std::wstring wTitle(wideStrLen, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, title.data(), -1, wTitle.data(), wideStrLen);

	m_handle = CreateWindowExW(
			0,
			maple::CLASS_NAME,
			(style & WINDOW_STYLE_TITLE_BAR) ? wTitle.data() : nullptr,
			0,
			CW_USEDEFAULT, CW_USEDEFAULT, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top,
			nullptr,
			nullptr,
			maple::Application::getInstance()->getWinInstance(),
			this);

	if (m_handle == nullptr) {
		throw std::runtime_error("Failed to create window handle! " + std::to_string(GetLastError()));
	}

	SetWindowLongW(m_handle, GWL_STYLE, dwStyle);
	SetWindowLongW(m_handle, GWL_EXSTYLE, exStyle);

	m_eventWorker = new events::Event::Worker();
}

maple::widgets::Window::Window(const std::wstring_view &title, uint32_t style) {
	m_window = this;
	m_visible = false;
	LONG dwStyle = 0;
	LONG exStyle = 0;
	if (style & WINDOW_STYLE_RESIZABLE)
		dwStyle |= WS_THICKFRAME;
	else if (style & WINDOW_STYLE_BORDER)
		dwStyle |= WS_BORDER;

	if (style & WINDOW_STYLE_TITLE_BAR)
		dwStyle |= WS_CAPTION | WS_SYSMENU;
	if (style & WINDOW_STYLE_MAXIMIZE_BOX)
		dwStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
	if (style & WINDOW_STYLE_MINIMIZE_BOX)
		dwStyle |= WS_MINIMIZEBOX | WS_SYSMENU;

	if (style & WINDOW_STYLE_MENU) {
		dwStyle |= WS_POPUP;
		exStyle |= WS_EX_NOACTIVATE;
		m_isPopup = true;
	} else if (style & WINDOW_STYLE_POPUP) {
		dwStyle |= WS_POPUP;
		exStyle |= WS_EX_ACCEPTFILES;
		m_isPopup = true;
	} else {
		exStyle |= WS_EX_ACCEPTFILES;
	}

	m_width = m_isPopup ? 1 : 854;
	m_height = m_isPopup ? 1 : 480;

	RECT clientArea{};
	clientArea.top = 0;
	clientArea.left = 0;
	clientArea.bottom = m_height;
	clientArea.right = m_width;

	if (AdjustWindowRectEx(&clientArea, dwStyle, false, 0) == 0)
		throw std::runtime_error("Failed to calculate size of content area!");

//	m_windowSizeLimits.ptMinTrackSize.x = m_minWidth + (clientArea.right - clientArea.left - 854);
//	m_windowSizeLimits.ptMinTrackSize.y = m_minHeight + (clientArea.bottom - clientArea.top - 480);
//	m_windowSizeLimits.ptMaxTrackSize.x = m_maxWidth;
//	m_windowSizeLimits.ptMaxTrackSize.y = m_maxHeight;

	m_handle = CreateWindowExW(
			0,
			maple::CLASS_NAME,
			(style & WINDOW_STYLE_TITLE_BAR) ? title.data() : nullptr,
			0,
			CW_USEDEFAULT, CW_USEDEFAULT, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top,
			nullptr,
			nullptr,
			maple::Application::getInstance()->getWinInstance(),
			this);

	if (m_handle == nullptr) {
		throw std::runtime_error("Failed to create window handle! " + std::to_string(GetLastError()));
	}

	SetWindowLongW(m_handle, GWL_STYLE, dwStyle);
	SetWindowLongW(m_handle, GWL_EXSTYLE, exStyle);

	m_eventWorker = new events::Event::Worker();
}

maple::widgets::Window::~Window() {
	delete m_eventWorker;
	DestroyWindow(m_handle);
}

HWND maple::widgets::Window::getWinHandle() const {
	return m_handle;
}

void maple::widgets::Window::visible(const bool visible) {
	if (m_visible != visible) {
		m_visible = visible;
		if (visible) {
			auto flags = SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW;
			auto zOrder = HWND_TOP;
			if (m_isPopup) {
				flags |= SWP_NOACTIVATE;
				zOrder = HWND_TOPMOST;
			}

			SetWindowPos(m_handle, zOrder, 0, 0, 0, 0, flags);
			PostMessageW(m_handle, WM_SHOWWINDOW, TRUE, 0);
		} else {
			ShowWindow(m_handle, SW_HIDE);
		}
	}
}

void maple::widgets::Window::close() const {
	PostMessageW(m_handle, WM_CLOSE, 0, 0);
}

maple::events::Event::Worker *maple::widgets::Window::eventWorker() const {
	return m_eventWorker;
}

void maple::widgets::Window::onMouseEvent(const std::shared_ptr<events::MouseEvent> &event) {
	printf("[Window] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->x(), event->y());
}
