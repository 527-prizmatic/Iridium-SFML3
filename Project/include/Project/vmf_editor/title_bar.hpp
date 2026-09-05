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

		void setTitle(std::string title);

	private:
		std::unique_ptr<ir::vgui::FramedElement> titleBar_;
		vmf::Context* context_;
		ir::vgui::Label* title_;
	};
}

#endif // PROJECT_EDITOR_TITLEBAR_HPP_