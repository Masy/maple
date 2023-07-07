//
// Created by masy on 16.06.2023.
//

#include <stdexcept>
#include <windowsx.h>
#include "maple/Application.hpp"
#include "maple/events/Events.hpp"
#include "maple/Maple.hpp"

maple::Application *maple::Application::getInstance() {
	return INSTANCE;
}

LRESULT maple::Application::handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_CREATE) {
		auto *createInfo = reinterpret_cast<CREATESTRUCTW*>(lParam);
		INSTANCE->m_windows[hWnd] = reinterpret_cast<maple::widgets::Window*>(createInfo->lpCreateParams);
		return 0;
	} else if (uMsg == INSTANCE->m_eventMsgId) {
		auto *winEvent = reinterpret_cast<maple::events::WinEvent*>(lParam);

		for (auto &handler = winEvent->handlers.first; handler != winEvent->handlers.second; handler++) {
			if (winEvent->event->cancelled())
				break;

			handler->second(winEvent->widget, winEvent->event);
		}

		if (winEvent->cv != nullptr) {
			*winEvent->finished = true;
			winEvent->cv->notify_all();
		}

		delete winEvent;
		return 0;
	}

	if (uMsg != WM_QUIT) {
		widgets::Window *pWindow;
		try {
			pWindow = INSTANCE->m_windows.at(hWnd);
		} catch (const std::exception &) {
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}

		switch (uMsg) {
			case WM_DESTROY: {
				auto event = std::make_shared<events::WindowDestroyEvent>();
				event->emit(pWindow);
				delete pWindow;
				INSTANCE->m_windows.erase(hWnd);
			} break;

			case WM_MOVE:{
				int x = (int) (short) LOWORD(lParam);
				int y = (int) (short) HIWORD(lParam);
				if (x == -32000 || y == -32000)
					return 0;

				pWindow->position(x, y);
			} break;

			case WM_SIZE:{
				RECT clientArea;
				GetClientRect(pWindow->winHandle(), &clientArea);
				int width = (clientArea.right - clientArea.left);
				int height = (clientArea.bottom - clientArea.top);

				pWindow->resize(width, height);


				switch(wParam){
					case SIZE_MAXIMIZED: pWindow->state(MAPLE_WINDOW_MAXIMIZED);
						break;

					case SIZE_MINIMIZED: pWindow->state(MAPLE_WINDOW_MINIMIZED);
						break;

					case SIZE_RESTORED: pWindow->state(MAPLE_WINDOW_WINDOWED);
						break;

					default: break;
				}
			} break;

			case WM_ACTIVATE: {
				bool activated = LOWORD(wParam) != WA_INACTIVE;
				widgets::Window *pOtherWindow = INSTANCE->m_windows.at(hWnd);

				auto event = std::make_shared<events::ActivationEvent>(activated, pOtherWindow);
				event->emit(pWindow);
			} break;

			case WM_SETFOCUS:{
				pWindow->focused(true);
			} break;

			case WM_KILLFOCUS:{
				pWindow->focused(false);
			} break;

			case WM_CLOSE: {
				auto event = std::make_shared<events::WindowCloseEvent>();
				event->emit(pWindow);
				if (event->cancelled())
					return 0;
			} break;

			case WM_SHOWWINDOW: {
				pWindow->visible(wParam == TRUE);
				//TODO: add to render queue if now visible
			} break;

			case WM_MOUSEACTIVATE : {
				if (pWindow->isPopup())
					return MA_NOACTIVATE;

				break;
			}

			case WM_GETMINMAXINFO:{
				auto sizeLimits = (LPMINMAXINFO) lParam;
				sizeLimits->ptMinTrackSize = pWindow->minMaxInfo().ptMinTrackSize;
				sizeLimits->ptMaxTrackSize = pWindow->minMaxInfo().ptMaxTrackSize;
			} break;

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:{
				uint64_t keyCode = wParam;
				bool repeat = lParam & 0x40000000u;
				auto event = std::make_shared<events::KeyEvent>(keyCode, getModifierBitMask(), repeat ? MAPLE_KEY_REPEAT : MAPLE_KEY_PRESSED);
				event->emit(pWindow);
			} break;

			case WM_KEYUP:
			case WM_SYSKEYUP:{
				uint64_t keyCode = wParam;
				auto event = std::make_shared<events::KeyEvent>(keyCode, getModifierBitMask(), MAPLE_KEY_RELEASED);
				event->emit(pWindow);
			} break;

			case WM_CHAR: {
				uint32_t codePoint = wParam;
				if (codePoint == UNICODE_NOCHAR)
					break;

				auto event = std::make_shared<events::CharEvent>(codePoint);
				event->emit(pWindow);
			} break;

			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_XBUTTONDOWN: {
				int x = (int) (short) LOWORD(lParam);
				int y = (int) (short) HIWORD(lParam);
				uint32_t mouseButton;

				switch(uMsg) {
					case WM_RBUTTONDOWN:
						mouseButton = MAPLE_MB_RIGHT;
						break;
					case WM_MBUTTONDOWN:
						mouseButton = MAPLE_MB_MIDDLE;
						break;
					case WM_XBUTTONDOWN:
						if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
							mouseButton = MAPLE_MB_FORWARD;
						else
							mouseButton = MAPLE_MB_BACKWARD;
						break;
					default:
						mouseButton = MAPLE_MB_LEFT;
						break;
				}

				auto event = std::make_shared<events::MouseEvent>(x, y, mouseButton, getModifierBitMask(), MAPLE_KEY_PRESSED);
				event->emit(pWindow);
			} break;

			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			case WM_XBUTTONUP: {
				int x = (int) (short) LOWORD(lParam);
				int y = (int) (short) HIWORD(lParam);
				uint32_t mouseButton;

				switch(uMsg) {
					case WM_RBUTTONUP:
						mouseButton = MAPLE_MB_RIGHT;
						break;
					case WM_MBUTTONUP:
						mouseButton = MAPLE_MB_MIDDLE;
						break;
					case WM_XBUTTONUP:
						if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
							mouseButton = MAPLE_MB_FORWARD;
						else
							mouseButton = MAPLE_MB_BACKWARD;
						break;
					default:
						mouseButton = MAPLE_MB_LEFT;
						break;
				}

				auto event = std::make_shared<events::MouseEvent>(x, y, mouseButton, getModifierBitMask(), MAPLE_KEY_RELEASED);
				event->emit(pWindow);
			} break;

			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDBLCLK:
			case WM_XBUTTONDBLCLK: {
				int x = (int) (short) LOWORD(lParam);
				int y = (int) (short) HIWORD(lParam);
				uint32_t mouseButton;

				switch(uMsg) {
					case WM_RBUTTONDBLCLK:
						mouseButton = MAPLE_MB_RIGHT;
						break;
					case WM_MBUTTONDBLCLK:
						mouseButton = MAPLE_MB_MIDDLE;
						break;
					case WM_XBUTTONDBLCLK:
						if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
							mouseButton = MAPLE_MB_BACKWARD;
						else
							mouseButton = MAPLE_MB_FORWARD;
						break;
					default:
						mouseButton = MAPLE_MB_LEFT;
						break;
				}

				auto event = std::make_shared<events::DoubleClickEvent>(x, y, mouseButton, getModifierBitMask());
				event->emit(pWindow);
			} break;

			case WM_MOUSEWHEEL:{
				auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
				POINT cursorPos = {(int) (short) LOWORD(lParam), (int) (short) HIWORD(lParam)};
				ScreenToClient(hWnd, &cursorPos);

				auto event = std::make_shared<events::ScrollEvent>(cursorPos.x, cursorPos.y, 0, zDelta, getModifierBitMask());
				event->emit(pWindow);
			} break;

			case WM_MOUSEHWHEEL:{
				auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
				POINT cursorPos = {(int) (short) LOWORD(lParam), (int) (short) HIWORD(lParam)};
				ScreenToClient(hWnd, &cursorPos);

				auto event = std::make_shared<events::ScrollEvent>(cursorPos.x, cursorPos.y, zDelta, 0, getModifierBitMask());
				event->emit(pWindow);
			} break;

			case WM_DROPFILES: {
				auto hDrop = (HDROP) wParam;
				POINT cursor;
				DragQueryPoint(hDrop, &cursor);

				size_t count = DragQueryFileW(hDrop, 0xFFFFFFFF, nullptr, 0);
				std::vector<std::filesystem::path> paths;
				paths.resize(count);
				for (size_t n = 0; n < count; n++) {
					int size = (int) DragQueryFileW(hDrop, n, nullptr, 0) + 1;
					WCHAR buffer[size];
					DragQueryFileW(hDrop, n, buffer, size);
					paths[n] = std::filesystem::path(buffer);
				}

				DragFinish(hDrop);

				auto event = std::make_shared<events::FileDropEvent>(cursor.x, cursor.y, std::move(paths));
				event->emit(pWindow);
			} break;

			case WM_MOUSEMOVE:{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);

				if (pWindow->interactState() == MAPLE_INTERACT_DEFAULT) {
					pWindow->interactState(MAPLE_INTERACT_HOVERED);
					auto event = std::make_shared<events::MouseEnterEvent>();
					event->emit(pWindow);
				}

				auto event = std::make_shared<events::MouseMoveEvent>(x, y);
				event->emit(pWindow);

				TRACKMOUSEEVENT tracker{};
				tracker.cbSize = sizeof(tracker);
				tracker.dwFlags = TME_LEAVE | TME_HOVER;
				tracker.hwndTrack = hWnd;
				tracker.dwHoverTime = HOVER_DEFAULT;

				TrackMouseEvent(&tracker);
			} break;

			case WM_MOUSEHOVER: {
				if (maple::widgets::Widget::HOVERED_WIDGET == nullptr)
					break;

				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);

				auto event = std::make_shared<events::MouseHoverEvent>(x, y);
				event->emit(maple::widgets::Widget::HOVERED_WIDGET);
			} break;

			case WM_MOUSELEAVE:{
				pWindow->interactState(MAPLE_INTERACT_DEFAULT);
				auto event = std::make_shared<events::MouseLeaveEvent>();
				event->emit(pWindow);
			} break;

			case WM_DPICHANGED: {
				auto oldScale = pWindow->contentScale();
				auto newScale = (float) HIWORD(wParam) / USER_DEFAULT_SCREEN_DPI;

				auto event = std::make_shared<events::ContentScaleEvent>(oldScale, newScale);
				event->emit(pWindow);

				RECT *const prcNewWindow = (RECT *) lParam;
				SetWindowPos(hWnd, nullptr, prcNewWindow->left, prcNewWindow->top,
							 prcNewWindow->right - prcNewWindow->left,
							 prcNewWindow->bottom - prcNewWindow->top,
							 SWP_NOZORDER | SWP_NOACTIVATE);
			} break;

			default:
				break;
		}
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

