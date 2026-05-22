#ifndef PROJECT_EDITOR_TOOL_BAR_HPP_
#define PROJECT_EDITOR_TOOL_BAR_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class UiButton;

	class Toolbar {
	public:
		enum class Direction {
			HORIZONTAL,
			VERTICAL
		};

		Toolbar(vmf::Context* context);

		/// @return Whether an event was picked up
		bool processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer);

		void addButton(std::unique_ptr<vmf::UiButton> button);
		
		void setDimensions(ir::Vector topLeftCorner, ir::Vector size);
		void setPosition(ir::Vector topLeftCorner);
		void setSize(ir::Vector size);
		void setDirection(Direction dir);
		void setButtonSize(float size);
		
		ir::Vector getPosition();
		ir::Vector getSize();
		Direction getDirection() { return direction_; }
		float getButtonSize() { return buttonSize_; }

	private:
		void recalculateLayout();

		vmf::Context* context_;
		std::unique_ptr<ir::render::Rectangle> rect_;
		std::vector<std::unique_ptr<vmf::UiButton>> buttonList_;

		float buttonSize_ { 50.f };
		Direction direction_ { Direction::HORIZONTAL };
	};
}

#endif // PROJECT_EDITOR_TOOL_BAR_HPP_