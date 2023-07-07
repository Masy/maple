//
// Created by masy on 06.07.2023.
//

#pragma once

#include <cstdint>

enum INTERACT_STATE {
	/**
	 * The widget is currently neither hovered nor pressed.
	 */
	MAPLE_INTERACT_DEFAULT,
	/**
	 * The widget is currently being hovered over.
	 */
	MAPLE_INTERACT_HOVERED,
	/**
	 * The widget is currently pressed down.
	 *
	 * This doesn't necessarily mean the mouse is on top of the widget, since the widget can be pressed down
	 * and then the mouse moved somewhere else.
	 */
	MAPLE_INTERACT_PRESSED
};

/**
 * Enum describing the current state of the window.
 */
enum WINDOW_STATE {
	/**
	 * The window is open, but neither maximized or minimized.
	 */
	MAPLE_WINDOW_WINDOWED,
	/**
	 * The window is maximized.
	 */
	MAPLE_WINDOW_MAXIMIZED,
	/**
	 * The window is minimized to the icon tray.
	 */
	MAPLE_WINDOW_MINIMIZED
};

enum KEY_STATE {
	MAPLE_KEY_RELEASED,
	MAPLE_KEY_PRESSED,
	MAPLE_KEY_REPEAT
};

inline constexpr uint32_t MAPLE_MOD_SHIFT = 0x01;
inline constexpr uint32_t MAPLE_MOD_CONTROL = 0x02;
inline constexpr uint32_t MAPLE_MOD_ALT = 0x04;
inline constexpr uint32_t MAPLE_MOD_SUPER = 0x08;
inline constexpr uint32_t MAPLE_MOD_CAPS_LOCK = 0x10;
inline constexpr uint32_t MAPLE_MOD_NUM_LOCK = 0x20;

inline constexpr uint32_t MAPLE_KEY_UNKNOWN = 0xFFFFFFFFu;
inline constexpr uint32_t MAPLE_MB_LEFT = 0x00;
inline constexpr uint32_t MAPLE_MB_RIGHT = 0x01;
inline constexpr uint32_t MAPLE_MB_MIDDLE = 0x02;
inline constexpr uint32_t MAPLE_MB_FORWARD = 0x03;
inline constexpr uint32_t MAPLE_MB_BACKWARD = 0x04;


