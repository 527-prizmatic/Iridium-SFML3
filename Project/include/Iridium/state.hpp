#ifndef IRIDIUM_STATE_HPP_
#define IRIDIUM_STATE_HPP_

#include <typeinfo>

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"
#include "Iridium/state_machine.hpp"
#include "Iridium/state.inl"

namespace iridium {
	/// @brief Core state machine state class for main game logic.
	/// All states in use should derive from this one, using the IRIDIUM_STATE_CLASS macro.
	/// Ideally, no resources should be initialized during construction; everything should be done in onInitialize() instead.
	class State {
	private:
		
	public:
		State() = default;
		~State() = default;

		virtual void onInitialize() = 0; /// Fires upon initializing the state, initialize all resources here
		virtual void onReceiveEvent(const sf::Event& e) = 0; /// Fires first on every frame
		virtual void onUpdate(iridium::ApplicationWindow& window) = 0; /// Fires on every frame, after polling system events
		virtual void onRender(iridium::ApplicationWindow& window) = 0; /// Fires on every frame upon rendering
		virtual void onEnd() = 0; /// Fires upon changing states, destroy allocated resources here
	};
}

#endif // IRIDIUM_STATE_HPP_