#ifndef PROJECT_VMF_STATE_HPP_
#define PROJECT_VMF_STATE_HPP_

#include "Iridium/state.hpp"

#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/text.hpp"

#include "Iridium/vgui/element.hpp"
#include "Iridium/vgui/label.hpp"
#include "Iridium/vgui/input_field.hpp"

#include "Project/vmf_editor/draw_area.hpp"
#include "Project/vmf_editor/text_button.hpp"
#include "Project/vmf_editor/icon_button.hpp"
#include "Project/vmf_editor/toolbar.hpp"
#include "Project/vmf_editor/editor_model.hpp"

#include "Project/vmf_editor/title_bar.hpp"
#include "Project/vmf_editor/color_picker.hpp"
#include "Project/vmf_editor/save_popup.hpp"
#include "Project/vmf_editor/load_popup.hpp"

#include "Project/vmf_editor/ui_button_factory.hpp"

class VmfEditorState : public ir::StateBase<VmfEditorState> {
public:
	void onInitialize() {
		vmfContext_ = std::make_unique<vmf::Context>();

		editorModel_ = std::make_unique<vmf::EditorModel>(&*vmfContext_);
		
		drawArea_ = std::make_unique<vmf::DrawArea>(&*vmfContext_);
		vmfContext_->posOffset = context_->appWindow->getSize() * .5f / vmfContext_->zoomFactor;
		
		titleBar_ = std::make_unique<vmf::TitleBar>(&*vmfContext_, ir::Vector { 2.f, 2.f });
		savePopup_ = std::make_unique<vmf::SavePopup>(&*vmfContext_, ir::Vector { 2.f, 42.f });
		loadPopup_ = std::make_unique<vmf::LoadPopup>(&*vmfContext_, ir::Vector { 2.f, 42.f });

		toolbarBottom_ = std::make_unique<vmf::Toolbar>(&*vmfContext_);
		toolbarBottom_->setPosition(ir::Vector { 2.f, 672.f });
		toolbarBottom_->setSize(ir::Vector { 1276.f, 46.f });
		toolbarBottom_->setButtonSize(42.f);

		toolbarBottom_->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_point", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::POINT; }, sf::Color::Green)));
		toolbarBottom_->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_line", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::LINE; }, sf::Color::Cyan)));
		toolbarBottom_->addButton(std::move(vmf::produceToolButton(&*vmfContext_, "ui_tri", [&](vmf::Context* context){ context->drawingType = ir::render::Component::Type::TRIANGLE; }, sf::Color::Blue)));

		rectOverlay_ = std::make_unique<ir::render::Rectangle>();
		rectOverlay_->setSize(1280.f, 720.f);
		rectOverlay_->setColor(sf::Color(0u, 0u, 0u, 64u));
		rectOverlay_->setMode(ir::render::Mode::SOLID);

		colorPicker_ = std::make_unique<vmf::ColorPicker>(&*vmfContext_);
		colorPicker_->setPosition(ir::Vector{ 2.f, 552.f });
	}
	
	void onReceiveEvent(const sf::Event& event) {
		titleBar_->processEvent(event);
		savePopup_->processEvent(event);
		loadPopup_->processEvent(event);

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
				if (e->code == sf::Keyboard::Key::O) {
					vmfContext_->registerEvent(vmf::UserEvent::MODEL_LOAD);
				}
				if (e->code == sf::Keyboard::Key::N) {
					vmfContext_->registerEvent(vmf::UserEvent::MODEL_DISCARD);
				}
			}
			if (e->code == sf::Keyboard::Key::Escape && e->shift) {
				meta_exit();
			}

