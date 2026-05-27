#ifndef PROJECT_EDITOR_TOOL_FACTORY_HPP_
#define PROJECT_EDITOR_TOOL_FACTORY_HPP_

#include "Project/vmf_editor/text_button.hpp"
#include "Project/vmf_editor/icon_button.hpp"
#include "Project/vmf_editor/toolbar.hpp"

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
		button->setLabelScale(2.f);
		return button;
	}

	inline std::unique_ptr<vmf::TextButton> produceTextButton(vmf::Context* context, std::string_view label, vmf::UserEvent event, sf::Color color = sf::Color::Green) {
		auto button = std::make_unique<vmf::TextButton>(context, label);
		button->setColors(color, sf::Color::White);
		button->setEvent(event);
		button->setLabelScale(2.f);
		return button;
	}
}

#endif // PROJECT_EDITOR_TOOL_FACTORY_HPP_