#ifndef PROJECT_EDITOR_TOOL_FACTORY_HPP_
#define PROJECT_EDITOR_TOOL_FACTORY_HPP_

#include "Project/vmf_editor/text_button.hpp"
#include "Project/vmf_editor/icon_button.hpp"
#include "Project/vmf_editor/toolbar.hpp"

#include "Iridium/vgui/label.hpp"
#include "Iridium/vgui/icon.hpp"

namespace vmf {
	inline std::unique_ptr<vmf::IconButton> produceToolButton(vmf::Context* context, std::string_view modelPath, std::function<void(vmf::Context*)> func, sf::Color color = sf::Color::Cyan) {
		auto button = std::make_unique<vmf::IconButton>(context, modelPath);
		button->setColors(color, sf::Color::White);
		button->setFunction(func);
		button->setIconScale(4.f);
		return button;
	}

	inline std::unique_ptr<vmf::IconButton> produceToolButton(vmf::Context* context, std::string_view modelPath, vmf::UserEvent event, sf::Color color = sf::Color::Cyan) {
		auto button = std::make_unique<vmf::IconButton>(context, modelPath);
		button->setColors(color, sf::Color::White);
		button->setEvent(event);
		button->setIconScale(4.f);
		return button;
	}

	inline std::unique_ptr<vmf::TextButton> produceTextButton(vmf::Context* context, std::string_view label, std::function<void(vmf::Context*)> func, sf::Color color = sf::Color::Green) {
		auto button = std::make_unique<vmf::TextButton>(context, label);
		button->setColors(color, sf::Color::White);
		button->setFunction(func);
		button->setLabelScale(16.f);
		return button;
	}

	inline std::unique_ptr<vmf::TextButton> produceTextButton(vmf::Context* context, std::string_view label, vmf::UserEvent event, sf::Color color = sf::Color::Green) {
		auto button = std::make_unique<vmf::TextButton>(context, label);
		button->setColors(color, sf::Color::White);
		button->setEvent(event);
		button->setLabelScale(16.f);
		return button;
	}

	/// Quick button factory for VGUI building
	inline auto makeButton = [](ir::Vector pos, ir::Vector size, sf::Color clr, std::string text) -> std::unique_ptr<ir::vgui::FramedElement> {
		auto button { std::make_unique<ir::vgui::FramedElement>() };
		button->setPosition(pos);
		button->setSize(size);
		button->setColors(clr, sf::Color::Transparent);
		
		auto label { std::make_unique<ir::vgui::Label>(text) };
		label->setColor(clr);
		label->setAnchor(ir::vgui::Label::Anchor::OVER);
		label->setScale(16.f);

		button->addChildElement("label", std::move(label));
		return button;
	};

	/// Quick button factory for VGUI building
	inline auto makeIconButton = [](ir::Vector pos, ir::Vector size, sf::Color clr, float scale, std::string text) -> std::unique_ptr<ir::vgui::FramedElement> {
		auto button { std::make_unique<ir::vgui::FramedElement>() };
		button->setPosition(pos);
		button->setSize(size);
		button->setColors(clr, sf::Color::Transparent);
		
		auto icon { std::make_unique<ir::vgui::Icon>(text) };
		icon->setIcon(text);
		icon->setFrameColor(clr);
		icon->setScale(scale);
		icon->setPosition((size - ir::Vector { scale, scale }) * .5f);

		button->addChildElement("icon", std::move(icon));
		return button;
	};
}

#endif // PROJECT_EDITOR_TOOL_FACTORY_HPP_