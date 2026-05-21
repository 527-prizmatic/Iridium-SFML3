#include "Project/vmf_editor/draw_area.hpp"

namespace vmf {
	DrawArea::DrawArea(vmf::Context* context) {
		context_ = context;
		gridRenderer_ = std::make_unique<ir::render::ModelRenderer>();
		gridRenderer_->setModel(assembleGridModel());
	}

	ir::render::Model DrawArea::assembleGridModel() {
		using namespace ir::render;
		Model model {};

		static const sf::Color colorGridBase { 255u, 255u, 255u, 16u };
		static const sf::Color colorGridMedium { 255u, 224u, 224u, 64u };
		static const sf::Color colorGridAxes { 255u, 0u, 0u, 255u };

		auto addAxesComponents = [&](short offset, sf::Color clr) {
			model.addComponent(std::move(Component { Vertex(-128, offset, clr), Vertex(128, offset, clr) }));
			model.addComponent(std::move(Component { Vertex(offset, -128, clr), Vertex(offset, 128, clr) }));
		};

		for (short i = -128; i < 128; i++) {
			addAxesComponents(i, colorGridBase);
		}

		for (short i = -128; i < 128; i += 4) {
			addAxesComponents(i, colorGridMedium);
		}

		addAxesComponents(0, colorGridAxes);

		return model;
	}

	void DrawArea::processKeyboardInput(const sf::Event& event) {
		
	}

	void DrawArea::processMouseInput(ir::input::Mouse* mouseInput) {
		
	}

	void DrawArea::render(ir::render::VertexRenderer& renderer) {
		gridRenderer_->setScale(context_->zoomFactor);
		gridRenderer_->setPosition(context_->posOffset * context_->zoomFactor);
		gridRenderer_->render(renderer);
	}
}