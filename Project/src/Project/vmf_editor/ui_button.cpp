#include "Project/vmf_editor/ui_button.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"
#include "Iridium/input/mouse.hpp"

namespace vmf {
	UiButton::UiButton(vmf::Context* context) {
		context_ = context;
		
		rect_ = std::make_unique<ir::render::Rectangle>();
		label_ = std::make_unique<ir::render::Text>();
		label_->setScale(3.f);
	}
	
#pragma region Public member functions
	bool UiButton::processMouseInput(ir::input::Mouse* mouseInput) {
		ir::Vector mousePos { mouseInput->getCursorPosition() };
		if (mousePos.x > rect_->getPosition().x &&
			mousePos.y > rect_->getPosition().y &&
			mousePos.x < rect_->getPosition().x + rect_->getSize().x &&
			mousePos.y < rect_->getPosition().y + rect_->getSize().y) {

			if (mouseInput->isPressed(sf::Mouse::Button::Left)) {
				isHeldDown_ = true;
				return true;
			}
			else if (mouseInput->isReleased(sf::Mouse::Button::Left)) {
				if (isHeldDown_) {
					func_(context_);
					isHeldDown_ = false;
					return true;
				}
			}
		}
		else {
			isHeldDown_ = false;
		}
		return false;
	}

	void UiButton::render(ir::render::VertexRenderer& renderer) {
		if (!isTransparent_) {
			rect_->setColor(sf::Color::Black);
			rect_->setMode(ir::render::Mode::SOLID);
			rect_->render(renderer);
		}
		
		setColor(isHeldDown_ ? activeColor_ : idleColor_);
		label_->render(renderer);
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->render(renderer);
	}
#pragma endregion

#pragma region Private member functions
	void UiButton::recenterLabel() {
		label_->setAnchor(label_->getBoundingBoxSize() * .5f);
		label_->setPosition(rect_->getPosition() + rect_->getSize() * .5f);
	}

	void UiButton::setColor(sf::Color color) {
		label_->setColor(color);
		rect_->setColor(color);
	}
#pragma endregion

#pragma region Mutators & accessors
	UiButton& UiButton::setDimensions(ir::Vector topLeftCorner, ir::Vector size) {
		rect_->setPosition(topLeftCorner);
		rect_->setSize(size);
		return *this;
	}

	UiButton& UiButton::setLabel(std::string_view label) {
		label_->setString(label.data());
		recenterLabel();
		return *this;
	}
	
	UiButton& UiButton::setLabelScale(float scale) {
		label_->setScale(scale);
		recenterLabel();
		return *this;
	}

	UiButton& UiButton::setFunction(std::function<void(vmf::Context*)> func) {
		func_ = func;
		return *this;
	}
	
	UiButton& UiButton::setIsTransparent(bool choice) {
		isTransparent_ = choice;
		return *this;
	}
	
	UiButton& UiButton::setIdleColor(sf::Color color) {
		idleColor_ = color;
		return *this;
	}

	UiButton& UiButton::setActiveColor(sf::Color color) {
		activeColor_ = color;
		return *this;
	}

	UiButton& UiButton::setColors(sf::Color idle, sf::Color active) {
		idleColor_ = idle;
		activeColor_ = active;
		return *this;
	}

	float UiButton::getLabelScale() { return label_->getScale(); }
	std::string UiButton::getLabel() { return label_->getString(); }
#pragma endregion
}