#ifndef IRIDIUM_INPUT_MOUSE_HPP_
#define IRIDIUM_INPUT_MOUSE_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"

namespace Ir {
	enum InputState {
		IDLE = 0,
		PRESSED = 1,
		ACTIVE = 2,
		RELEASED = 3
	};

	namespace MouseInput {
		void Setup(Ir::ApplicationWindow& _app_window);

		void Update();

		bool IsIdle(sf::Mouse::Button _button);
		bool IsPressed(sf::Mouse::Button _button);
		bool IsActive(sf::Mouse::Button _button);
		bool IsReleased(sf::Mouse::Button _button);
		Ir::InputState GetState(sf::Mouse::Button _button);

		bool IsWithinArea(Ir::Vector _top_left, Ir::Vector _size);

		Ir::Vector GetPosition();
	}
}

#endif // IRIDIUM_INPUT_MOUSE_HPP_