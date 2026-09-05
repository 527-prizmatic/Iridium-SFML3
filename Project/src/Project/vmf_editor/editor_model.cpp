#include "Project/vmf_editor/editor_model.hpp"
#include "Iridium/rendering/model.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace vmf {
	EditorModel::EditorModel(vmf::Context* context) {
		context_ = context;

		model_ = std::make_unique<ir::render::Model>();
		renderer_ = std::make_unique<ir::render::ModelRenderer>();
	}
	
	void EditorModel::processKeyboardInput(const sf::Event::KeyPressed* event) {
		int increment = event->shift ? 4 : 1;
		if (event->control) {
			if (event->code == sf::Keyboard::Key::Left) {
				moveModel(-increment, 0);
			} else if (event->code == sf::Keyboard::Key::Right) {
				moveModel(increment, 0);
			} else if (event->code == sf::Keyboard::Key::Up) {
				moveModel(0, -increment);
			} else if (event->code == sf::Keyboard::Key::Down) {
				moveModel(0, increment);
			}

			else if (event->code == sf::Keyboard::Key::Z) {
				removeLastComponent();
			}
		}
	}

	bool EditorModel::load(std::string_view filename) {
		std::unique_ptr newModel { std::make_unique<ir::render::Model>() };
		if (newModel) {
			*newModel = ir::render::Model::loadFromFile(filename);
			model_ = std::move(newModel);
			return model_ != nullptr;
		}
		else {
			return false;
		}
	}

	bool EditorModel::save(std::string_view filename) {
		return model_->saveToFile(filename);
	}

	void EditorModel::render(ir::render::VertexRenderer& renderer) {
		renderer_->setModel(*model_);
		renderer_->setPosition(context_->posOffset * context_->zoomFactor);
		renderer_->setScale(context_->zoomFactor);
		renderer_->render(renderer);
	}

	void EditorModel::addComponent(ir::render::Component cmp) {
		if (model_) {
			model_->addComponent(std::move(cmp));
		}
	}

	void EditorModel::removeLastComponent() {
		if (model_ && model_->getComponentCount() != 0) {
			model_->removeLastComponent();
		}
	}

	void EditorModel::clear() {
		model_ = std::make_unique<ir::render::Model>();
	}

	void EditorModel::moveModel(int x, int y) {
		for (auto& cmp : *model_) {
			for (auto& v : cmp) {
				v.x += x;
				v.y += y;
			}
		}
	}

	void EditorModel::moveModel(sf::Vector2i offset) {
		moveModel(offset.x, offset.y);
	}
}