#ifndef PROJECT_EDITOR_DRAW_AREA_HPP_
#define PROJECT_EDITOR_DRAW_AREA_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class DrawArea {
	public:
		DrawArea(vmf::Context* context);

		void processKeyboardInput(const sf::Event::KeyPressed* event);

		void processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer, ir::Vector mousePos);

		void renderQueuedPoints(ir::render::VertexRenderer& renderer, ir::Vector mousePosition);

		void zoom(float delta, ir::Vector mousePos = ir::Vector { 0.f, 0.f });

	private:
		
		std::unique_ptr<ir::render::ModelRenderer> gridRenderer_;

		ir::render::Model assembleGridModel();
		void drawGrid(ir::render::VertexRenderer& renderer);

		vmf::Context* context_;

		ir::Vector gridToScreen(sf::Vector2i grid);
		sf::Vector2i screenToGrid(ir::Vector screen);

	};
}

#endif // PROJECT_EDITOR_DRAW_AREA_HPP_