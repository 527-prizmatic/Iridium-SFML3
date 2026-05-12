#include "Iridium/state_machine.hpp"
#include "Iridium/state.hpp"
#include "Iridium/exceptions.hpp"

namespace iridium {
	namespace detail {
		const std::string g_nullStateName = "__none";
	}

	StateMachine::StateMachine() {
		currentState_ = iridium::detail::g_nullStateName;
	}

	bool StateMachine::loadState(std::string _name) {
		if (availableStates_.contains(_name)) {
			nextState_ = _name;
			return true;
		}
		else
			return false;
	}

	void StateMachine::initialize() {
		if (nextState_.has_value()) {
			if (currentState_ != iridium::detail::g_nullStateName)
				unload();
			currentState_ = nextState_.value();
			availableStates_[currentState_]->onInitialize();
			nextState_.reset();
		}
	}
	
	void StateMachine::handleEvents(iridium::ApplicationWindow &_window) {
		if (!availableStates_[currentState_])
			throw iridium::Exceptions::BadStateID(currentState_);

		while (const std::optional event = _window.PollNextEvent()) {
			availableStates_[currentState_]->onReceiveEvent(event.value());
		}
	}
	
	void StateMachine::update(iridium::ApplicationWindow& _window) {
		if (!availableStates_[currentState_])
			throw iridium::Exceptions::BadStateID(currentState_);

		availableStates_[currentState_]->onUpdate(_window);
	}
	
	void StateMachine::render(iridium::ApplicationWindow &_window) {
		if (!availableStates_[currentState_])
			throw iridium::Exceptions::BadStateID(currentState_);

		_window.clear(sf::Color::Black);
		availableStates_[currentState_]->onRender(_window);
		_window.Flush();
	}
	
	void StateMachine::unload() {
		if (!availableStates_[currentState_])
			throw iridium::Exceptions::BadStateID(currentState_);

		availableStates_[currentState_]->onEnd();
	}	
}