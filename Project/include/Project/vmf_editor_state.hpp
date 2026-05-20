#ifndef PROJECT_VMF_STATE_HPP_
#define PROJECT_VMF_STATE_HPP_

#include "Iridium/state.hpp"

class VmfEditorState : public ir::StateBase<VmfEditorState> {

public:
	void onInitialize() {
		editingModel_ = std::make_unique<ir::render::Model>();
		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
			if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Left) {
				offsetPos_.x += 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Right) {
				offsetPos_.x -= 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Up) {
				offsetPos_.y += 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Down) {
				offsetPos_.y -= 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->control) {
				if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Z) {
					editingModel_->popLastComponent();
				} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::D) {
					editingModel_ = std::make_unique<ir::render::Model>();
				}
			}

			else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Enter && event.getIf<sf::Event::KeyReleased>()->shift) {
				static char id { 'a' };
				std::string filename { "text_" };
				filename.push_back(id);
				std::ofstream stream(filename + "_lower.vmf", std::ios::binary);
				if (!stream.fail()) {
					for (size_t i = 0; i < editingModel_->getComponentCount(); i++) {
						auto cmp = editingModel_->getComponent(i);
						stream.write(reinterpret_cast<char*>(&cmp.type), 1);
						for (int j = 0; j <= static_cast<int>(cmp.type); j++) {
							stream.write(reinterpret_cast<char*>(&cmp.vertices[j]), sizeof(ir::render::Vertex));
						}
					}
					stream.close();
				}
				id++;
			}

		} else if (event.is<sf::Event::MouseWheelScrolled>()) {
			float delta = event.getIf<sf::Event::MouseWheelScrolled>()->delta;
			zoomFactor_ *= std::powf(1.1f, delta);
			offsetPos_ /= std::powf(1.1f, delta);
			offsetPos_.x = static_cast<int>(offsetPos_.x);
			offsetPos_.y = static_cast<int>(offsetPos_.y);
		}
	}

	void onUpdate() {
		if (context_->mouseInput->isPressed(sf::Mouse::Button::Left)) {
			clickPosFloat_ = context_->mouseInput->getCursorPosition();
			ir::Vector v = clickPosFloat_ + ir::Vector(128.f, 128.f) * zoomFactor_;
			v -= offsetPos_ * zoomFactor_;
			clickPos_.x = static_cast<int>(v.x / zoomFactor_) - 128;
			clickPos_.y = static_cast<int>(v.y / zoomFactor_) - 128;
		}

		if (context_->mouseInput->isReleased(sf::Mouse::Button::Left)) {
			clickPosFloat_ = context_->mouseInput->getCursorPosition();
			ir::Vector v = clickPosFloat_ + ir::Vector(128.f, 128.f) * zoomFactor_;
			v -= offsetPos_ * zoomFactor_;
			int x = static_cast<int>(v.x / zoomFactor_) - 128;
			int y = static_cast<int>(v.y / zoomFactor_) - 128;

			ir::render::Vertex v1(clickPos_.x, clickPos_.y, sf::Color::White);
			ir::render::Vertex v2(x, y, sf::Color::White);

			editingModel_->addComponent(ir::render::Component(v1, v2));
		}
	}

	void onRender() {

		/// Draw pixel grid
		context_->vertexRenderer->reset(sf::PrimitiveType::Lines);
		for (int i = -128; i < 128; i++) {
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(-128.f * zoomFactor_, i * zoomFactor_), sf::Color(255u, 255u, 255u, 16u));
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(128.f * zoomFactor_, i * zoomFactor_), sf::Color(255u, 255u, 255u, 16u));
			
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(i * zoomFactor_, -128.f * zoomFactor_), sf::Color(255u, 255u, 255u, 16u));
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(i * zoomFactor_, 128.f * zoomFactor_), sf::Color(255u, 255u, 255u, 16u));
		}

		for (int i = -128; i < 128; i += 2) {
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(-128.f * zoomFactor_, i * zoomFactor_), sf::Color(192u, 255u, 255u, 24u));
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(128.f * zoomFactor_, i * zoomFactor_), sf::Color(192u, 255u, 255u, 24u));
			
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(i * zoomFactor_, -128.f * zoomFactor_), sf::Color(192u, 255u, 255u, 24u));
			context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(i * zoomFactor_, 128.f * zoomFactor_), sf::Color(192u, 255u, 255u, 24u));
		}
		
		context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(-128.f * zoomFactor_, 0.f), sf::Color::Red);
		context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(128.f * zoomFactor_, 0.f), sf::Color::Red);
		
		context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(0.f, -128.f * zoomFactor_), sf::Color::Red);
		context_->vertexRenderer->addPoint(offsetPos_ * zoomFactor_ + ir::Vector(0.f, 128.f * zoomFactor_), sf::Color::Red);
		
		context_->vertexRenderer->flush();

		modelRenderer_->setModel(*editingModel_);
		modelRenderer_->setScale(zoomFactor_);
		modelRenderer_->setPosition((offsetPos_ + ir::Vector(.5f, .5f)) * zoomFactor_);
		modelRenderer_->render(*context_->vertexRenderer);

		if (context_->mouseInput->isActive(sf::Mouse::Button::Left)) {
			context_->vertexRenderer->reset(sf::PrimitiveType::Lines);
			context_->vertexRenderer->addPoint(clickPosFloat_, sf::Color::Yellow);
			context_->vertexRenderer->addPoint(context_->mouseInput->getCursorPosition(), sf::Color::Yellow);
			context_->vertexRenderer->flush();
		}
	}
		
	void onEnd() {

	}

private:
	float zoomFactor_ { 10.f };
	ir::Vector offsetPos_ { 0.f, 0.f };

	sf::Vector2i clickPos_ { 128, 128 };
	ir::Vector clickPosFloat_ { 0.f, 0.f };

	std::unique_ptr<ir::render::Model> editingModel_;
	std::unique_ptr<ir::render::ModelRenderer> modelRenderer_;
};




#endif // PROJECT_VMF_STATE_HPP_