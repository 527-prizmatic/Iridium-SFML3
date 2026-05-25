#include "Project/vmf_editor/ui_button.hpp"
#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"
#include "Iridium/input/mouse.hpp"

namespace vmf {
	UiButton::UiButton(vmf::Context* context) {
		context_ = context;
		rect_ = std::make_unique<ir::render::Rectangle>();
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
#pragma endregion

#pragma region Private member functions
	void UiButton::setColor(sf::Color color) {
		rect_->setColor(color);
	}

	void UiButton::renderBackgroundRect(ir::render::VertexRenderer& renderer) {
		if (!isTransparent_) {
			rect_->setColor(sf::Color::Black);
			rect_->setMode(ir::render::Mode::SOLID);
			rect_->render(renderer);
		}
	}
	
	void UiButton::renderFrameRect(ir::render::VertexRenderer& renderer) {
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->render(renderer);
	}
#pragma endregion

#pragma region Mutators & accessors
	void UiButton::setDimensions(ir::Vector topLeftCorner, ir::Vector size) {
		rect_->setPosition(topLeftCorner);
		rect_->setSize(size);
	}

	void UiButton::setFunction(std::function<void(vmf::Context*)> func) {
		func_ = func;
	}
	
	void UiButton::setIsTransparent(bool choice) {
		isTransparent_ = choice;
	}
	
	void UiButton::setIdleColor(sf::Color color) {
		idleColor_ = color;
	}

	void UiButton::setActiveColor(sf::Color color) {
		activeColor_ = color;
	}

	void UiButton::setColors(sf::Color idle, sf::Color active) {
		idleColor_ = idle;
		activeColor_ = active;
	}
#pragma endregion
}