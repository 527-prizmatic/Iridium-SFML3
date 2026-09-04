#include "Iridium/vgui/label.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace ir::vgui {
	Label::Label(std::string text) {
		ir::render::Text::loadModels();

		label_ = std::make_unique<ir::render::Text>();
		if (label_) {
			label_->setString(text);
			label_->setScale(20.f);
		}
		else {
			LOG_ERROR("Error during creation of VGUI label \"" + text + "\"");
		}
	}

	bool Label::update(ir::input::Mouse& mouseInput) {
		if (parent_ != nullptr) {
			ir::Vector relativePos {};
			ir::Vector boundingBoxSize { label_->getBoundingBoxSize() };
			switch (anchor_) {
				default:
				case Anchor::LEFT: {
					relativePos.x = -boundingBoxSize.x - 5.f;
					relativePos.y = parent_->getSize().y * .5f - boundingBoxSize.y * .5f;
					break;
				}
				case Anchor::RIGHT: {
					relativePos.x = parent_->getSize().x + 5.f;
					relativePos.y = parent_->getSize().y * .5f - boundingBoxSize.y * .5f;
					break;
				}
				case Anchor::TOP: {
					relativePos.x = parent_->getSize().x * .5f - boundingBoxSize.x * .5f;
					relativePos.y = -boundingBoxSize.y - 5.f;
					break;
				}
				case Anchor::BOTTOM: {
					relativePos.x = parent_->getSize().x * .5f - boundingBoxSize.x * .5f;
					relativePos.y = parent_->getSize().y  + 5.f;
					break;
				}
				case Anchor::OVER: {
					relativePos.x = parent_->getSize().x * .5f - label_->getBoundingBoxSize().x * .5f;
					relativePos.y = parent_->getSize().y * .5f - label_->getBoundingBoxSize().y * .5f;
					break;
				}
			}
			pos_ = relativePos;
			size_ = boundingBoxSize;
		}

	//	return Element::update(mouseInput);
		return false;
	}

	void Label::render(ir::render::VertexRenderer& renderer) const {
		renderDebugFrame(renderer);

		if (label_) {
			label_->setPosition(getAbsolutePosition());
			label_->render(renderer);
		}
		
		renderChildren(renderer);
	}

	void Label::setScale(float scale) {
		if (label_) {
			label_->setScale(scale);
		}
	}

	float Label::getScale() {
		if (label_) {
			return label_->getScale();
		}
		return -1.f;
	}

	void Label::setLabel(std::string text) {
		if (label_) {
			label_->setString(text);
		}
	}

	std::string Label::getLabel() {
		if (label_) {
			return label_->getString();
		}
		return "ERROR_LABEL";
	}

	void Label::setColor(sf::Color clr) {
		if (label_) {
			label_->setColor(clr);
		}
	}
	
	sf::Color Label::getColor() {
		if (label_) {
			return label_->getColor();
		}
		return sf::Color::Transparent;
	}

	void Label::setAnchor(Label::Anchor anchor) {
		anchor_ = anchor;
	}

	Label::Anchor Label::getAnchor() {
		return anchor_;
	}

	void Label::setPosition(ir::Vector pos) {
		if (parent_ == nullptr) {
			pos_ = pos;
		}
	}
}