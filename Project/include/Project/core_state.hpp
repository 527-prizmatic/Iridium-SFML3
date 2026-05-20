#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model_renderer.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() {
		rec_ = std::make_unique<ir::render::Rectangle>();
		rec_->setCorners(ir::Vector(100.f, 100.f), ir::Vector(150.f, 150.f));
		rec_->setColor(sf::Color::Red);
		rec_->setMode(ir::render::Mode::WIREFRAME);

		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();
	//	modelRenderer_->setModel(ir::render::Model::testTriangle());
		modelRenderer_->setModel(ir::render::Model::loadFromFile("text"));
		modelRenderer_->setScale(10.f);
	}
	
	void onReceiveEvent(const sf::Event& event) {
		std::cout << "a";
		if (event.is<sf::Event::KeyReleased>()) {
			if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			} else {
				modelRenderer_->setAngle(modelRenderer_->getAngle() + ir::math::pi * .1f);
				std::cout << modelRenderer_->getAngle() << std::endl;
			}
		}
	}

	void onUpdate() {
		ir::Vector pos = modelRenderer_->getPosition();
		pos.x += 100.f * context_->deltaTime();
		modelRenderer_->setPosition(context_->mouseInput->getCursorPosition());
	}

	void onRender() {
		modelRenderer_->render(*context_->vertexRenderer);
	}
		
	void onEnd() { }

private:
	std::unique_ptr<ir::render::Rectangle> rec_;
	std::unique_ptr<ir::render::ModelRenderer> modelRenderer_;
};

#endif // PROJECT_TESTSTATE_HPP_