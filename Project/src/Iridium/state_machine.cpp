#include "Iridium/state_machine.hpp"
#include "Iridium/state.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {
	namespace detail {
		const std::string g_nullStateName = "__none";
	}

	StateMachine::StateMachine() {
		currentState_ = ir::detail::g_nullStateName;
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
			if (currentState_ != ir::detail::g_nullStateName)
				unload();
			currentState_ = nextState_.value();
			availableStates_.at(currentState_).onInitialize();
			nextState_.reset();
		}
	}
	
	void StateMachine::handleEvents(ir::ApplicationWindow& window) {
		if (!availableStates_.contains(currentState_))
			throw ir::Exceptions::BadStateID(currentState_);

		while (const std::optional event = window.pollNextEvent()) {
			availableStates_.at(currentState_).onReceiveEvent(event.value());
		}
	}
	
	/// @todo Add GameClock ref argument, and propagate that change to states as well
	void StateMachine::update(ir::ApplicationWindow& window) {
		if (!availableStates_.contains(currentState_))
			throw ir::Exceptions::BadStateID(currentState_);

		availableStates_.at(currentState_).onUpdate(window);
	}
	
	void StateMachine::render(ir::ApplicationWindow &window) {
		if (!availableStates_.contains(currentState_))
			throw ir::Exceptions::BadStateID(currentState_);

		window.clear(sf::Color::Black);
		availableStates_.at(currentState_).onRender(window);
		window.flush();
	}
	
	void StateMachine::unload() {
		if (!availableStates_.contains(currentState_))
			throw ir::Exceptions::BadStateID(currentState_);

		availableStates_.at(currentState_).onEnd();
	}	
}