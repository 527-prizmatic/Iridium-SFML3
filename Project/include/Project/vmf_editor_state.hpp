#ifndef PROJECT_VMF_STATE_HPP_
#define PROJECT_VMF_STATE_HPP_

#include "Iridium/state.hpp"
#include "Project/vmf_editor/draw_area.hpp"
#include "Project/vmf_editor/ui_button.hpp"

class VmfEditorState : public ir::StateBase<VmfEditorState> {

public:
	void onInitialize() {
		vmfContext_ = std::make_unique<vmf::Context>();

		editingModel_ = std::make_unique<ir::render::Model>();
		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();

		drawArea_ = std::make_unique<vmf::DrawArea>(&*vmfContext_);

		buttonDiscard_ = std::make_unique<vmf::UiButton>(&*vmfContext_);
		buttonDiscard_->setDimensions(ir::Vector { 600.f, 600.f }, ir::Vector { 100.f, 40.f });
		buttonDiscard_->setLabel("test");
		buttonDiscard_->setLabelScale(2.f);
		buttonDiscard_->setFunction([&](vmf::Context* context){ context->registerEvent(vmf::UserEvent::DEBUG); });
		buttonDiscard_->setColors(sf::Color::Red, sf::Color::White);
		buttonDiscard_->setIsTransparent(true);
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
			auto e = event.getIf<sf::Event::KeyReleased>();

			if (e->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			} 
			if (e->control) {
				if (e->code == sf::Keyboard::Key::Z) {
					editingModel_->popLastComponent();
				} else if (e->code == sf::Keyboard::Key::D) {
					editingModel_ = std::make_unique<ir::render::Model>();
				}
			} else if (e->code == sf::Keyboard::Key::Enter && e->shift) {
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

		} else if (event.is<sf::Event::KeyPressed>()) {
			auto e = event.getIf<sf::Event::KeyPressed>();
			drawArea_->processKeyboardInput(e);
			
		} else if (event.is<sf::Event::MouseWheelScrolled>()) {
			auto e = event.getIf<sf::Event::MouseWheelScrolled>();
			drawArea_->zoom(e->delta);
			modelRenderer_->setScale(vmfContext_->zoomFactor);
		}
		
	}

	void onUpdate() {
		bool canDraw = true;
		if (buttonDiscard_->processMouseInput(context_->mouseInput)) {
			canDraw = false;
		}

		if (canDraw) {
			drawArea_->processMouseInput(context_->mouseInput);
		}

		/// @todo Move into a proper event processor
		while (vmfContext_->events.size() != 0) {
			processUserEvent(vmfContext_->popFirstEvent());
		}
	}

	void processUserEvent(vmf::UserEvent evt) {
		if (evt == vmf::UserEvent::DEBUG) {
			LOG_INFO("Button debug");

		} else if (evt == vmf::UserEvent::MODEL_SAVE) {
			LOG_WARN("Model save not yet implemented, debugging purposes only");

			LOG_INFO("Saved model");

		} else if (evt == vmf::UserEvent::MODEL_DISCARD) {
			editingModel_ = std::make_unique<ir::render::Model>();

			LOG_INFO("Discarded model");
		}
	}

	void onRender() {
		drawArea_->render(*context_->vertexRenderer);

		modelRenderer_->setModel(*editingModel_);
		modelRenderer_->setPosition((vmfContext_->posOffset + ir::Vector(.5f, .5f)) * vmfContext_->zoomFactor);
		modelRenderer_->render(*context_->vertexRenderer);

		buttonDiscard_->render(*context_->vertexRenderer);

		/*
		if (vmfContext_->vertexList.size() == 1) {
			context_->vertexRenderer->reset(sf::PrimitiveType::Lines);
			context_->vertexRenderer->addPoint(clickPosFloat_, sf::Color::Yellow);
			context_->vertexRenderer->addPoint(context_->mouseInput->getCursorPosition(), sf::Color::Yellow);
			context_->vertexRenderer->flush();
		}
		*/
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

	std::unique_ptr<vmf::UiButton> buttonDiscard_;
};




#endif // PROJECT_VMF_STATE_HPP_