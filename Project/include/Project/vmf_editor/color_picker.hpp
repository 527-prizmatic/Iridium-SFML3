#ifndef PROJECT_EDITOR_COLOR_PICKER_HPP_
#define PROJECT_EDITOR_COLOR_PICKER_HPP_

#include "Project/vmf_editor/context.hpp"

#include "Iridium/vgui/slider.hpp"

namespace vmf {
	class ColorPicker {
	public:
		ColorPicker(vmf::Context* context);

		/// @return Whether an event was picked up
		bool processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer);

		void setPosition(ir::Vector topLeftCorner);

		void addToPalette();
		void addToPalette(sf::Color clr);

	private:

		std::vector<sf::Color> palette_;

		std::unique_ptr<ir::vgui::FramedElement> frame_ { };

		ir::vgui::Slider* sliderR_;
		ir::vgui::Slider* sliderG_;
		ir::vgui::Slider* sliderB_;
		ir::vgui::Slider* sliderA_;
		
		std::unique_ptr<ir::render::Rectangle> rect_;

		vmf::Context* context_;

		void drawPalette(ir::render::VertexRenderer& renderer);
		void drawPaletteColor(ir::render::VertexRenderer& renderer, sf::Color clr, unsigned int pos);
	};
}

#endif // PROJECT_EDITOR_COLOR_PICKER_HPP_