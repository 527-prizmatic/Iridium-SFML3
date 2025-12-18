#include "Iridium/input/mouse.hpp"
#include <array>

namespace Ir {
	namespace MouseInput {
		namespace _priv {
			std::array<Ir::InputState, sf::Mouse::ButtonCount> g_states;
			Ir::ApplicationWindow* g_window;
		}

		void Setup(Ir::ApplicationWindow& _app_window) {
			Ir::MouseInput::_priv::g_window = &_app_window;
		}

		void Update() {
			if (!Ir::MouseInput::_priv::g_window) {
				for (unsigned int btn = 0; btn < Ir::MouseInput::_priv::g_states.size(); btn++) {
					Ir::MouseInput::_priv::g_states[btn] = Ir::InputState::IDLE;
				}
			}

			for (unsigned int btn = 0; btn < Ir::MouseInput::_priv::g_states.size(); btn++) {
				bool focus = Ir::MouseInput::_priv::g_window->HasFocus();

				bool clicked = focus && sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(btn));

				if (clicked) {
					if (Ir::MouseInput::_priv::g_states[btn] == Ir::InputState::IDLE)
						Ir::MouseInput::_priv::g_states[btn] = Ir::InputState::PRESSED;
					else
						Ir::MouseInput::_priv::g_states[btn] = Ir::InputState::ACTIVE;
				}
				else {
					if (Ir::MouseInput::_priv::g_states[btn] == Ir::InputState::ACTIVE)
						Ir::MouseInput::_priv::g_states[btn] = Ir::InputState::RELEASED;
					else
						Ir::MouseInput::_priv::g_states[btn] = Ir::InputState::IDLE;
				}
			}
		}

		bool IsIdle(sf::Mouse::Button _button) {
			if (!Ir::MouseInput::_priv::g_window)
				return true;
			return Ir::MouseInput::_priv::g_states[static_cast<unsigned int>(_button)] == Ir::InputState::IDLE;
		}

		bool IsPressed(sf::Mouse::Button _button) {
			if (!Ir::MouseInput::_priv::g_window)
				return false;
			return Ir::MouseInput::_priv::g_states[static_cast<unsigned int>(_button)] == Ir::InputState::PRESSED;
		}

		bool IsActive(sf::Mouse::Button _button) {
			if (!Ir::MouseInput::_priv::g_window)
				return false;
			return Ir::MouseInput::_priv::g_states[static_cast<unsigned int>(_button)] == Ir::InputState::ACTIVE;
		}

		bool IsReleased(sf::Mouse::Button _button) {
			if (!Ir::MouseInput::_priv::g_window)
				return false;
			return Ir::MouseInput::_priv::g_states[static_cast<unsigned int>(_button)] == Ir::InputState::RELEASED;
		}

		Ir::InputState GetState(sf::Mouse::Button _button) {
			if (!Ir::MouseInput::_priv::g_window)
				return Ir::InputState::IDLE;
			return Ir::MouseInput::_priv::g_states[static_cast<unsigned int>(_button)];
		}

		bool IsWithinArea(Ir::Vector _top_left, Ir::Vector _size) {
			if (!Ir::MouseInput::_priv::g_window)
				return false;

			sf::IntRect area {sf::Vector2i{_top_left}, sf::Vector2i{_size}};
			return area.contains(sf::Mouse::getPosition());
		}

		Ir::Vector GetPosition() {
			if (!Ir::MouseInput::_priv::g_window)
				return Ir::Vector::zero;
			
			return Ir::Vector::FromSFMLVector(Ir::MouseInput::_priv::g_window->GetMouseCursorPosition());
		}
	}
}