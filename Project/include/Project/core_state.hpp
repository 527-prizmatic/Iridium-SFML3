#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() { }
	
	void onReceiveEvent(const sf::Event& event) { std::cout <<"a";}

	void onUpdate(ir::ApplicationWindow& window) { }

	void onRender(ir::ApplicationWindow& window) { }
		
	void onEnd() { }
};

#endif // PROJECT_TESTSTATE_HPP_