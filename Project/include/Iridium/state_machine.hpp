#ifndef IRIDIUM_STATEMACHINE_HPP_
#define IRIDIUM_STATEMACHINE_HPP_

#include "Iridium/libraries.hpp"

namespace ir {
	class State;
	class ApplicationWindow;

	/// @brief Verifies that the type is a correctly implemented derivative of Ir::State.
	template <typename T>
	concept StateClass = requires {
		std::is_base_of<ir::State, T>::value;
		{ T::getStateName() } -> std::same_as<std::string>;
	};

	class StateMachine {
	public:
		StateMachine();

		/// @brief Queues loading of the state with the given name, to be loaded upon the start of the next frame.
		/// @return Whether the state was successfully queued
		/// @deprecated Cumbersome and error-prone due to subtleties of std::type_info.
		/// Use the templated version instead.
		[[deprecated]] bool loadState(std::string name);

		/// @brief Queues loading of the state with the given type, to be loaded upon the start of the next frame.
		/// @brief If the state did not exist already, it is registered, allowing to perform lazy initialization if the user wishes.
		template <StateClass T> void loadState() {
			registerState<T>();
			nextState_ = T::getStateName();
		}

		/// @brief Performs initialization for the currently active state.
		void initialize();

		/// @brief Collects events for the given application window, and sends them to the currently active state for processing.
		void handleEvents(ir::ApplicationWindow& window);

		/// @brief Performs frame updates for the currently active state.
		void update(ir::ApplicationWindow& window);

		/// @brief Performs rendering operations for the currently active state.
		void render(ir::ApplicationWindow& window);

		/// @brief Calls resource destruction functions for the currently active state.
		void unload();

		/// @brief Registers a state of the given type into the state machine.
		template <StateClass T> bool registerState() {
			if (availableStates_.contains(T::ir_getStateName()))
				return false;

			availableStates_[T::ir_getStateName()] = std::make_shared<T>();
			std::dynamic_pointer_cast<T>(availableStates_[T::ir_getStateName()])->ir_setStateMachine(this);
			std::cout << "Registered state " << T::ir_getStateName() << std::endl;
			return true;
		}

		/// @return type_info name of the currently active state.
		/// @note A return value of "__none" means the state machine was not initialized yet.
		/// @attention type_info slightly obfuscates type names, pay attention to this if doing manual type name comparison.
		/// Prefer using getStateName() instead of writing type names manually in such comparisons.
		std::string getCurrentStateName() {
			return currentState_;
		}

		void requestExit() { requestedExit_ = true; }
		bool hasRequestedExit() { return requestedExit_; }

	private:
		std::map<std::string, std::shared_ptr<ir::State>> availableStates_; ///< Storage for available states
		std::string currentState_; ///< Name of the currently active state
		std::optional<std::string> nextState_; ///< Name of the state to be loaded upon starting the next frame

		bool requestedExit_ { false };
	};
}

#endif // IRIDIUM_STATEMACHINE_HPP_