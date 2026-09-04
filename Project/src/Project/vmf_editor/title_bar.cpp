#include "Project/vmf_editor/title_bar.hpp"

#include "Iridium/vgui/element.hpp"

#include "Project/vmf_editor/ui_button_factory.hpp"

namespace vmf {
	TitleBar::TitleBar(vmf::Context* context, ir::Vector pos) {
		context_ = context;
		titleBar_ = std::make_unique<ir::vgui::FramedElement>();
		if (!titleBar_) {
			LOG_ERROR("Could not create title bar!!");
			return;
		}

		titleBar_ = std::make_unique<ir::vgui::FramedElement>();
		titleBar_->setPosition(pos);
		titleBar_->setSize(ir::Vector { 1276.f, 36.f });
		titleBar_->setColors(sf::Color::White, sf::Color::Black);

		auto buttonSave { vmf::makeButton(ir::Vector { 2.f, 2.f }, ir::Vector { 120.f, 32.f }, sf::Color::Green, "Save") };
		buttonSave->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::MODEL_SAVE); });
		titleBar_->addChildElement("ButtonSave", std::move(buttonSave));

		auto buttonDiscard { vmf::makeButton(ir::Vector { 126.f, 2.f }, ir::Vector { 120.f, 32.f }, sf::Color::Red, "Discard") };
		buttonDiscard->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::MODEL_DISCARD); });
		titleBar_->addChildElement("ButtonDiscard", std::move(buttonDiscard));
	}

	void TitleBar::processEvent(const sf::Event& event) {
		if (!titleBar_) {
			return;
		}

		titleBar_->processEvent(event);
	}

	bool TitleBar::update(ir::input::Mouse* mouseInput) {
		if (!titleBar_) {
			return false;
		}

		return titleBar_->update(*mouseInput);
	}

	void TitleBar::render(ir::render::VertexRenderer& renderer) {
		if (!titleBar_) {
			return;
		}

		titleBar_->render(renderer);
	}
}