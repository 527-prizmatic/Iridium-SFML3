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
#include "Project/vmf_editor/color_picker.hpp"

#include "Project/vmf_editor/ui_button_factory.hpp"

class VmfEditorState : public ir::StateBase<VmfEditorState> {
public:
	void onInitialize() {
		vmfContext_ = std::make_unique<vmf::Context>();

		editorModel_ = std::make_unique<vmf::EditorModel>(&*vmfContext_);
		
		drawArea_ = std::make_unique<vmf::DrawArea>(&*vmfContext_);
		vmfContext_->posOffset = context_->appWindow->getSize() * .5f / vmfContext_->zoomFactor;

		toolbarTop_ = std::make_unique<vmf::Toolbar>(&*vmfContext_);
		toolbarTop_->setPosition(ir::Vector { 2.f, 2.f });
		toolbarTop_->setSize(ir::Vector { 1276.f, 36.f });
		toolbarTop_->setButtonSize(120.f);

		toolbarTop_->addButton(std::move(vmf::produceTextButton(&*vmfContext_, "Discard", vmf::UserEvent::MODEL_DISCARD, sf::Color::Red)));
		toolbarTop_->addButton(std::move(vmf::produceTextButton(&*vmfContext_, "Save", vmf::UserEvent::MODEL_SAVE, sf::Color::Green)));
		
		toolbarBottom_ = std::make_unique<vmf::Toolbar>(&*vmfContext_);
		toolbarBottom_->setPosition(ir::Vector { 2.f, 672.f });
		toolbarBottom_->setSize(ir::Vector { 1276.f, 46.f });
		toolbarBottom_->setButtonSize(42.f);

		toolbarBottom_->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_point", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::POINT; }, sf::Color::Green)));
		toolbarBottom_->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_line", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::LINE; }, sf::Color::Cyan)));
		toolbarBottom_->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_tri", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::TRIANGLE; }, sf::Color::Blue)));

		toolbarSave_ = std::make_unique<vmf::Toolbar>(&*vmfContext_);
		toolbarSave_->setPosition(ir::Vector { 2.f, 42.f });
		toolbarSave_->setSize(ir::Vector { 512.f, 36.f });
		toolbarSave_->setButtonSize(80.f);

		toolbarSave_->addButton(std::move(vmf::produceTextButton(&*vmfContext_, std::string{}, [](vmf::Context* context){}, sf::Color(192u, 192u, 192u))), 340.f);
		toolbarSave_->addButton(std::move(vmf::produceTextButton(&*vmfContext_, "Save", vmf::UserEvent::CONFIRM_MODEL_SAVE, sf::Color::Green)));
		toolbarSave_->addButton(std::move(vmf::produceTextButton(&*vmfContext_, "Cancel", vmf::UserEvent::CANCEL_MODEL_SAVE, sf::Color::Red)));

		rectOverlay_ = std::make_unique<ir::render::Rectangle>();
		rectOverlay_->setSize(1280.f, 720.f);
		rectOverlay_->setColor(sf::Color(0u, 0u, 0u, 64u));
		rectOverlay_->setMode(ir::render::Mode::SOLID);

		colorPicker_ = std::make_unique<vmf::ColorPicker>(&*vmfContext_);
		colorPicker_->setPosition(ir::Vector{ 2.f, 572.f });
	}
	
