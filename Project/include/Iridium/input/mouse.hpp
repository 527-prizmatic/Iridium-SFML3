#ifndef IRIDIUM_INPUT_MOUSE_HPP_
#define IRIDIUM_INPUT_MOUSE_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"

namespace ir {
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
	/// @todo Could likely be replaced by a class.
	namespace MouseInput {
		/// @brief Sets up mouse input and links an application window,
		/// for detecting window focus and relative cursor position.
		void setup(ir::ApplicationWindow& window);

		void update();

		bool isIdle(sf::Mouse::Button button); ///< @return Whether the specified button is not being pressed (continuous)
		bool isPressed(sf::Mouse::Button button); ///< @return Whether the specified button was just pressed (1-frame pulse)
		bool isActive(sf::Mouse::Button button); ///< @return Whether the specified button is being held down (continuous)
		bool isReleased(sf::Mouse::Button button); ///< @return Whether the specified button was just released (1-frame pulse)
		ir::InputState getState(sf::Mouse::Button button); ///< @return Current state of the specified button

		/// @return Whether the mouse cursor is within the specified region of the linked application window
		bool isWithinArea(ir::Vector topLeft, ir::Vector size);

		/// @return Mouse position relative to the linked window, or to the desktop if there is none
		ir::Vector getPosition();
	}
}

#endif // IRIDIUM_INPUT_MOUSE_HPP_