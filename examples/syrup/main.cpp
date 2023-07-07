//
// Created by masy on 18.06.2023.
//

#include "maple/Application.hpp"
#include "maple/events/WindowDestroyEvent.hpp"
#include "maple/events/ContentScaleEvent.hpp"

int main(int argc, const char **argv) {
	maple::Application app(argc, argv);

	auto *mainWindow = new maple::widgets::Window("Title");

	maple::events::connect(mainWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
		printf("[1] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->cursorX(), event->cursorY());
	});

	maple::events::connect(mainWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
		printf("[2] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->cursorX(), event->cursorY());
		if (event->cursorX() > window->width() / 2) {
			event->cancelled(true);
			auto *testWindow = new maple::widgets::Window("popup");
			maple::events::connect(testWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
				printf("test\n");
			});
			testWindow->show();
		}
	});
	maple::events::connect(mainWindow, [] (maple::widgets::Window *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
		printf("[3] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->cursorX(), event->cursorY());
	});

	maple::events::connect(mainWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::WindowDestroyEvent> &event) {
		maple::Application::getInstance()->stop();
	});

	mainWindow->show();

	app.run();
}