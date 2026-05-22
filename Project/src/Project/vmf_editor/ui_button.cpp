#include "Project/vmf_editor/ui_button.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"
#include "Iridium/input/mouse.hpp"

namespace vmf {
	UiButton::UiButton(vmf::Context* context, ir::Vector topLeftCorner, ir::Vector size, std::string_view label, std::function<void(vmf::Context*)> func) {
		context_ = context;

		rect_ = std::make_unique<ir::render::Rectangle>();
		rect_->setPosition(topLeftCorner);
		rect_->setSize(size);

		label_ = std::make_unique<ir::render::Text>();
		label_->setString(label.data());
		setLabelScale(3.f);

		func_ = func;
	}

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
	
	void UiButton::setLabelScale(float scale) {
		label_->setScale(scale);
		recenterLabel();
	}

	float UiButton::getLabelScale() { return label_->getScale(); }
	std::string UiButton::getLabel() { return label_->getString(); }

	void UiButton::setLabel(std::string_view label) {
		label_->setString(label.data());
		recenterLabel();
	}
	
	void UiButton::setColor(sf::Color color) {
		label_->setColor(color);
		rect_->setColor(color);
	}

	void UiButton::recenterLabel() {
		label_->setAnchor(label_->getBoundingBoxSize() * .5f);
		label_->setPosition(rect_->getPosition() + rect_->getSize() * .5f);
	}
}