//
// Created by masy on 19.06.2023.
//

#pragma once

#include <limits>

namespace maple::widgets {

	class Window;

	class Widget {
	public:

		virtual ~Widget() noexcept;

		[[nodiscard]] bool isVisible() const;

		virtual void setVisible(bool visible);

		inline void show() {
			setVisible(true);
		}

		inline void hide() {
			setVisible(false);
		}

	protected:

		Widget();

	protected:

		Window *m_window = nullptr;
		Widget *m_parent = nullptr;
		int m_width = 80;
		int m_height = 24;
		int m_minWidth = -1;
		int m_minHeight = -1;
		int m_maxWidth = std::numeric_limits<int>::max();
		int m_maxHeight = std::numeric_limits<int>::max();
		bool m_visible = true;
		int m_tabIndex = 0;

	};

}
