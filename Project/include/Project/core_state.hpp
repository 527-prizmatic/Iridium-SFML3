#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"
#include "Iridium/rendering/shapes.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() {
		rec_ = std::make_unique<ir::render::Rectangle>();
		rec_->setCorners(ir::Vector(100.f, 100.f), ir::Vector(150.f, 150.f));
		rec_->setColor(sf::Color::Red);
		rec_->setMode(ir::render::Mode::WIREFRAME);
	}
	
	void onReceiveEvent(const sf::Event& event) {
		std::cout << "a";
		if (event.is<sf::Event::KeyReleased>()) {
			if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			}
		}
	}

	void onUpdate() {
		ir::Vector pos = rec_->getPosition();
		pos.x += 100.f * context_->deltaTime();
		rec_->setPosition(context_->mouseInput->getCursorPosition());
	}

	void onRender() {
		context_->appWindow->render(*rec_);
	}
		
	void onEnd() { }

private:
	std::unique_ptr<ir::render::Rectangle> rec_;
};

#endif // PROJECT_TESTSTATE_HPP_