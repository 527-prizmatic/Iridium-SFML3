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
		/// @return Whether the state was successfully queued
		template <StateClass T> bool LoadState() {
			if (this->m_availableStates.contains(T::GetStateName())) {
				this->m_nextState = T::GetStateName();
				return true;
			}
			else
				return false;
		}

		/// @brief Performs initialization for the currently active state.
		void Initialize();

		/// @brief Collects events for the given application window, and sends them to the currently active state for processing.
		void HandleEvents(Ir::ApplicationWindow& _window);

		/// @brief Performs frame updates for the currently active state.
		void Update();

		/// @brief Performs rendering operations for the currently active state.
		void Render(Ir::ApplicationWindow& _window);

		/// @brief Calls resource destruction functions for the currently active state.
		void Unload();

		template <StateClass T> bool RegisterState() {
			if (this->m_availableStates.contains(T::GetStateName()))
				return false;

			this->m_availableStates[T::GetStateName()] = std::make_shared<T>();
			std::dynamic_pointer_cast<T>(this->m_availableStates[T::GetStateName()])->SetStateMachine(this);
			return true;
		}

		std::string GetCurrentStateName() {
			return this->m_currentState;
		}

	private:
		std::map<std::string, std::shared_ptr<Ir::State>> m_availableStates; ///< Storage for available states
		std::string m_currentState; ///< Name of the currently active state
		std::optional<std::string> m_nextState; ///< Name of the state to be loaded upon starting the next frame
	};
}

#endif // IRIDIUM_STATEMACHINE_HPP_