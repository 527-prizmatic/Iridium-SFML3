#ifndef IRIDIUM_STATEMACHINE_HPP_
#define IRIDIUM_STATEMACHINE_HPP_

#include "Iridium/libraries.hpp"

namespace Ir {
	class State;
	class ApplicationWindow;

	template <typename T>
	concept StateClass = std::is_base_of<Ir::State, T>::value;

	template <typename T>
	concept FullyImplementedStateClass = requires {
		std::is_base_of<Ir::State, T>::value;
		{ T::GetStateName() } -> std::same_as<std::string>;
	};

	class StateMachine {
	public:
		StateMachine();

		bool LoadState(std::string _name);

		template <FullyImplementedStateClass T>
		bool LoadState() {
			if (this->m_availableStates.contains(T::GetStateName())) {
				this->m_nextState = T::GetStateName();
				return true;
			}
			else
				return false;
		}

		void Initialize();

		void HandleEvents(Ir::ApplicationWindow& _window);

		void Update();

		void Render(Ir::ApplicationWindow& _window);

		void Unload();

		template <FullyImplementedStateClass T> bool RegisterState() {
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
		std::map<std::string, std::shared_ptr<Ir::State>> m_availableStates;
		std::string m_currentState;
		std::optional<std::string> m_nextState;
	};
}

#endif // IRIDIUM_STATEMACHINE_HPP_