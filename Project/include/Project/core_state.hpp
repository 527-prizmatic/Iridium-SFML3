#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() { }
	
	void onReceiveEvent(const sf::Event& event) {
		std::cout << "a";
		if (event.is<sf::Event::KeyReleased>()) {
			if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			}
		}
	}

	void onUpdate(ir::ApplicationWindow& window) { }

	void onRender(ir::ApplicationWindow& window) { }
		
	void onEnd() { }
};

#endif // PROJECT_TESTSTATE_HPP_