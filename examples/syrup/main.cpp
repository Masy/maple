//
// Created by masy on 18.06.2023.
//

#include "maple/Application.hpp"

int main(int argc, const char **argv) {
	maple::Application app(argc, argv);

	auto *mainWindow = new maple::widgets::Window("Title");

	maple::events::connect(mainWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
		printf("[1] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->x(), event->y());
	});

	maple::events::connect(mainWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
		printf("[2] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->x(), event->y());
		if (event->x() > window->width() / 2)
			event->cancelled(true);
	});
	maple::events::connect(mainWindow, [] (maple::widgets::Widget *window, const std::shared_ptr<maple::events::MouseEvent> &event) {
		printf("[3] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->x(), event->y());
	});

	mainWindow->show();

	app.run();
}