	void onReceiveEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyReleased>()) {
	//		auto e = event.getIf<sf::Event::KeyReleased>();


		}
		else if (event.is<sf::Event::KeyPressed>()) {
			auto e = event.getIf<sf::Event::KeyPressed>();

			if (e->code == sf::Keyboard::Key::Escape && vmfContext_->saveMode) {
				vmfContext_->registerEvent(vmf::UserEvent::CANCEL_MODEL_SAVE);
			} 

			if (e->control) {
				if (e->code == sf::Keyboard::Key::S) {
					vmfContext_->registerEvent(vmf::UserEvent::MODEL_SAVE);
				}
			}
			if (e->code == sf::Keyboard::Key::Escape && e->shift) {
				meta_exit();
			}

			drawArea_->processKeyboardInput(e);
			editorModel_->processKeyboardInput(e);
		}
		else if (event.is<sf::Event::TextEntered>()) {
			auto e = event.getIf<sf::Event::TextEntered>();
			vmf::TextButton* saveTextField_ = dynamic_cast<vmf::TextButton*>(toolbarSave_->getButton(0));
			std::string current = saveTextField_->getLabel();

			if (e->unicode == 13) {
				vmfContext_->registerEvent(vmf::UserEvent::CONFIRM_MODEL_SAVE);
			} else if (e->unicode == 8) {
				if (current.size() > 0) {
					current.pop_back();
				}
			}
			else {
				if (current.size() < 32) {
					current.push_back(e->unicode);
				}
			}

			saveTextField_->setLabel(current);
		}
		else if (event.is<sf::Event::MouseWheelScrolled>()) {
			auto e = event.getIf<sf::Event::MouseWheelScrolled>();
			drawArea_->zoom(e->delta, context_->mouseInput->getCursorPosition());
		}
	}

	void onUpdate() {
		if (!vmfContext_->saveMode) {
			bool canDraw = true;
			if (toolbarTop_->processMouseInput(context_->mouseInput) ||
				toolbarBottom_->processMouseInput(context_->mouseInput) ||
				colorPicker_->processMouseInput(context_->mouseInput)) {
				canDraw = false;
			}

			if (canDraw) {
				drawArea_->processMouseInput(context_->mouseInput);
			}
		}
		else {
			toolbarSave_->processMouseInput(context_->mouseInput);
		}

		while (vmfContext_->events.size() != 0) {
			processUserEvent(vmfContext_->popFirstEvent());
		}
	}

	void processUserEvent(vmf::UserEvent evt) {
		if (evt == vmf::UserEvent::DEBUG) {
			LOG_INFO("Button debug");

		}
		else if (evt == vmf::UserEvent::MODEL_SAVE) {
			LOG_WARN("Model save not yet implemented, debugging purposes only");

			vmfContext_->saveMode = true;
			dynamic_cast<vmf::TextButton*>(toolbarSave_->getButton(0))->setLabel("");

			LOG_INFO("Entering model save mode");

		}
		else if (evt == vmf::UserEvent::MODEL_DISCARD) {
			editorModel_->clear();
				vmfContext_->vertexList.clear();

			LOG_INFO("Discarded model");
		}
		else if (evt == vmf::UserEvent::COMPONENT_VALIDATE) {
			editorModel_->addComponent(vmfContext_->inputToComponent());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
				vmfContext_->vertexList.erase(vmfContext_->vertexList.begin());
			}
			else {
				vmfContext_->vertexList.clear();
			}

			LOG_INFO("Component input validated");
		}
		else if (evt == vmf::UserEvent::CONFIRM_MODEL_SAVE) {
			std::string_view filename = dynamic_cast<vmf::TextButton*>(toolbarSave_->getButton(0))->getLabel();
			if (filename.size() == 0) {
				filename = "model";
			}
			
			if (editorModel_->save(filename.data())) {
				LOG_INFO(std::string{"Model saved as "} + filename.data() + std::string{".vmf"});
			}
			else {
				LOG_ERROR(std::string{"Error trying to save model as "} + filename.data() + std::string{".vmf"});
			}

			vmfContext_->saveMode = false;
		}
		else if (evt == vmf::UserEvent::CANCEL_MODEL_SAVE) {
			vmfContext_->saveMode = false;

			LOG_INFO("File saving canceled");
		}
		else if (evt == vmf::UserEvent::ADD_CURRENT_TO_PALETTE) {
			colorPicker_->addToPalette();

			LOG_INFO("Added current color to palette");
		}
	}

	void onRender() {
		drawArea_->render(*context_->vertexRenderer, context_->mouseInput->getCursorPosition());
		editorModel_->render(*context_->vertexRenderer);
		toolbarTop_->render(*context_->vertexRenderer);
		toolbarBottom_->render(*context_->vertexRenderer);
		colorPicker_->render(*context_->vertexRenderer);

		if (vmfContext_->saveMode) {
			rectOverlay_->render(*context_->vertexRenderer);
			toolbarSave_->render(*context_->vertexRenderer);
		}
	}
		
	void onEnd() {

	}

private:
	sf::Vector2i clickPos_ { 128, 128 };
	ir::Vector clickPosFloat_ { 0.f, 0.f };

	std::unique_ptr<vmf::Context> vmfContext_;
	
	std::unique_ptr<vmf::DrawArea> drawArea_;
	std::unique_ptr<vmf::EditorModel> editorModel_;

	std::unique_ptr<vmf::Toolbar> toolbarTop_;
	std::unique_ptr<vmf::Toolbar> toolbarBottom_;
	std::unique_ptr<vmf::Toolbar> toolbarSave_;

	std::unique_ptr<vmf::ColorPicker> colorPicker_;

	std::unique_ptr<ir::render::Rectangle> rectOverlay_;
};

#endif // PROJECT_VMF_STATE_HPP_