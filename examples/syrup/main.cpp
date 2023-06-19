//
// Created by masy on 18.06.2023.
//

#include "maple/Application.hpp"

int main(int argc, const char **argv) {
	maple::Application app(argc, argv);

	auto *mainWindow = new maple::widgets::Window("Title");
	mainWindow->show();

	app.run();
}