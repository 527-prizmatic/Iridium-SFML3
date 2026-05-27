#ifndef PROJECT_EDITOR_UI_BUTTON_HPP_
#define PROJECT_EDITOR_UI_BUTTON_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class UiButton {
	public:
		UiButton(vmf::Context* context);

		/// @return Whether an event was picked up
		bool processMouseInput(ir::input::Mouse* mouseInput);

		virtual void render(ir::render::VertexRenderer& renderer) = 0;

		virtual void setDimensions(ir::Vector topLeftCorner, ir::Vector size);

		void setFunction(std::function<void(vmf::Context*)> func);

		void setIsTransparent(bool choice);
		void setIdleColor(sf::Color color);
		void setActiveColor(sf::Color color);
		void setColors(sf::Color idle, sf::Color active);

		void setEvent(vmf::UserEvent event) { event_ = event; }
		void clearEvent() { event_ = {}; }

		bool getIsTransparent() { return isTransparent_; }
		sf::Color getIdleColor() { return idleColor_; }
		sf::Color getActiveColor() { return activeColor_; }

	protected:
		virtual void setColor(sf::Color color);

		void renderBackgroundRect(ir::render::VertexRenderer& renderer);
		void renderFrameRect(ir::render::VertexRenderer& renderer);
		
		vmf::Context* context_;
		
		std::unique_ptr<ir::render::Rectangle> rect_;
		std::function<void(vmf::Context*)> func_ {};
		std::optional<vmf::UserEvent> event_;

		sf::Color idleColor_ { sf::Color::Red };
		sf::Color activeColor_ { sf::Color::White };

		bool isHeldDown_ { false };
		bool isTransparent_ { true };
	};
}

#endif // PROJECT_EDITOR_UI_BUTTON_HPP_