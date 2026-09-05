#include "Project/vmf_editor/load_popup.hpp"

#include "Iridium/vgui/input_field.hpp"

#include "Project/vmf_editor/ui_button_factory.hpp"

namespace vmf {
	LoadPopup::LoadPopup(vmf::Context* context, ir::Vector pos) {
		context_ = context;
		loadPopup_ = std::make_unique<ir::vgui::FramedElement>();
		if (!loadPopup_) {
			LOG_ERROR("Could not create save popup!!");
			return;
		}

		loadPopup_ = std::make_unique<ir::vgui::FramedElement>();
		loadPopup_->setPosition(pos);
		loadPopup_->setSize(ir::Vector { 512.f, 36.f });
		loadPopup_->setColors(sf::Color::White, sf::Color::Black);

		auto filename { std::make_unique<ir::vgui::TextField>("") };
		filename->setPosition(ir::Vector { 2.f, 2.f });
		filename->setSize(ir::Vector { 340.f, 32.f });
		filename->setFrameColor(sf::Color::White);
		filename->setColorFocused(sf::Color(255u, 255u, 255u, 32u));
		filename->setColorUnfocused(sf::Color::Black);
		filename->setFrameColor(sf::Color::White);
		filename->setMaxChars(24u);
		filename->setScale(16.f);
		loadPopup_->addChildElement("FilenameField", std::move(filename));

		auto buttonSave { vmf::makeButton(ir::Vector { 346.f, 2.f }, ir::Vector { 80.f, 32.f }, sf::Color(64u, 64u, 192u, 255u), "Load") };
		buttonSave->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::CONFIRM_MODEL_LOAD); });
		loadPopup_->addChildElement("ButtonSave", std::move(buttonSave));
		
		auto buttonDiscard { vmf::makeButton(ir::Vector { 430.f, 2.f }, ir::Vector { 80.f, 32.f }, sf::Color::Red, "Cancel") };
		buttonDiscard->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::CANCEL_MODEL_LOAD); });
		loadPopup_->addChildElement("ButtonDiscard", std::move(buttonDiscard));

		textField_ = loadPopup_->getChild<ir::vgui::TextField>("FilenameField");
	}

	void LoadPopup::processEvent(const sf::Event& event) {
		if (!loadPopup_) {
			return;
		}

		bool confirm { false };
		if (event.is<sf::Event::TextEntered>() && context_->loadMode) {
			auto c = event.getIf<sf::Event::TextEntered>()->unicode;
			if (c == '\r') {
				context_->registerEvent(vmf::UserEvent::CONFIRM_MODEL_LOAD);
				confirm = true;
			}
		}

		if (!confirm) {
			loadPopup_->processEvent(event);
		}

		if (event.is<sf::Event::TextEntered>()) {
			setColor(sf::Color::White);
		}
	}

	bool LoadPopup::update(ir::input::Mouse* mouseInput) {
		if (!loadPopup_) {
			return false;
		}

		return loadPopup_->update(*mouseInput);
	}

	void LoadPopup::render(ir::render::VertexRenderer& renderer) {
		if (!loadPopup_) {
			return;
		}

		loadPopup_->render(renderer);
	}

	void LoadPopup::setValue(const std::string val) {
		if (textField_) {
			textField_->setValue(val);
		}
	}

	std::string LoadPopup::getValue() const {
		return textField_ ? textField_->getValue() : "ERR_VAL";
	}

	void LoadPopup::focus() {
		if (!textField_) {
			return;
		}

		textField_->focus();
	}

	void LoadPopup::setColor(const sf::Color clr) {
		if (textField_) {
			textField_->setFrameColor(clr);
			textField_->setLabelColor(clr);
		}
	}
}