maple::Application::Application([[maybe_unused]] const int argc, [[maybe_unused]] const char **argv) {
	if (INSTANCE != nullptr)
		throw std::runtime_error("Failed to create maple application instance: There is an instance already!");

	m_windowClass.lpfnWndProc = handleMessage;
	m_windowClass.hInstance = GetModuleHandleW(maple::CLASS_NAME);
	m_windowClass.lpszClassName = maple::CLASS_NAME;
	m_windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_windowClass.style = CS_DBLCLKS;

	RegisterClassW(&m_windowClass);

	m_eventMsgId = RegisterWindowMessageW(L"mapleEventMessage");
	if (m_eventMsgId == 0)
		throw std::runtime_error("Failed to register maple event message!");

	m_threadId = GetCurrentThreadId();

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	INSTANCE = this;
}

void maple::Application::run() {
	MSG message{};

	while (GetMessageW(&message, nullptr, 0, 0) > 0) {
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
}

void maple::Application::stop() {
	PostQuitMessage(0);
}

HINSTANCE maple::Application::getWinInstance() const {
	return m_windowClass.hInstance;
}

uint32_t maple::Application::getEventMessageId() const {
	return m_eventMsgId;
}

uint64_t maple::Application::getThreadId() const {
	return m_threadId;
}

uint32_t maple::Application::getModifierBitMask() {
	uint32_t bitmask = 0;

	if (HIBYTE(GetKeyState(VK_SHIFT)))
		bitmask |= MAPLE_MOD_SHIFT;
	if (HIBYTE(GetKeyState(VK_CONTROL)))
		bitmask |= MAPLE_MOD_CONTROL;
	if (HIBYTE(GetKeyState(VK_MENU)))
		bitmask |= MAPLE_MOD_ALT;
	if (LOBYTE(GetKeyState(VK_CAPITAL)))
		bitmask |= MAPLE_MOD_CAPS_LOCK;
	if (LOBYTE(GetKeyState(VK_NUMLOCK)))
		bitmask |= MAPLE_MOD_NUM_LOCK;

	return bitmask;
}
