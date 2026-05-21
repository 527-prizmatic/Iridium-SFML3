#ifndef PROJECT_VMF_STATE_HPP_
#define PROJECT_VMF_STATE_HPP_

#include "Iridium/state.hpp"
#include "Project/vmf_editor/draw_area.hpp"
#include "Project/vmf_editor/context.hpp"

class VmfEditorState : public ir::StateBase<VmfEditorState> {

public:
	void onInitialize() {
		vmfContext_ = std::make_unique<vmf::Context>();

		editingModel_ = std::make_unique<ir::render::Model>();
		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();

		drawArea_ = std::make_unique<vmf::DrawArea>(&*vmfContext_);
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
			if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Left) {
				vmfContext_->posOffset.x += 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Right) {
				vmfContext_->posOffset.x -= 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Up) {
				vmfContext_->posOffset.y += 2.f;
			} else if (event.getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Down) {
				vmfContext_->posOffset.y -= 2.f;
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
			vmfContext_->zoomFactor *= std::powf(1.1f, delta);
			vmfContext_->posOffset /= std::powf(1.1f, delta);
			vmfContext_->posOffset.x = static_cast<int>(vmfContext_->posOffset.x);
			vmfContext_->posOffset.y = static_cast<int>(vmfContext_->posOffset.y);
		}
	}

	void onUpdate() {
		if (context_->mouseInput->isPressed(sf::Mouse::Button::Left)) {
			clickPosFloat_ = context_->mouseInput->getCursorPosition();
			ir::Vector v = clickPosFloat_ + ir::Vector(128.f, 128.f) * vmfContext_->zoomFactor;
			v -= vmfContext_->posOffset * vmfContext_->zoomFactor;
			clickPos_.x = static_cast<int>(v.x / vmfContext_->zoomFactor) - 128;
			clickPos_.y = static_cast<int>(v.y / vmfContext_->zoomFactor) - 128;
		}

		if (context_->mouseInput->isReleased(sf::Mouse::Button::Left)) {
			clickPosFloat_ = context_->mouseInput->getCursorPosition();
			ir::Vector v = clickPosFloat_ + ir::Vector(128.f, 128.f) * vmfContext_->zoomFactor;
			v -= vmfContext_->posOffset * vmfContext_->zoomFactor;
			int x = static_cast<int>(v.x / vmfContext_->zoomFactor) - 128;
			int y = static_cast<int>(v.y / vmfContext_->zoomFactor) - 128;

			ir::render::Vertex v1(clickPos_.x, clickPos_.y, sf::Color::White);
			ir::render::Vertex v2(x, y, sf::Color::White);

			editingModel_->addComponent(ir::render::Component(v1, v2));
		}
	}

	void onRender() {
		drawArea_->render(*context_->vertexRenderer);

		modelRenderer_->setModel(*editingModel_);
		modelRenderer_->setScale(vmfContext_->zoomFactor);
		modelRenderer_->setPosition((vmfContext_->posOffset + ir::Vector(.5f, .5f)) * vmfContext_->zoomFactor);
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

	sf::Vector2i clickPos_ { 128, 128 };
	ir::Vector clickPosFloat_ { 0.f, 0.f };

	std::unique_ptr<ir::render::Model> editingModel_;
	std::unique_ptr<ir::render::ModelRenderer> modelRenderer_;
	std::unique_ptr<vmf::DrawArea> drawArea_;
	std::unique_ptr<vmf::Context> vmfContext_;
};




#endif // PROJECT_VMF_STATE_HPP_