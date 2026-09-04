#ifndef PROJECT_EDITOR_TITLEBAR_HPP_
#define PROJECT_EDITOR_TITLEBAR_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class TitleBar {
	public:
		TitleBar(vmf::Context* context, ir::Vector pos);

		void processEvent(const sf::Event& event);
		bool update(ir::input::Mouse* mouseInput);
		void render(ir::render::VertexRenderer& renderer);

	private:
		std::unique_ptr<ir::vgui::FramedElement> titleBar_;
		vmf::Context* context_;
	};
}

#endif // PROJECT_EDITOR_TITLEBAR_HPP_