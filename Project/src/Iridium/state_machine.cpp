#include "Iridium/state_machine.hpp"
#include "Iridium/state.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/time.hpp"

namespace Ir {
	namespace _priv {
		const std::string g_nullStateName = "__none";
	}

	StateMachine::StateMachine() {
		this->m_currentState = Ir::_priv::g_nullStateName;
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
			if (this->m_currentState != Ir::_priv::g_nullStateName)
				this->Unload();
			this->m_currentState = this->m_nextState.value();
			this->m_availableStates[this->m_currentState]->OnInitialize();
			this->m_nextState.reset();
		}
	}
	
	void StateMachine::HandleEvents(Ir::ApplicationWindow &_window) {
		if (!this->m_availableStates[this->m_currentState])
			throw Ir::Exceptions::BadStateID(this->m_currentState);

#ifdef USING_IMGUI
		ImGui::SFML::Update(_window.GetMouseCursorPosition(), sf::Vector2f{_window.GetSize()}, sf::seconds(Ir::Time::DeltaUnscaled()));
#endif

		while (const std::optional event = _window.PollNextEvent()) {
			this->m_availableStates[this->m_currentState]->OnReceiveEvent(event.value());
		}
	}
	
	void StateMachine::Update(Ir::ApplicationWindow& _window) {
		if (!this->m_availableStates[this->m_currentState])
			throw Ir::Exceptions::BadStateID(this->m_currentState);

		this->m_availableStates[this->m_currentState]->OnUpdate(_window);
	}
	
	void StateMachine::Render(Ir::ApplicationWindow &_window) {
		if (!this->m_availableStates[this->m_currentState])
			throw Ir::Exceptions::BadStateID(this->m_currentState);

		_window.Clear(sf::Color::Black);
		this->m_availableStates[this->m_currentState]->OnRender(_window);

#ifdef USING_IMGUI
		ImGui::SFML::Render();
#endif
		_window.Flush();
	}
	
	void StateMachine::Unload() {
		if (!this->m_availableStates[this->m_currentState])
			throw Ir::Exceptions::BadStateID(this->m_currentState);

		this->m_availableStates[this->m_currentState]->OnEnd();
	}	
}