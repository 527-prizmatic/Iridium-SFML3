#ifndef IRIDIUM_INPUT_MOUSE_HPP_
#define IRIDIUM_INPUT_MOUSE_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"

namespace iridium {
	enum InputState {
		IDLE = 0,
		PRESSED = 1,
		ACTIVE = 2,
		RELEASED = 3
	};

	/// @brief Wraps functions for handling mouse input.
	/// Iridium provides a simple wrapper around SFML's utilities to facilitate detection of mouse button states
	/// and easier handling of mouse cursor position.
	/// All mouse input is considered inactive if there is no linked window, or if it loses system focus.
	namespace MouseInput {
		/// @brief Sets up mouse input and links an application window,
		/// for detecting window focus and relative cursor position.
		void Setup(iridium::ApplicationWindow& _app_window);

		void update();

		bool IsIdle(sf::Mouse::Button _button); ///< @return Whether the specified button is not being pressed (continuous)
		bool IsPressed(sf::Mouse::Button _button); ///< @return Whether the specified button was just pressed (1-frame pulse)
		bool IsActive(sf::Mouse::Button _button); ///< @return Whether the specified button is being held down (continuous)
		bool IsReleased(sf::Mouse::Button _button); ///< @return Whether the specified button was just released (1-frame pulse)
		iridium::InputState GetState(sf::Mouse::Button _button); ///< @return Current state of the specified button

		/// @return Whether the mouse cursor is within the specified region of the linked application window
		bool IsWithinArea(iridium::Vector _top_left, iridium::Vector _size);

		/// @return Mouse position relative to the linked window, or to the desktop if there is none
		iridium::Vector getPosition();
	}
}

#endif // IRIDIUM_INPUT_MOUSE_HPP_