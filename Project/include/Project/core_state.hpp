#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/state.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/text.hpp"

#include "Iridium/assets/asset_manager.hpp"
#include "Iridium/assets/sound_manager.hpp"

#include "Iridium/vgui/element.hpp"
#include "Iridium/vgui/checkbox.hpp"
#include "Iridium/vgui/label.hpp"
#include "Iridium/vgui/input_field.hpp"

class CoreState : public ir::StateBase<CoreState> {
public:
	void onInitialize() {
		ir::render::Text::loadModels();

		text_ = std::make_unique<ir::render::Text>();
		text_->setColor(sf::Color::Green);
		text_->setString("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789");
		text_->setPosition(ir::Vector{ 10.f, 10.f });
		text_->setScale(25.f);

		root_ = std::make_unique<ir::vgui::Element>();
		root_->setPosition(ir::Vector { 100.f, 100.f });

		root_->addChildElement("child1", std::make_unique<ir::vgui::Element>());
		(*root_)["child1"]->setPosition(ir::Vector { 10.f, 10.f });
		(*root_)["child1"]->setSize(ir::Vector { 20.f, 80.f });
		
		root_->addChildElement("checkbox", std::make_unique<ir::vgui::Checkbox>());
		(*root_)["checkbox"]->setPosition(ir::Vector { 40.f, 40.f });
		(*root_)["checkbox"]->setSize(ir::Vector { 25.f, 25.f });

		(*root_)["checkbox"]->registerClickEvent([&]() { text_->setScale(text_->getScale() + .5f); });
		
		root_->addChildElement("label1", std::make_unique<ir::vgui::Label>("Label 1"));
		auto* label1 = root_->getElement<ir::vgui::Label>("label1");
		label1->setAnchor(ir::vgui::Label::Anchor::TOP);
		
		root_->addChildElement("label2", std::make_unique<ir::vgui::Label>("Label 2"));
		auto* label2 = root_->getElement<ir::vgui::Label>("label2");
		label2->setAnchor(ir::vgui::Label::Anchor::LEFT);

		root_->addChildElement("label3", std::make_unique<ir::vgui::Label>("Label 3"));
		auto* label3 = root_->getElement<ir::vgui::Label>("label3");
		label3->setAnchor(ir::vgui::Label::Anchor::RIGHT);

		root_->addChildElement("label4", std::make_unique<ir::vgui::Label>("Label 4"));
		auto* label4 = root_->getElement<ir::vgui::Label>("label4");
		label4->setAnchor(ir::vgui::Label::Anchor::BOTTOM);

		root_->addChildElement("label5", std::make_unique<ir::vgui::TextField>("Label 5"));
		auto* label5 = root_->getElement<ir::vgui::TextField>("label5");
		label5->setPosition(ir::Vector { 100.f, 100.f });
		label5->setSize(ir::Vector { 100.f, 25.f });
	//	label5->setAnchor(ir::vgui::Label::Anchor::OVER);
	}
	
	void onReceiveEvent(const sf::Event& event) {
		root_->processEvent(event);
		if (event.is<sf::Event::KeyReleased>()) {
			auto code = event.getIf<sf::Event::KeyReleased>()->code;
			if (code == sf::Keyboard::Key::Escape) {
				meta_exit();
			}
		}
	}

	void onUpdate() {
		root_->update(*context_->mouseInput);

		auto* label5 = root_->getElement<ir::vgui::TextField>("label5");
		if (label5->hasFocus()) {
			label5->setMaxChars(20);
		}
		else {
			label5->setMaxChars(10);
		}

		if (dynamic_cast<ir::vgui::Checkbox*>((*root_)["checkbox"])->isEnabled()) {
			text_->setColor(sf::Color::Cyan);
		}
		else {
			text_->setColor(sf::Color::Green);
		}
	}

	void onRender() {
		text_->render(*context_->vertexRenderer);
		root_->render(*context_->vertexRenderer);
	}
		
	void onEnd() { }

private:
	std::unique_ptr<ir::render::Text> text_;
	std::unique_ptr<ir::vgui::Element> root_;
};

#endif // PROJECT_TESTSTATE_HPP_