#include "Project/vmf_editor/icon_button.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace vmf {
	IconButton::IconButton(vmf::Context* context, std::string_view model)
		: UiButton(context) {
		icon_ = std::make_unique<ir::render::ModelRenderer>();

		ir::render::Model modelData = ir::render::Model::loadFromFile(model.data());
		icon_->setModel(modelData);
	//	icon_->setScale(3.f);
	}

	void IconButton::render(ir::render::VertexRenderer& renderer) {
		renderBackgroundRect(renderer);
		setColor(isHeldDown_ ? activeColor_ : idleColor_);
		icon_->render(renderer);
		renderFrameRect(renderer);
		}
		
	void IconButton::recenterIcon() {
		icon_->setAnchor(icon_->getBoundingBoxSize() * .5f);
		icon_->setPosition(rect_->getPosition() + rect_->getSize() * .5f);
	}

	void IconButton::setColor(sf::Color color) {
		icon_->setColor(color);
		UiButton::setColor(color);
	}

	void IconButton::setDimensions(ir::Vector topLeftCorner, ir::Vector size) {
		UiButton::setDimensions(topLeftCorner, size);
		recenterIcon();
	}

	void IconButton::setIcon(std::string_view model) {
		ir::render::Model modelData = ir::render::Model::loadFromFile(model.data());
		icon_->setModel(modelData);
		recenterIcon();
	}
	
	void IconButton::setIconScale(float scale) {
		icon_->setScale(scale);
		recenterIcon();
	}

	float IconButton::getIconScale() { return icon_->getScale(); }
}