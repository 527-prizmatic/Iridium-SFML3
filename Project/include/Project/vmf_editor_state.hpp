#ifndef PROJECT_VMF_STATE_HPP_
#define PROJECT_VMF_STATE_HPP_

#include "Iridium/state.hpp"

#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/text.hpp"

#include "Project/vmf_editor/draw_area.hpp"
#include "Project/vmf_editor/text_button.hpp"
#include "Project/vmf_editor/icon_button.hpp"
#include "Project/vmf_editor/toolbar.hpp"
#include "Project/vmf_editor/editor_model.hpp"

#include "Project/vmf_editor/tool_button_factory.hpp"

class VmfEditorState : public ir::StateBase<VmfEditorState> {
public:
	void onInitialize() {
		vmfContext_ = std::make_unique<vmf::Context>();

		editorModel_ = std::make_unique<vmf::EditorModel>(&*vmfContext_);
		
		drawArea_ = std::make_unique<vmf::DrawArea>(&*vmfContext_);
		vmfContext_->posOffset = context_->appWindow->getSize() * .5f / vmfContext_->zoomFactor;

		toolbarTop = std::make_unique<vmf::Toolbar>(&*vmfContext_);
		toolbarTop->setPosition(ir::Vector { 2.f, 2.f });
		toolbarTop->setSize(ir::Vector { 1276.f, 46.f });
		toolbarTop->setButtonSize(160.f);

		toolbarBottom = std::make_unique<vmf::Toolbar>(&*vmfContext_);
		toolbarBottom->setPosition(ir::Vector { 2.f, 672.f });
		toolbarBottom->setSize(ir::Vector { 1276.f, 46.f });
		toolbarBottom->setButtonSize(42.f);

		toolbarBottom->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_point", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::POINT; }, sf::Color::Green)));
		toolbarBottom->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_line", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::LINE; }, sf::Color::Cyan)));
		toolbarBottom->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_tri", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::TRIANGLE; }, sf::Color::Blue)));

		/// @todo This could probably use of a factory
		/*
		{
			auto buttonDiscard = std::make_unique<vmf::TextButton>(&*vmfContext_);
			buttonDiscard->setLabel("test");
			buttonDiscard->setLabelScale(2.f);
			buttonDiscard->setFunction([&](vmf::Context* context){ context->registerEvent(vmf::UserEvent::DEBUG); });
			buttonDiscard->setColors(sf::Color::Blue, sf::Color::White);
			buttonDiscard->setIsTransparent(true);
			toolbarTop->addButton(std::move(buttonDiscard));
		}
		
		{
			auto buttonDiscard = std::make_unique<vmf::TextButton>(&*vmfContext_);
			buttonDiscard->setLabel("save");
			buttonDiscard->setLabelScale(2.f);
			buttonDiscard->setFunction([&](vmf::Context* context){ context->registerEvent(vmf::UserEvent::MODEL_SAVE); });
			buttonDiscard->setColors(sf::Color::Green, sf::Color::White);
			buttonDiscard->setIsTransparent(true);
			toolbarTop->addButton(std::move(buttonDiscard));
		}
		*/
		{
			auto buttonDiscard = std::make_unique<vmf::TextButton>(&*vmfContext_);
			buttonDiscard->setLabel("discard");
			buttonDiscard->setLabelScale(2.f);
			buttonDiscard->setFunction([&](vmf::Context* context){ context->registerEvent(vmf::UserEvent::MODEL_DISCARD); });
			buttonDiscard->setColors(sf::Color::Red, sf::Color::White);
			buttonDiscard->setIsTransparent(true);
			toolbarTop->addButton(std::move(buttonDiscard));
		}
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
			auto e = event.getIf<sf::Event::KeyReleased>();

			if (e->code == sf::Keyboard::Key::Escape) {
				meta_exit();
			} 
			if (e->control) {
				
			} else if (e->code == sf::Keyboard::Key::Enter && e->shift) {
				editorModel_->save("square");
			}

		} else if (event.is<sf::Event::KeyPressed>()) {
			auto e = event.getIf<sf::Event::KeyPressed>();
			drawArea_->processKeyboardInput(e);
			editorModel_->processKeyboardInput(e);
			
		} else if (event.is<sf::Event::MouseWheelScrolled>()) {
			auto e = event.getIf<sf::Event::MouseWheelScrolled>();
			drawArea_->zoom(e->delta, context_->mouseInput->getCursorPosition());
		}
	}

	void onUpdate() {
		bool canDraw = true;
		if (toolbarTop->processMouseInput(context_->mouseInput) ||
			toolbarBottom->processMouseInput(context_->mouseInput)) {
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
			editorModel_->clear();

			LOG_INFO("Discarded model");
		} else if (evt == vmf::UserEvent::COMPONENT_VALIDATE) {
			editorModel_->addComponent(vmfContext_->inputToComponent());
			vmfContext_->vertexList.clear();

			LOG_INFO("Component input validated");
		}
	}

	void onRender() {
		drawArea_->render(*context_->vertexRenderer, context_->mouseInput->getCursorPosition());
		editorModel_->render(*context_->vertexRenderer);
		toolbarTop->render(*context_->vertexRenderer);
		toolbarBottom->render(*context_->vertexRenderer);
	}
		
	void onEnd() {

	}

private:
	sf::Vector2i clickPos_ { 128, 128 };
	ir::Vector clickPosFloat_ { 0.f, 0.f };

	std::unique_ptr<vmf::Context> vmfContext_;
	
	std::unique_ptr<vmf::DrawArea> drawArea_;
	std::unique_ptr<vmf::EditorModel> editorModel_;

	std::unique_ptr<vmf::Toolbar> toolbarTop;
	std::unique_ptr<vmf::Toolbar> toolbarBottom;
};

#endif // PROJECT_VMF_STATE_HPP_