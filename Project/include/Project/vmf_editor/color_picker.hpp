#ifndef PROJECT_EDITOR_COLOR_PICKER_HPP_
#define PROJECT_EDITOR_COLOR_PICKER_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class ColorPicker {
	public:
		ColorPicker(vmf::Context* context);

		/// @return Whether an event was picked up
		bool processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer);

		void setPosition(ir::Vector topLeftCorner);

	private:


		std::array<ir::Vector, 4> knobPos_ { };
		
		std::unique_ptr<ir::render::Rectangle> rect_;
		std::unique_ptr<ir::render::Text> text_;

		vmf::Context* context_;

		ir::Vector position_;
		const ir::Vector sliderSize_ { 8.f, 16.f };

		char selected { -1 };

		void computeKnobPositions();
	};
}

#endif // PROJECT_EDITOR_COLOR_PICKER_HPP_