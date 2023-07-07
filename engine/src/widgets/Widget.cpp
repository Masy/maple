//
// Created by masy on 19.06.2023.
//

#include "maple/widgets/Widget.hpp"
#include "maple/events/InteractStateEvent.hpp"
#include "maple/events/ResizeEvent.hpp"
#include "maple/events/MoveEvent.hpp"
#include "maple/events/FocusEvent.hpp"

using namespace maple::widgets;

Widget *Widget::HOVERED_WIDGET = nullptr;

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

int Widget::x() const {
	return m_posX;
}

int Widget::y() const {
	return m_posY;
}

void Widget::position(const int posX, const int posY) {
	int offsetX = posX - m_posX;
	int offsetY = posY - m_posY;

	if (offsetX == 0 && offsetY == 0)
		return;

	m_posX = posX;
	m_posY = posY;

	auto event = std::make_shared<events::MoveEvent>(offsetX, offsetY);
	event->emit(this);
}

int Widget::width() const {
	return m_width;
}

int Widget::height() const {
	return m_height;
}

void Widget::resize(const int width, const int height) {
	int deltaWidth = width - m_width;
	int deltaHeight = height - m_height;

	if (deltaWidth == 0 && deltaHeight == 0)
		return;

	m_width = width;
	m_height = height;

	auto event = std::make_shared<events::ResizeEvent>(deltaWidth, deltaHeight);
	event->emit(this);
}

bool Widget::visible() const {
	return m_visible;
}

void Widget::visible(const bool visible) {
	m_visible = visible;
}

bool Widget::focused() const {
	return m_focused;
}

void Widget::focused(const bool focused) {
	if (m_focused == focused)
		return;

	m_focused = focused;
	auto event = std::make_shared<events::FocusEvent>(m_focused);
	event->emit(this);
}

INTERACT_STATE Widget::interactState() const {
	return m_interactState;
}

void Widget::interactState(const INTERACT_STATE newState) {
	if (m_interactState == newState)
		return;

	INTERACT_STATE prevState = m_interactState;
	m_interactState = newState;

	auto event = std::make_shared<events::InteractStateEvent>(prevState, newState);
	event->emit(this);
}

void Widget::onMouseEvent(const std::shared_ptr<events::MouseEvent> &event) {
	printf("[Widget] mouse button %d clicked at %d, %d\n", event->mouseButton(), event->cursorX(), event->cursorY());
	if (!event->cancelled())
		event->emit(this);
}
