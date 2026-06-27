#ifndef PROJECT_EDITOR_DRAW_AREA_HPP_
#define PROJECT_EDITOR_DRAW_AREA_HPP_

#include "Project/vmf_editor/context.hpp"

namespace vmf {
	struct DrawGuide {
		enum class Orientation : unsigned char {
			HORIZONTAL,
			VERTICAL
		} orientation;
		short position;
	};

	class DrawArea {
	public:
		DrawArea(vmf::Context* context);

		void processKeyboardInput(const sf::Event::KeyPressed* event);

		void processMouseInput(ir::input::Mouse* mouseInput);

		void render(ir::render::VertexRenderer& renderer, ir::Vector mousePos);

		void renderQueuedPoints(ir::render::VertexRenderer& renderer, ir::Vector mousePosition);

		void zoom(float delta, ir::Vector mousePos = ir::Vector { 0.f, 0.f });

		void createGuide(DrawGuide::Orientation orientation, short position);

	private:
		
		struct {
			sf::Color gridBase { 255u, 255u, 255u, 16u };
			sf::Color gridMedium { 255u, 224u, 224u, 64u };
			sf::Color gridAxes { 255u, 0u, 0u, 255u };
			sf::Color drawPreview { 0u, 255u, 255u, 255u };
			sf::Color guides { 160u, 96u, 255u, 255u };
		} colors_;

		std::unique_ptr<ir::render::ModelRenderer> gridRenderer_;
		std::vector<DrawGuide> guides_;

		ir::render::Model assembleGridModel();
		void drawGrid(ir::render::VertexRenderer& renderer);
		void drawGuides(ir::render::VertexRenderer& renderer);

		vmf::Context* context_;

		ir::Vector gridToScreen(sf::Vector2i grid);
		sf::Vector2i screenToGrid(ir::Vector screen);
		ir::Vector screenToGridFloat(ir::Vector screen);
	};
}

#endif // PROJECT_EDITOR_DRAW_AREA_HPP_