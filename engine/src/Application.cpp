//
// Created by masy on 16.06.2023.
//

#include <stdexcept>
#include "maple/Application.hpp"

maple::Application *maple::Application::getInstance() {
	return INSTANCE;
}

LRESULT maple::Application::handleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_CREATE) {
		auto *createInfo = reinterpret_cast<CREATESTRUCTW*>(lParam);
		INSTANCE->m_windows[hWnd] = reinterpret_cast<maple::widgets::Window*>(createInfo->lpCreateParams);
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
			case WM_CLOSE: {
				delete pWindow;
			} break;

			case WM_DESTROY: {
				INSTANCE->m_windows.erase(hWnd);
				INSTANCE->stop();
			} break;

			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_XBUTTONDOWN: {
				int x = (int) (short) LOWORD(lParam);
				int y = (int) (short) HIWORD(lParam);
				int mouseButton;

				switch(uMsg){
					case WM_RBUTTONDOWN:
						mouseButton = 1;
						break;
					case WM_MBUTTONDOWN:
						mouseButton = 2;
						break;
					case WM_XBUTTONDOWN:
						if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
							mouseButton = 3;
						else
							mouseButton = 4;
						break;
					default:
						mouseButton = 0;
						break;
				}

				auto event = std::make_shared<events::MouseEvent>(x, y, mouseButton, 0, false);
				event->emit(pWindow);
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
