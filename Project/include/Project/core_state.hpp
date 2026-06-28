#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/text.hpp"

#include "Iridium/assets/asset_manager.hpp"
#include "Iridium/assets/sound_manager.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() {
		ir::render::Text::loadModels();

		rec_ = std::make_unique<ir::render::Rectangle>();
		rec_->setCorners(ir::Vector(100.f, 100.f), ir::Vector(150.f, 150.f));
		rec_->setColor(sf::Color::Red);
		rec_->setMode(ir::render::Mode::WIREFRAME);

		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();
	//	modelRenderer_->setModel(ir::render::Model::testTriangle());
		modelRenderer_->setModel(ir::render::Model::loadFromFile("..\\text\\text_g_lower"));
		modelRenderer_->setScale(10.f);

		text_ = std::make_unique<ir::render::Text>();
		text_->setColor(sf::Color::Green);
	//	text_->setString("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		text_->setPosition(ir::Vector{ 10.f, 10.f });
		text_->setScale(3.f);

		sfx_ = context_->assetManager->registerSound("linnk.wav");
		music1_ = context_->assetManager->registerMusic("bonk.ogg");
		music2_ = context_->assetManager->registerMusic("capaphonk.ogg");
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
			auto code = event.getIf<sf::Event::KeyReleased>()->code;
			if (code == sf::Keyboard::Key::Escape) {
				meta_exit();
			}
			else if (code == sf::Keyboard::Key::Numpad1) {
				context_->assetManager->playMusic(music1_);
			}
			else if (code == sf::Keyboard::Key::Numpad2) {
				context_->assetManager->playMusic(music2_);
			}
			else if (code == sf::Keyboard::Key::Numpad4) {
				context_->assetManager->pauseMusic(music1_);
			}
			else if (code == sf::Keyboard::Key::Numpad5) {
				context_->assetManager->pauseMusic(music2_);
			}
			else if (code == sf::Keyboard::Key::Numpad7) {
				context_->assetManager->stopMusic(music1_);
			}
			else if (code == sf::Keyboard::Key::Numpad8) {
				context_->assetManager->stopMusic(music2_);
			}
			else {
				modelRenderer_->setAngle(modelRenderer_->getAngle() + ir::math::pi * .1f);
				LOG_INFO(std::to_string(modelRenderer_->getAngle()));

				context_->soundManager->playSound(sfx_);
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
		text_->render(*context_->vertexRenderer);
	}
		
	void onEnd() { }

private:
	std::unique_ptr<ir::render::Rectangle> rec_;
	std::unique_ptr<ir::render::ModelRenderer> modelRenderer_;
	std::unique_ptr<ir::render::Text> text_;

	ir::SoundHandle sfx_ {};

	ir::MusicHandle music1_ {};
	ir::MusicHandle music2_ {};
};

#endif // PROJECT_TESTSTATE_HPP_