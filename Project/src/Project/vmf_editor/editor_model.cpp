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
}