			drawArea_->processKeyboardInput(e);
			editorModel_->processKeyboardInput(e);
		}
		else if (event.is<sf::Event::TextEntered>()) {

		}
		else if (event.is<sf::Event::MouseWheelScrolled>()) {
			auto e = event.getIf<sf::Event::MouseWheelScrolled>();
			drawArea_->zoom(e->delta, context_->mouseInput->getCursorPosition());
		}
	}

	void onUpdate() {
		if (!vmfContext_->saveMode && !vmfContext_->loadMode) {
			bool canDraw = true;
			if (titleBar_->update(context_->mouseInput) ||
				toolbarBottom_->processMouseInput(context_->mouseInput) ||
				colorPicker_->processMouseInput(context_->mouseInput)) {
				canDraw = false;
			}

			if (canDraw) {
				drawArea_->processMouseInput(context_->mouseInput);
			}
		}
		else {
			if (vmfContext_->saveMode) {
				savePopup_->update(context_->mouseInput);
			}
			else if (vmfContext_->loadMode) {
				loadPopup_->update(context_->mouseInput);
			}
		}

		while (vmfContext_->events.size() != 0) {
			processUserEvent(vmfContext_->popFirstEvent());
		}
	}

	void processUserEvent(vmf::UserEvent evt) {
		switch (evt) {
			case vmf::UserEvent::DEBUG: {
				LOG_INFO("Button debug");
				break;
			}

			case vmf::UserEvent::MODEL_SAVE: {
				vmfContext_->saveMode = true;
				savePopup_->setValue("");
				savePopup_->focus();

				LOG_INFO("Entering model save mode");
				break;
			}

			case vmf::UserEvent::MODEL_LOAD: {
				vmfContext_->loadMode = true;
				loadPopup_->setValue("");
				loadPopup_->focus();
				loadPopup_->setColor(sf::Color::White);

				LOG_INFO("Entering model load mode");
				break;
			}

			case vmf::UserEvent::MODEL_DISCARD: {
				editorModel_->clear();
				vmfContext_->vertexList.clear();

				LOG_INFO("Discarded model");
				break;
			}

			case vmf::UserEvent::COMPONENT_VALIDATE: {
				editorModel_->addComponent(vmfContext_->inputToComponent());
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
					vmfContext_->vertexList.erase(vmfContext_->vertexList.begin());
				}
				else {
					vmfContext_->vertexList.clear();
				}

				LOG_INFO("Component input validated");
				break;
			}

			case vmf::UserEvent::CONFIRM_MODEL_SAVE: {
				std::string_view filename = savePopup_->getValue();
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
				break;
			}

			case vmf::UserEvent::CONFIRM_MODEL_LOAD: {
				std::string_view filename = loadPopup_->getValue();
				if (filename.size() == 0) {
					filename = "model";
				}
				
				try {
					editorModel_->load(filename.data());
					LOG_INFO(std::string{"Loaded model "} + filename.data() + std::string{".vmf"});
					vmfContext_->loadMode = false;
				}
				catch (ir::Exceptions::BadModelName& e) {
					LOG_ERROR(std::string{"Error trying to load model "} + filename.data() + std::string{".vmf"});
					loadPopup_->setColor(sf::Color::Red);
				}

				break;
			}
			
			case vmf::UserEvent::CANCEL_MODEL_SAVE: {
				vmfContext_->saveMode = false;

				LOG_INFO("File saving canceled");
				break;
			}

			case vmf::UserEvent::CANCEL_MODEL_LOAD: {
				vmfContext_->loadMode = false;

				LOG_INFO("File loading canceled");
				break;
			}

			case vmf::UserEvent::ADD_CURRENT_TO_PALETTE: {
				colorPicker_->addToPalette();

				LOG_INFO("Added current color to palette");
				break;
			}

			case vmf::UserEvent::WINDOW_MINIMIZE: {
				context_->appWindow->minimize();

				LOG_INFO("Minimizing");
				break;
			}

			case vmf::UserEvent::WINDOW_CLOSE: {
				meta_exit();

				LOG_INFO("Exiting");
				break;
			}
		}
	}

	void onRender() {
		drawArea_->render(*context_->vertexRenderer, context_->mouseInput->getCursorPosition());
		editorModel_->render(*context_->vertexRenderer);
		titleBar_->render(*context_->vertexRenderer);
		toolbarBottom_->render(*context_->vertexRenderer);
		colorPicker_->render(*context_->vertexRenderer);

		if (vmfContext_->saveMode) {
			rectOverlay_->render(*context_->vertexRenderer);
			savePopup_->render(*context_->vertexRenderer);
		}
		if (vmfContext_->loadMode) {
			rectOverlay_->render(*context_->vertexRenderer);
			loadPopup_->render(*context_->vertexRenderer);
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

	std::unique_ptr<vmf::Toolbar> toolbarBottom_;

	std::unique_ptr<vmf::TitleBar> titleBar_;
	std::unique_ptr<vmf::SavePopup> savePopup_;
	std::unique_ptr<vmf::LoadPopup> loadPopup_;

	std::unique_ptr<vmf::ColorPicker> colorPicker_;

	std::unique_ptr<ir::render::Rectangle> rectOverlay_;
};

#endif // PROJECT_VMF_STATE_HPP_