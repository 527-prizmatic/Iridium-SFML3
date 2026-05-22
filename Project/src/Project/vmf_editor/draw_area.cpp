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
			sf::Vector2i clickPos { screenToGrid(mouseInput->getCursorPosition() + ir::Vector(.5f, .5f) * context_->zoomFactor) };
			/// @todo Add color selection
			context_->vertexList.push_back(ir::render::Vertex(clickPos.x, clickPos.y, sf::Color::White));

			auto tryValidate = [&](size_t count) {
				if (context_->vertexList.size() == count) {
					context_->registerEvent(vmf::UserEvent::COMPONENT_VALIDATE);
				}
			};

			switch (context_->drawingType) {
			case ir::render::Component::Type::POINT:
				tryValidate(1);
				break;
			case ir::render::Component::Type::LINE:
				tryValidate(2);
				break;
			case ir::render::Component::Type::TRIANGLE:
				tryValidate(3);
				break;
			}
		}
		if (mouseInput->isPressed(sf::Mouse::Button::Right)) {
			context_->vertexList.clear();
		}
	}

	void DrawArea::render(ir::render::VertexRenderer& renderer, ir::Vector mousePos) {
		gridRenderer_->setScale(context_->zoomFactor);
		gridRenderer_->setPosition(context_->posOffset * context_->zoomFactor);
		gridRenderer_->render(renderer);

		/// @todo Render drawing preview for points and lines
		mousePos += ir::Vector(.5f, .5f) * context_->zoomFactor;
		if (context_->drawingType == ir::render::Component::Type::LINE) {
			if (context_->vertexList.size() == 1) {
				renderer.reset();
				renderer.addPoint(gridToScreen(context_->vertexList[0].getPosition()), sf::Color::Cyan);
				renderer.addPoint(mousePos, sf::Color::Cyan);
				renderer.flush();
			}
		} else if (context_->drawingType == ir::render::Component::Type::TRIANGLE) {
				renderer.reset();
			if (context_->vertexList.size() >= 1) {
				renderer.addPoint(gridToScreen(context_->vertexList[0].getPosition()), sf::Color::Cyan);
				renderer.addPoint(gridToScreen(screenToGrid(mousePos)), sf::Color::Cyan);
			}
			if (context_->vertexList.size() >= 2) {
				renderer.addPoint(gridToScreen(context_->vertexList[1].getPosition()), sf::Color::Cyan);
				renderer.addPoint(gridToScreen(screenToGrid(mousePos)), sf::Color::Cyan);
				renderer.addPoint(gridToScreen(context_->vertexList[1].getPosition()), sf::Color::Cyan);
				renderer.addPoint(gridToScreen(context_->vertexList[0].getPosition()), sf::Color::Cyan);
			}
				renderer.flush();
		}
	}

	void DrawArea::zoom(float delta, ir::Vector mousePos) {
		sf::Vector2i cursorPosGrid = screenToGrid(mousePos);

		context_->zoomFactor *= std::powf(1.1f, delta);
		context_->posOffset /= std::powf(1.1f, delta);
		context_->posOffset.x = static_cast<int>(context_->posOffset.x);
		context_->posOffset.y = static_cast<int>(context_->posOffset.y);

		sf::Vector2i cursorPosGridNew = screenToGrid(mousePos);
		context_->posOffset += ir::Vector::fromSFMLVector(cursorPosGridNew - cursorPosGrid);
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
		if (screen.x < 0.f) {
			screen.x -= 1.f;
		}
		if (screen.y < 0.f) {
			screen.y -= 1.f;
		}
		sf::Vector2i grid { static_cast<int>(screen.x), static_cast<int>(screen.y) };
		return grid;
	}
}