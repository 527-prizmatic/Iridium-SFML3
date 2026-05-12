#include "Iridium/input/mouse.hpp"
#include <array>

namespace iridium {
	namespace MouseInput {
		namespace detail {
			std::array<iridium::InputState, sf::Mouse::ButtonCount> g_states;
			iridium::ApplicationWindow* g_window;
		}

		void Setup(iridium::ApplicationWindow& _app_window) {
			iridium::MouseInput::detail::g_window = &_app_window;
		}

		void update() {
			if (!iridium::MouseInput::detail::g_window) {
				for (unsigned int btn = 0; btn < iridium::MouseInput::detail::g_states.size(); btn++) {
					iridium::MouseInput::detail::g_states[btn] = iridium::InputState::IDLE;
				}
			}

			for (unsigned int btn = 0; btn < iridium::MouseInput::detail::g_states.size(); btn++) {
				bool focus = iridium::MouseInput::detail::g_window->HasFocus();

				bool clicked = focus && sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(btn));

				if (clicked) {
					if (iridium::MouseInput::detail::g_states[btn] == iridium::InputState::IDLE)
						iridium::MouseInput::detail::g_states[btn] = iridium::InputState::PRESSED;
					else
						iridium::MouseInput::detail::g_states[btn] = iridium::InputState::ACTIVE;
				}
				else {
					if (iridium::MouseInput::detail::g_states[btn] == iridium::InputState::ACTIVE)
						iridium::MouseInput::detail::g_states[btn] = iridium::InputState::RELEASED;
					else
						iridium::MouseInput::detail::g_states[btn] = iridium::InputState::IDLE;
				}
			}
		}

		bool IsIdle(sf::Mouse::Button _button) {
			if (!iridium::MouseInput::detail::g_window)
				return true;
			return iridium::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == iridium::InputState::IDLE;
		}

		bool IsPressed(sf::Mouse::Button _button) {
			if (!iridium::MouseInput::detail::g_window)
				return false;
			return iridium::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == iridium::InputState::PRESSED;
		}

		bool IsActive(sf::Mouse::Button _button) {
			if (!iridium::MouseInput::detail::g_window)
				return false;
			return iridium::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == iridium::InputState::ACTIVE;
		}

		bool IsReleased(sf::Mouse::Button _button) {
			if (!iridium::MouseInput::detail::g_window)
				return false;
			return iridium::MouseInput::detail::g_states[static_cast<unsigned int>(_button)] == iridium::InputState::RELEASED;
		}

		iridium::InputState GetState(sf::Mouse::Button _button) {
			if (!iridium::MouseInput::detail::g_window)
				return iridium::InputState::IDLE;
			return iridium::MouseInput::detail::g_states[static_cast<unsigned int>(_button)];
		}

		bool IsWithinArea(iridium::Vector _top_left, iridium::Vector _size) {
			if (!iridium::MouseInput::detail::g_window)
				return false;

			sf::IntRect area {sf::Vector2i{_top_left}, sf::Vector2i{_size}};
			return area.contains(sf::Vector2i{iridium::MouseInput::getPosition()});
		}

		iridium::Vector getPosition() {
			if (!iridium::MouseInput::detail::g_window)
				return iridium::Vector::kZero;
			
			return iridium::Vector::fromSFMLVector(iridium::MouseInput::detail::g_window->GetMouseCursorPosition());
		}
	}
}