#ifndef IRIDIUM_STATE_HPP_
#define IRIDIUM_STATE_HPP_

#include <typeinfo>

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"
#include "Iridium/state_machine.hpp"
#include "Iridium/state.inl"

namespace Ir {
	/// @brief Core state machine state class for main game logic.
	/// All states in use should derive from this one, using the IRIDIUM_STATE_CLASS macro.
	/// Ideally, no resources should be initialized during construction; everything should be done in OnInitialize() instead.
	class State {
	private:
		
	public:
		State() = default;
		~State() = default;

		virtual void OnInitialize() = 0; /// Fires upon initializing the state, initialize all resources here
		virtual void OnReceiveEvent(const sf::Event& _e) = 0; /// Fires first on every frame
		virtual void OnUpdate(Ir::ApplicationWindow& _window) = 0; /// Fires on every frame, after polling system events
		virtual void OnRender(Ir::ApplicationWindow& _window) = 0; /// Fires on every frame upon rendering
		virtual void OnEnd() = 0; /// Fires upon changing states, destroy allocated resources here
	};
}

#endif // IRIDIUM_STATE_HPP_