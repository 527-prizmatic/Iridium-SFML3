#include "Iridium/input/mouse.hpp"
#include <array>

namespace ir {
	namespace input {
		void Mouse::update(ir::ApplicationWindow& window) {
			cursorPosition_ = ir::Vector::fromSFMLVector(window.getMouseCursorPosition());

			bool focus = window.hasFocus();
			for (unsigned int btn = 0; btn <  states_.size(); btn++) {
				bool clicked = focus && sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(btn));

				if (clicked) {
					if ( states_[btn] == States::IDLE) {
						states_[btn] = States::PRESSED;
					} else {
						states_[btn] = States::ACTIVE;
					}
				} else {
					if ( states_[btn] == States::ACTIVE) {
						states_[btn] = States::RELEASED;
					} else {
						states_[btn] = States::IDLE;
					}
				}
			}
		}

		bool Mouse::isIdle(sf::Mouse::Button button) {
			return states_[static_cast<unsigned int>(button)] == States::IDLE;
		}

		bool Mouse::isPressed(sf::Mouse::Button button) {
			return states_[static_cast<unsigned int>(button)] == States::PRESSED;
		}

		bool Mouse::isActive(sf::Mouse::Button button) {
			return  states_[static_cast<unsigned int>(button)] == States::ACTIVE;
		}

		bool Mouse::isReleased(sf::Mouse::Button button) {
			return  states_[static_cast<unsigned int>(button)] == States::RELEASED;
		}

		ir::input::States Mouse::getState(sf::Mouse::Button button) {
			return  states_[static_cast<unsigned int>(button)];
		}

		bool Mouse::isWithinArea(ir::Vector topLeft, ir::Vector size) {
			sf::IntRect area {sf::Vector2i{topLeft}, sf::Vector2i{size}};
			return area.contains(sf::Vector2i{cursorPosition_});
		}

		ir::Vector Mouse::getCursorPosition() {
			return cursorPosition_;
		}
	}
}