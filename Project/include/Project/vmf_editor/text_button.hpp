#ifndef PROJECT_EDITOR_TEXT_BUTTON_HPP_
#define PROJECT_EDITOR_TEXT_BUTTON_HPP_

#include "Project/vmf_editor/ui_button.hpp"

namespace vmf {
	class TextButton : public UiButton {
	public:
		TextButton(vmf::Context* context, std::string_view label = "Button");

		void render(ir::render::VertexRenderer& renderer);

		void setDimensions(ir::Vector topLeftCorner, ir::Vector size);
		void setLabel(std::string_view label);
		void setLabelScale(float scale);

		std::string getLabel();
		float getLabelScale();

	private:
		void recenterLabel();
		void setColor(sf::Color color);

		std::unique_ptr<ir::render::Text> label_;
	};
}

#endif // PROJECT_EDITOR_TEXT_BUTTON_HPP_