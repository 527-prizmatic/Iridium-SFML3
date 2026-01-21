#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"

IRIDIUM_STATE_CLASS(CoreState)
public:
	void OnInitialize() override { }
	
	void OnReceiveEvent(const sf::Event& _e) override { }

	void OnUpdate(Ir::ApplicationWindow& _window) override { }

	void OnRender(Ir::ApplicationWindow& _window) override { }
		
	void OnEnd() override { }
};

#endif // PROJECT_TESTSTATE_HPP_