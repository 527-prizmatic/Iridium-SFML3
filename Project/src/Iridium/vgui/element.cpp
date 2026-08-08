#include "Iridium/vgui/element.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace ir::vgui {
	std::unique_ptr<ir::render::Rectangle> Element::rect_;

	void Element::createRect() {
		if (!rect_) {
			rect_ = std::make_unique<ir::render::Rectangle>();
		}
	} 

	Element::Element() {
		createRect();

		if (rect_) {
			rect_->setPosition(ir::Vector { 0.f, 0.f });
			rect_->setSize(ir::Vector { 100.f, 100.f });
		}
	}

	void Element::render(ir::render::VertexRenderer& renderer) const {
		renderFrame(renderer);
		for (auto& child : children_) {
			child.second->render(renderer);
		}
	}


	Element* Element::getElement(std::string key) const {
		auto it = children_.find(key);
		if (it != children_.end()) {
			return it->second.get();
		}
		return nullptr;
	}

	Element* Element::operator[](std::string key) const {
		return getElement(key);
	}

	Element* Element::operator[](const char* key) const {
		return getElement(std::string(key));
	}

	void Element::addChildElement(std::string key, std::unique_ptr<ir::vgui::Element> child) {
		if (child) {
			child->parent_ = this;
			children_[key] = std::move(child);
		}
	}
	
	void Element::setPosition(ir::Vector pos) {
		pos_ = pos;
	}
	void Element::setSize(ir::Vector size) {
		size_ = size;
	}

	ir::Vector Element::getPosition() {
		return pos_;
	}

	ir::Vector Element::getSize() {
		return size_;
	}

	void Element::resizeRectangle() const {
		if (rect_) {
			rect_->setPosition(parent_ ? parent_->getPosition() + pos_ : pos_);
			rect_->setSize(size_);
		}
	}

	void Element::renderFrame(ir::render::VertexRenderer& renderer) const {
		if (rect_) {
			resizeRectangle();

			rect_->setMode(ir::render::Mode::SOLID);
			rect_->setColor(clrBackground_);
			rect_->render(renderer);

			rect_->setMode(ir::render::Mode::WIREFRAME);
			rect_->setColor(clrBorder_);
			rect_->render(renderer);
		}
	}
}