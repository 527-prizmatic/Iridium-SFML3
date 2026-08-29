#include "Iridium/vgui/element.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

#include "Iridium/input/mouse.hpp"

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

	bool Element::update(ir::input::Mouse& mouseInput) {
		ir::Vector posAbsolute = getAbsolutePosition();
		bool isInArea = mouseInput.getCursorPosition().isInArea(posAbsolute, posAbsolute + size_);

		bool anyChildrenUpdated = false;
		for (auto& child : children_) {
			anyChildrenUpdated |= child.second->update(mouseInput);
		}

		if (!anyChildrenUpdated && isInArea) {
			if (mouseInput.isPressed(sf::Mouse::Button::Left)) {
				onClick();
				for (auto evt : clickEvents) {
					evt();
				}
			}
			else {
				onHover();
			}
		}
		else {
			if (mouseInput.isPressed(sf::Mouse::Button::Left)) {
				onDeselect();
			}
			else {
				onIdle();
			}
		}

		return anyChildrenUpdated || isInArea;
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
			// return children_[key];
		}
	}
	
	void Element::setPosition(ir::Vector pos) {
		pos_ = pos;
	}
	void Element::setSize(ir::Vector size) {
		size_ = size;
	}

	ir::Vector Element::getPosition() const { return pos_; }
	ir::Vector Element::getSize() const { return size_; }
	ir::Vector Element::getAbsolutePosition() const { return parent_ != nullptr ? pos_ + parent_->getAbsolutePosition() : pos_; }

	void Element::resizeRectangle() const {
		if (rect_) {
			rect_->setPosition(parent_ ? parent_->getPosition() + pos_ : pos_);
			rect_->setSize(size_);
		}
	}

	void Element::renderFrame(ir::render::VertexRenderer& renderer) const {
		createRect();
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

	void Element::onIdle() {
		clrBackground_ = sf::Color::Blue;
	}
	
	void Element::onHover() {
		clrBackground_ = sf::Color::Red;
	}

	void Element::onClick() {
	//	LOG_INFO("UI element clicked");
	}

	void Element::onDeselect() {
	//	LOG_INFO("UI element clicked");
	}

	void Element::registerClickEvent(ir::vgui::ClickEvent event) {
		clickEvents.push_back(std::move(event));
	}
}