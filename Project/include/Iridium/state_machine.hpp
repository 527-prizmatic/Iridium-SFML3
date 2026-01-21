#ifndef IRIDIUM_STATEMACHINE_HPP_
#define IRIDIUM_STATEMACHINE_HPP_

#include "Iridium/libraries.hpp"

namespace Ir {
	class State;
	class ApplicationWindow;

	/// @brief Verifies that the type is a correctly implemented derivative of Ir::State.
	template <typename T>
	concept StateClass = requires {
		std::is_base_of<Ir::State, T>::value;
		{ T::GetStateName() } -> std::same_as<std::string>;
	};

	class StateMachine {
	public:
		StateMachine();

		/// @brief Queues loading of the state with the given name, to be loaded upon the start of the next frame.
		/// @return Whether the state was successfully queued
		/// @deprecated Cumbersome and error-prone due to subtleties of std::type_info.
		/// Use the templated version instead.
		[[deprecated]] bool LoadState(std::string _name);

		/// @brief Queues loading of the state with the given type, to be loaded upon the start of the next frame.
		/// @brief If the state did not exist already, it is registered, allowing to perform lazy initialization if the user wishes.
		template <StateClass T> void LoadState() {
			this->RegisterState<T>();
			this->m_nextState = T::GetStateName();
		}

		/// @brief Performs initialization for the currently active state.
		void Initialize();

		/// @brief Collects events for the given application window, and sends them to the currently active state for processing.
		void HandleEvents(Ir::ApplicationWindow& _window);

		/// @brief Performs frame updates for the currently active state.
		void Update(Ir::ApplicationWindow& _window);

		/// @brief Performs rendering operations for the currently active state.
		void Render(Ir::ApplicationWindow& _window);

		/// @brief Calls resource destruction functions for the currently active state.
		void Unload();

		/// @brief Registers a state of the given type into the state machine.
		template <StateClass T> bool RegisterState() {
			if (this->m_availableStates.contains(T::GetStateName()))
				return false;

			this->m_availableStates[T::GetStateName()] = std::make_shared<T>();
			std::dynamic_pointer_cast<T>(this->m_availableStates[T::GetStateName()])->SetStateMachine(this);
			std::cout << "Registered state " << T::GetStateName() << std::endl;
			return true;
		}

		/// @return type_info name of the currently active state.
		/// @note A return value of "__none" means the state machine was not initialized yet.
		/// @attention type_info slightly obfuscates type names, pay attention to this if doing manual type name comparison.
		///
		/// Prefer using GetStateName() instead of writing type names manually in such comparisons.
		std::string GetCurrentStateName() {
			return this->m_currentState;
		}

		void RequestExit() { this->m_requestedExit = true; }
		bool HasRequestedExit() { return this->m_requestedExit; }

	private:
		std::map<std::string, std::shared_ptr<Ir::State>> m_availableStates; ///< Storage for available states
		std::string m_currentState; ///< Name of the currently active state
		std::optional<std::string> m_nextState; ///< Name of the state to be loaded upon starting the next frame

		bool m_requestedExit { false };
	};
}

#endif // IRIDIUM_STATEMACHINE_HPP_