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

		auto buttonSave { vmf::makeButton(ir::Vector { 2.f, 2.f }, ir::Vector { 120.f, 32.f }, sf::Color(128u, 224u, 64u), "Save") };
		buttonSave->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::MODEL_SAVE); });
		titleBar_->addChildElement("ButtonSave", std::move(buttonSave));

		auto buttonLoad { vmf::makeButton(ir::Vector { 124.f, 2.f }, ir::Vector { 120.f, 32.f }, sf::Color(128u, 80u, 224u, 255u), "Load") };
		buttonLoad->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::MODEL_LOAD); });
		titleBar_->addChildElement("ButtonLoad", std::move(buttonLoad));

		auto buttonDiscard { vmf::makeButton(ir::Vector { 246.f, 2.f }, ir::Vector { 120.f, 32.f }, sf::Color(224u, 64u, 48u), "Discard") };
		buttonDiscard->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::MODEL_DISCARD); });
		titleBar_->addChildElement("ButtonDiscard", std::move(buttonDiscard));

		auto buttonMin { vmf::makeIconButton(ir::Vector { 1208.f, 2.f }, ir::Vector { 32.f, 32.f }, sf::Color(32u, 224u, 192u, 255u), 24.f, "tools\\line") };
		buttonMin->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::WINDOW_MINIMIZE); });
		buttonMin->getChild<ir::vgui::Icon>("icon")->setPosition(ir::Vector { 4.f, 22.f });
		titleBar_->addChildElement("ButtonMin", std::move(buttonMin));

		auto buttonClose { vmf::makeIconButton(ir::Vector { 1242.f, 2.f }, ir::Vector { 32.f, 32.f }, sf::Color(224u, 48u, 92u, 255u), 26.f, "tools\\cross") };
		buttonClose->registerClickEvent([&](){ context_->registerEvent(vmf::UserEvent::WINDOW_CLOSE); });
		titleBar_->addChildElement("ButtonClose", std::move(buttonClose));

		auto min { titleBar_->getChild<ir::vgui::FramedElement>("ButtonMin") };
		if (min) {
			auto label { std::make_unique<ir::vgui::Label>() };
			label->setScale(20.f);
			label->setAnchor(ir::vgui::Label::Anchor::LEFT);
			min->addChildElement("Title", std::move(label));
			title_ = min->getChild<ir::vgui::Label>("Title");
		}
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

	void TitleBar::setTitle(std::string title) {
		if (!title_) {
			return;
		}

		title_->setLabel(title);
	}
}