#include "Project/vmf_editor/draw_area.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"
#include "Iridium/input/mouse.hpp"

namespace vmf {
	DrawArea::DrawArea(vmf::Context* context) {
		context_ = context;
		gridRenderer_ = std::make_unique<ir::render::ModelRenderer>();
		gridRenderer_->setModel(std::move(assembleGridModel()));
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
			if (i % 4 == 0) {
				addAxesComponents(i, colorGridMedium);
			}
		}

		addAxesComponents(0, colorGridAxes);

		return model;
	}

	void DrawArea::processKeyboardInput(const sf::Event::KeyPressed* event) {
		if (event->code == sf::Keyboard::Key::Left) {
			context_->posOffset.x += 2.f;
		} else if (event->code == sf::Keyboard::Key::Right) {
			context_->posOffset.x -= 2.f;
		} else if (event->code == sf::Keyboard::Key::Up) {
			context_->posOffset.y += 2.f;
		} else if (event->code == sf::Keyboard::Key::Down) {
			context_->posOffset.y -= 2.f;
		}
	}

	void DrawArea::processMouseInput(ir::input::Mouse* mouseInput) {
		if (mouseInput->isPressed(sf::Mouse::Button::Left)) {
			sf::Vector2i clickPos { screenToGrid(mouseInput->getCursorPosition()) };
			/// @todo Add color selection
			context_->vertexList.push_back(ir::render::Vertex(clickPos.x, clickPos.y, sf::Color::White));

			/// @todo Implement variants for each component type (to be later selectable)
			if (context_->vertexList.size() == 2) {
				ir::render::Component cmp {};
				for (auto& v : context_->vertexList) {
					cmp.vertices.push_back(std::move(v));
				}
				
				/// @todo Add cmp to edited model
				// editingModel_->addComponent(ir::render::Component(v1, v2));

				context_->vertexList.clear();
			}
		}
	}

	void DrawArea::render(ir::render::VertexRenderer& renderer) {
		gridRenderer_->setScale(context_->zoomFactor);
		gridRenderer_->setPosition(context_->posOffset * context_->zoomFactor);
		gridRenderer_->render(renderer);

		if (context_->vertexList.size() == 1) {
			renderer.reset(sf::PrimitiveType::Lines);

			/// @todo Temporary solution, clean up this monster later
			auto offset = ir::Vector(.5f, .5f) * context_->zoomFactor;
			auto pos = gridToScreen(context_->vertexList[0].getPosition()) + offset;

			renderer.addPoint(pos + ir::Vector(10.f, 0.f), sf::Color::Yellow);
			renderer.addPoint(pos + ir::Vector(0.f, 10.f), sf::Color::Yellow);

			renderer.addPoint(pos + ir::Vector(0.f, 10.f), sf::Color::Yellow);
			renderer.addPoint(pos - ir::Vector(10.f, 0.f), sf::Color::Yellow);

			renderer.addPoint(pos - ir::Vector(10.f, 0.f), sf::Color::Yellow);
			renderer.addPoint(pos - ir::Vector(0.f, 10.f), sf::Color::Yellow);

			renderer.addPoint(pos - ir::Vector(0.f, 10.f), sf::Color::Yellow);
			renderer.addPoint(pos + ir::Vector(10.f, 0.f), sf::Color::Yellow);

			renderer.flush();
		}
	}

	void DrawArea::zoom(float delta) {
		context_->zoomFactor *= std::powf(1.1f, delta);
		context_->posOffset /= std::powf(1.1f, delta);
		context_->posOffset.x = static_cast<int>(context_->posOffset.x);
		context_->posOffset.y = static_cast<int>(context_->posOffset.y);
	}

		ir::Vector DrawArea::gridToScreen(sf::Vector2i grid) {
			grid += sf::Vector2i { context_->posOffset };
			ir::Vector screen { ir::Vector::fromSFMLVector(grid) };
			screen *= context_->zoomFactor;
			return screen;
		}

		sf::Vector2i DrawArea::screenToGrid(ir::Vector screen) {
			screen /= context_->zoomFactor;
			screen -= context_->posOffset;
			sf::Vector2i grid { static_cast<int>(screen.x), static_cast<int>(screen.y) };
			return grid;
		}
}