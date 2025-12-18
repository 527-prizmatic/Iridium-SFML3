#include "Iridium/state_machine.hpp"
#include "Iridium/state.hpp"

namespace Ir {
	StateMachine::StateMachine() {
		this->m_currentState = "__none";
	}

	bool StateMachine::LoadState(std::string _name) {
		if (this->m_availableStates.contains(_name)) {
			this->m_nextState = _name;
			return true;
		}
		else
			return false;
	}

	void StateMachine::Initialize() {
		if (this->m_nextState.has_value()) {
			this->Unload();
			this->m_currentState = this->m_nextState.value();
			this->m_availableStates[this->m_currentState]->OnInitialize();
			this->m_nextState.reset();
		}
	}
	
	void StateMachine::HandleEvents(Ir::ApplicationWindow &_window) {
		if (!this->m_availableStates[this->m_currentState])
			return;

		auto sfmlWindow = _window.GetSFMLWindow();
		if (auto lock = sfmlWindow.lock()) {
			while (const std::optional event = lock->pollEvent()) {
				this->m_availableStates[this->m_currentState]->OnReceiveEvent(event.value());
			}
		}
	}
	
	void StateMachine::Update() {
		if (!this->m_availableStates[this->m_currentState])
			return;

		this->m_availableStates[this->m_currentState]->OnUpdate();
	}
	
	void StateMachine::Render(Ir::ApplicationWindow &_window) {
		if (!this->m_availableStates[this->m_currentState])
			return;

		_window.Clear(sf::Color::Black);
		this->m_availableStates[this->m_currentState]->OnRender(_window);
		_window.Flush();
	}
	
	void StateMachine::Unload() {
		if (!this->m_availableStates[this->m_currentState])
			return;

		this->m_availableStates[this->m_currentState]->OnEnd();
	}	
}