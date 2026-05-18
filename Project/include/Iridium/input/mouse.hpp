#ifndef IRIDIUM_INPUT_MOUSE_HPP_
#define IRIDIUM_INPUT_MOUSE_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"

namespace ir {
	namespace input {
		enum States {
			IDLE = 0,
			PRESSED = 1,
			ACTIVE = 2,
			RELEASED = 3
		};

		/// @brief Wraps functions for handling mouse input.
		/// Iridium provides a simple wrapper around SFML's utilities to facilitate detection of button states and easier handling of cursor position.
		class Mouse {
		public:
			void update(ir::ApplicationWindow& window);

			bool isIdle(sf::Mouse::Button button); ///< @return Whether the specified button is not being pressed (continuous)
			bool isPressed(sf::Mouse::Button button); ///< @return Whether the specified button was just pressed (1-frame pulse)
			bool isActive(sf::Mouse::Button button); ///< @return Whether the specified button is being held down (continuous)
			bool isReleased(sf::Mouse::Button button); ///< @return Whether the specified button was just released (1-frame pulse)
			ir::input::States getState(sf::Mouse::Button button); ///< @return Current state of the specified button

			/// @return Whether the mouse cursor is within the specified region of the linked application window
			bool isWithinArea(ir::Vector topLeft, ir::Vector size);

			/// @return Mouse position relative to the linked window, or to the desktop if there is none
			ir::Vector getCursorPosition();

		private:
			std::array<ir::input::States, sf::Mouse::ButtonCount> states_ { IDLE };
			ir::Vector cursorPosition_ { ir::Vector::kZero };
		};
	}
}

#endif // IRIDIUM_INPUT_MOUSE_HPP_