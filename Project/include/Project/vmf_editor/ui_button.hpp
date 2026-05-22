#ifndef PROJECT_EDITOR_UI_BUTTON_HPP_
#define PROJECT_EDITOR_UI_BUTTON_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class UiButton {
	public:
		UiButton(vmf::Context* context, ir::Vector topLeftCorner, ir::Vector size, std::string_view label, std::function<void(vmf::Context*)> func);

		/// @return Whether an event was picked up
		bool processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer);

		void setLabelScale(float scale);
		float getLabelScale();

		void setLabel(std::string_view label);
		std::string getLabel();

		void setIdleColor(sf::Color color) { idleColor_ = color; }
		sf::Color getIdleColor() { return idleColor_; }
		void setActiveColor(sf::Color color) { activeColor_ = color; }
		sf::Color getActiveColor() { return activeColor_; }

		void setColors(sf::Color idle, sf::Color active) {
			idleColor_ = idle;
			activeColor_ = active;
		}

		void setIsTransparent(bool choice) { isTransparent_ = choice; }
		bool getIsTransparent() { return isTransparent_; }

	private:
	void recenterLabel();
	void setColor(sf::Color color);
	
	vmf::Context* context_;
	
	std::unique_ptr<ir::render::Rectangle> rect_;
	std::unique_ptr<ir::render::Text> label_;
	std::function<void(vmf::Context*)> func_ {};

	
	sf::Color idleColor_ { sf::Color::Red };
	sf::Color activeColor_ { sf::Color::White };

	bool isHeldDown_ { false };
	bool isTransparent_ { true };
	};
}

#endif // PROJECT_EDITOR_UI_BUTTON_HPP_