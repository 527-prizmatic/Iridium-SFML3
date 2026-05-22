#ifndef PROJECT_EDITOR_UI_BUTTON_HPP_
#define PROJECT_EDITOR_UI_BUTTON_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class UiButton {
	public:
		UiButton(vmf::Context* context);

		/// @return Whether an event was picked up
		bool processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer);

		UiButton& setDimensions(ir::Vector topLeftCorner, ir::Vector size);
		UiButton& setLabel(std::string_view label);
		UiButton& setLabelScale(float scale);
		UiButton& setFunction(std::function<void(vmf::Context*)> func);

		UiButton& setIsTransparent(bool choice);
		UiButton& setIdleColor(sf::Color color);
		UiButton& setActiveColor(sf::Color color);
		UiButton& setColors(sf::Color idle, sf::Color active);

		std::string getLabel();
		float getLabelScale();
		bool getIsTransparent() { return isTransparent_; }
		sf::Color getIdleColor() { return idleColor_; }
		sf::Color getActiveColor() { return activeColor_; }

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