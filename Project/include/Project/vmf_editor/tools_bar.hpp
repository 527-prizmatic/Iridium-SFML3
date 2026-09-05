#ifndef PROJECT_EDITOR_TOOLBAR_HPP_
#define PROJECT_EDITOR_TOOLBAR_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class ToolsBar {
	public:
		ToolsBar(vmf::Context* context, ir::Vector pos);

		void processEvent(const sf::Event& event);
		bool update(ir::input::Mouse* mouseInput);
		void render(ir::render::VertexRenderer& renderer);

	private:
		std::unique_ptr<ir::vgui::FramedElement> toolsBar_;
		vmf::Context* context_;
	};
}

#endif // PROJECT_EDITOR_TOOLBAR_HPP_