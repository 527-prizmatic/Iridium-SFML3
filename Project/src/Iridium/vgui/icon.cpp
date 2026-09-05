#include "Iridium/vgui/icon.hpp"
#include "Iridium/rendering/model_renderer.hpp"

namespace ir::vgui {
	Icon::Icon() {
		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();
	}

	Icon::Icon(std::string filename) {
		modelRenderer_ = std::make_unique<ir::render::ModelRenderer>();
		setIcon(filename);
	}

	bool Icon::update(ir::input::Mouse& mouseInput) {
		return false;
	}

	void Icon::render(ir::render::VertexRenderer& renderer) const {
		if (modelRenderer_) {
			modelRenderer_->setColor(clrFrame_);
			modelRenderer_->setPosition(getAbsolutePosition());
			modelRenderer_->render(renderer);
		}
	}

	void Icon::setScale(float scale) {
		scale_ = scale;
		if (modelRenderer_) {
			float modelSize { std::max(modelRenderer_->getModel().getHeight(), modelRenderer_->getModel().getWidth()) };
			modelRenderer_->setScale(scale_ / modelSize);
		}
	}

	float Icon::getScale() { return scale_; }

	void Icon::setIcon(std::string text) {
		if (modelRenderer_) {
			modelRenderer_->setModel(ir::render::Model::loadFromFile(text));
			setScale(scale_);
		}
	}
}