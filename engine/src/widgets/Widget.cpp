//
// Created by masy on 19.06.2023.
//

#include "maple/widgets/Widget.hpp"

using namespace maple::widgets;

Widget::Widget() {
	maple::events::connect(this, &Widget::onMouseEvent);
}

Widget::~Widget() noexcept {
	// Erase all registered event handlers of this widget
	maple::events::disconnect(this);
}

Window *Widget::window() {
	return m_window;
}

int Widget::width() const {
	return m_width;
}

int Widget::height() const {
	return m_height;
}

bool Widget::visible() const {
	return m_visible;
}

void Widget::visible(const bool visible) {
	m_visible = visible;
}

void Widget::onMouseEvent(const std::shared_ptr<events::MouseEvent> &event) {
	printf("[Widget] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->x(), event->y());
	if (!event->cancelled())
		event->emit(this);
}
