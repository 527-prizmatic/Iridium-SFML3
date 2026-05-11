#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"

IRIDIUM_STATE_CLASS(CoreState)
public:
	void onInitialize() override { }
	
	void onReceiveEvent(const sf::Event& event) override { }

	void onUpdate(ir::ApplicationWindow& window) override { }

	void onRender(ir::ApplicationWindow& window) override { }
		
	void onEnd() override { }
};

#endif // PROJECT_TESTSTATE_HPP_