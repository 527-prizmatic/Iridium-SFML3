#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"

IRIDIUM_STATE_CLASS(CoreState)
public:
	void onInitialize() override { }
	
	void onReceiveEvent(const sf::Event& _e) override { }

	void onUpdate(iridium::ApplicationWindow& _window) override { }

	void onRender(iridium::ApplicationWindow& _window) override { }
		
	void onEnd() override { }
};

#endif // PROJECT_TESTSTATE_HPP_