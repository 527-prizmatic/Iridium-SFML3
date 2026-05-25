#include "Project/vmf_editor/text_button.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace vmf {
	TextButton::TextButton(vmf::Context* context, std::string_view label)
		: UiButton(context) {
		label_ = std::make_unique<ir::render::Text>();
		label_->setString(label.data());
		label_->setScale(3.f);
	}

	void TextButton::render(ir::render::VertexRenderer& renderer) {
		renderBackgroundRect(renderer);
		setColor(isHeldDown_ ? activeColor_ : idleColor_);
		label_->render(renderer);
		renderFrameRect(renderer);
	}

	void TextButton::recenterLabel() {
		label_->setAnchor(label_->getBoundingBoxSize() * .5f);
		label_->setPosition(rect_->getPosition() + rect_->getSize() * .5f);
	}

	void TextButton::setColor(sf::Color color) {
		label_->setColor(color);
		UiButton::setColor(color);
	}

	void TextButton::setDimensions(ir::Vector topLeftCorner, ir::Vector size) {
		UiButton::setDimensions(topLeftCorner, size);
		recenterLabel();
	}

	void TextButton::setLabel(std::string_view label) {
		label_->setString(label.data());
		recenterLabel();
	}
	
	void TextButton::setLabelScale(float scale) {
		label_->setScale(scale);
		recenterLabel();
	}

	float TextButton::getLabelScale() { return label_->getScale(); }
	std::string TextButton::getLabel() { return label_->getString(); }
}