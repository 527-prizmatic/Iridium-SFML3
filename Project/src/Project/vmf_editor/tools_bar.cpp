#include "Project/vmf_editor/tools_bar.hpp"

#include "Iridium/vgui/element.hpp"

#include "Project/vmf_editor/ui_button_factory.hpp"

namespace vmf {
	ToolsBar::ToolsBar(vmf::Context* context, ir::Vector pos) {
		context_ = context;
		toolsBar_ = std::make_unique<ir::vgui::FramedElement>();
		if (!toolsBar_) {
			LOG_ERROR("Could not create toolbar!!");
			return;
		}

		toolsBar_ = std::make_unique<ir::vgui::FramedElement>();
		toolsBar_->setPosition(pos);
		toolsBar_->setSize(ir::Vector { 1276.f, 36.f });
		toolsBar_->setColors(sf::Color::White, sf::Color::Black);

		auto newButton = [&](float posX, float iconScale, std::string icon, sf::Color clr, ir::render::Component::Type drawingType) {
			std::string name { std::string("Button") + icon };
			auto button { vmf::makeIconButton(ir::Vector { posX, 2.f }, ir::Vector { 32.f, 32.f }, clr, iconScale, icon) };
			button->registerClickEvent([&, drawingType](){ context_->drawingType = drawingType; });
			button->registerClickEvent([&, name](){ toolsBar_->getChild<ir::vgui::FramedElement>(name)->setFrameColor(sf::Color::White); });
			button->registerReleaseEvent([&, name, clr](){ toolsBar_->getChild<ir::vgui::FramedElement>(name)->setFrameColor(clr); });
			toolsBar_->addChildElement(name, std::move(button));
		};

		newButton(2.f, 8.f, "tools\\vmf_editor\\tool_point", sf::Color(96, 224u, 64u, 255u), ir::render::Component::Type::POINT);
		newButton(36.f, 26.f, "tools\\vmf_editor\\tool_line", sf::Color(48u, 224u, 160u, 255u), ir::render::Component::Type::LINE);
		newButton(70.f, 26.f, "tools\\vmf_editor\\tool_triangle", sf::Color(64u, 128u, 224u, 255u), ir::render::Component::Type::TRIANGLE);
	}

	void ToolsBar::processEvent(const sf::Event& event) {
		if (!toolsBar_) {
			return;
		}

		toolsBar_->processEvent(event);
	}

	bool ToolsBar::update(ir::input::Mouse* mouseInput) {
		if (!toolsBar_) {
			return false;
		}

		return toolsBar_->update(*mouseInput);
	}

	void ToolsBar::render(ir::render::VertexRenderer& renderer) {
		if (!toolsBar_) {
			return;
		}

		toolsBar_->render(renderer);
	}
}