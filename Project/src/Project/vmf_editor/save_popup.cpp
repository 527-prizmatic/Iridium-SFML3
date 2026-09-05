#include "Project/vmf_editor/save_popup.hpp"

#include "Iridium/vgui/input_field.hpp"

#include "Project/vmf_editor/ui_button_factory.hpp"

namespace vmf {
	SavePopup::SavePopup(vmf::Context* context, ir::Vector pos) {
		context_ = context;
		savePopup_ = std::make_unique<ir::vgui::FramedElement>();
		if (!savePopup_) {
			LOG_ERROR("Could not create save popup!!");
			return;
		}

		savePopup_ = std::make_unique<ir::vgui::FramedElement>();
		savePopup_->setPosition(pos);
		savePopup_->setSize(ir::Vector { 512.f, 36.f });
		savePopup_->setColors(sf::Color::White, sf::Color::Black);

		auto filename { std::make_unique<ir::vgui::TextField>("") };
		filename->setPosition(ir::Vector { 2.f, 2.f });
		filename->setSize(ir::Vector { 340.f, 32.f });
		filename->setFrameColor(sf::Color::White);
		filename->setColorFocused(sf::Color(255u, 255u, 255u, 32u));
		filename->setColorUnfocused(sf::Color::Black);
		filename->setFrameColor(sf::Color::White);
		filename->setMaxChars(24u);
		filename->setScale(16.f);
		savePopup_->addChildElement("FilenameField", std::move(filename));

		auto buttonSave { vmf::makeButton(ir::Vector { 346.f, 2.f }, ir::Vector { 80.f, 32.f }, sf::Color::Green, "Save") };
		buttonSave->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::CONFIRM_MODEL_SAVE); });
		savePopup_->addChildElement("ButtonSave", std::move(buttonSave));
		
		auto buttonDiscard { vmf::makeButton(ir::Vector { 430.f, 2.f }, ir::Vector { 80.f, 32.f }, sf::Color::Red, "Cancel") };
		buttonDiscard->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::CANCEL_MODEL_SAVE); });
		savePopup_->addChildElement("ButtonDiscard", std::move(buttonDiscard));

		textField_ = savePopup_->getChild<ir::vgui::TextField>("FilenameField");
	}

	void SavePopup::processEvent(const sf::Event& event) {
		if (!savePopup_) {
			return;
		}

		bool confirm { false };
		if (event.is<sf::Event::TextEntered>() && context_->saveMode) {
			auto c = event.getIf<sf::Event::TextEntered>()->unicode;
			if (c == '\r') {
				context_->registerEvent(vmf::UserEvent::CONFIRM_MODEL_LOAD);
				confirm = true;
			}
		}

		if (!confirm) {
			savePopup_->processEvent(event);
		}
	}

	bool SavePopup::update(ir::input::Mouse* mouseInput) {
		if (!savePopup_) {
			return false;
		}

		return savePopup_->update(*mouseInput);
	}

	void SavePopup::render(ir::render::VertexRenderer& renderer) {
		if (!savePopup_) {
			return;
		}

		savePopup_->render(renderer);
	}

	void SavePopup::setValue(const std::string val) {
		if (textField_) {
			textField_->setValue(val);
		}
	}

	std::string SavePopup::getValue() const {
		return textField_ ? textField_->getValue() : "ERR_VAL";
	}

	void SavePopup::focus() {
		if (!textField_) {
			return;
		}

		textField_->focus();
	}
}