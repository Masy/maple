//
// Created by masy on 19.06.2023.
//

#include "maple/widgets/Widget.hpp"
#include "maple/widgets/Window.hpp"

using namespace maple::widgets;

Widget::Widget() = default;

Widget::~Widget() noexcept = default;

bool Widget::isVisible() const {
	return m_visible;
}

void Widget::setVisible(const bool visible) {
	m_visible = visible;
}
