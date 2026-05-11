#include "Iridium/input/mouse.hpp"
#include <array>

namespace ir {
	namespace MouseInput {
		namespace detail {
			std::array<ir::InputState, sf::Mouse::ButtonCount> g_states;
			ir::ApplicationWindow* g_window;
		}

		void setup(ir::ApplicationWindow& window) {
			ir::MouseInput::detail::g_window = &window;
		}

		void update() {
			if (!ir::MouseInput::detail::g_window) {
				for (unsigned int btn = 0; btn < ir::MouseInput::detail::g_states.size(); btn++) {
					ir::MouseInput::detail::g_states[btn] = ir::InputState::IDLE;
				}
			}

			for (unsigned int btn = 0; btn < ir::MouseInput::detail::g_states.size(); btn++) {
				bool focus = ir::MouseInput::detail::g_window->hasFocus();

				bool clicked = focus && sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(btn));

				if (clicked) {
					if (ir::MouseInput::detail::g_states[btn] == ir::InputState::IDLE)
						ir::MouseInput::detail::g_states[btn] = ir::InputState::PRESSED;
					else
						ir::MouseInput::detail::g_states[btn] = ir::InputState::ACTIVE;
				}
				else {
					if (ir::MouseInput::detail::g_states[btn] == ir::InputState::ACTIVE)
						ir::MouseInput::detail::g_states[btn] = ir::InputState::RELEASED;
					else
						ir::MouseInput::detail::g_states[btn] = ir::InputState::IDLE;
				}
			}
		}

		bool isIdle(sf::Mouse::Button _button) {
			if (!ir::MouseInput::detail::g_window)
				return true;
			return ir::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == ir::InputState::IDLE;
		}

		bool isPressed(sf::Mouse::Button _button) {
			if (!ir::MouseInput::detail::g_window)
				return false;
			return ir::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == ir::InputState::PRESSED;
		}

		bool isActive(sf::Mouse::Button _button) {
			if (!ir::MouseInput::detail::g_window)
				return false;
			return ir::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == ir::InputState::ACTIVE;
		}

		bool isReleased(sf::Mouse::Button _button) {
			if (!ir::MouseInput::detail::g_window)
				return false;
			return ir::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == ir::InputState::RELEASED;
		}

		ir::InputState getState(sf::Mouse::Button _button) {
			if (!ir::MouseInput::detail::g_window)
				return ir::InputState::IDLE;
			return ir::MouseInput::detail::g_states[static_cast<unsigned int>(_button)];
		}

		bool isWithinArea(ir::Vector topLeft, ir::Vector size) {
			if (!ir::MouseInput::detail::g_window)
				return false;

			sf::IntRect area {sf::Vector2i{topLeft}, sf::Vector2i{size}};
			return area.contains(sf::Vector2i{ir::MouseInput::getPosition()});
		}

		ir::Vector getPosition() {
			if (!ir::MouseInput::detail::g_window)
				return ir::Vector::kZero;
			
			return ir::Vector::fromSFMLVector(ir::MouseInput::detail::g_window->getMouseCursorPosition());
		}
	}
}