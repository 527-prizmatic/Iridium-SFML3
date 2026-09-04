#include "Iridium/vgui/element.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

#include "Iridium/input/mouse.hpp"

namespace ir::vgui {
#pragma region Core functions
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
				clickHeld_ = true;
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

		if (mouseInput.isReleased(sf::Mouse::Button::Left) && clickHeld_) {
			onRelease();
			clickHeld_ = false;
		}

		return anyChildrenUpdated || isInArea;
	}

	void Element::render(ir::render::VertexRenderer& renderer) const {
		renderDebugFrame(renderer);
		renderChildren(renderer);
	}
#pragma endregion

#pragma region Child management
	Element* Element::getChild(std::string key) const {
		auto it = children_.find(key);
		if (it != children_.end()) {
			return it->second.get();
		}
		return nullptr;
	}

	Element* Element::operator[](std::string key) const {
		return getChild(key);
	}

	Element* Element::operator[](const char* key) const {
		return getChild(std::string(key));
	}

	void Element::addChildElement(std::string key, std::unique_ptr<ir::vgui::Element> child) {
		if (child) {
			child->parent_ = this;
			children_[key] = std::move(child);
			children_[key]->resizeRectangle();
			// return children_[key];
		}
	}

	void Element::renderChildren(ir::render::VertexRenderer& renderer) const {
		for (auto& child : children_) {
			child.second->render(renderer);
		}
	}
#pragma endregion
	
#pragma region Event management
	void Element::registerClickEvent(ir::vgui::ClickEvent event) {
		clickEvents.push_back(std::move(event));
	}
	
	void Element::processEvent(const sf::Event& evt) {
		onSfEvent(evt);
		for (auto& child : children_) {
			child.second->processEvent(evt);
		}
	}
#pragma endregion

#pragma region Mutators and accessors
	void Element::setPosition(ir::Vector pos) {
		pos_ = pos;
	}
	void Element::setSize(ir::Vector size) {
		size_ = size;
	}

	ir::Vector Element::getPosition() const { return pos_; }
	ir::Vector Element::getSize() const { return size_; }
	ir::Vector Element::getAbsolutePosition() const { return parent_ != nullptr ? pos_ + parent_->getAbsolutePosition() : pos_; }
	
	void Element::setBackgroundColor(sf::Color clr) { clrBackground_ = clr; }
	sf::Color Element::getBackgroundColor() const { return clrBackground_; }
		
	void Element::setFrameColor(sf::Color clr) { clrFrame_ = clr; }
	sf::Color Element::getFrameColor() const { return clrFrame_; }

	void Element::setColors(sf::Color frame, sf::Color background) {
		clrBackground_ = background;
		clrFrame_ = frame;
	}

	void Element::setDebugMode(bool debug) {
		debugMode = debug;
	}
#pragma endregion

#pragma region Internal utilities
	void Element::resizeRectangle() const {
		if (rect_) {
			rect_->setPosition(getAbsolutePosition());
			rect_->setSize(size_);
		}
	}

	void Element::renderDebugFrame(ir::render::VertexRenderer& renderer) const {
		if (debugMode) {
			renderFrame(renderer);
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
			rect_->setColor(clrFrame_);
			rect_->render(renderer);
		}
	}
#pragma endregion

	void FramedElement::render(ir::render::VertexRenderer& renderer) const {
		renderFrame(renderer);
		renderChildren(renderer);
	}
}