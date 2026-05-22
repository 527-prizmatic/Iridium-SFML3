#include "Project/vmf_editor/toolbar.hpp"
#include "Project/vmf_editor/ui_button.hpp"

#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/input/mouse.hpp"

namespace vmf {
	Toolbar::Toolbar(vmf::Context* context) {
		context_ = context;

		rect_ = std::make_unique<ir::render::Rectangle>();
	}

#pragma region Public member functions
	bool Toolbar::processMouseInput(ir::input::Mouse* mouseInput) {
		ir::Vector mousePos { mouseInput->getCursorPosition() };
		if (mousePos.x > rect_->getPosition().x &&
			mousePos.y > rect_->getPosition().y &&
			mousePos.x < rect_->getPosition().x + rect_->getSize().x &&
			mousePos.y < rect_->getPosition().y + rect_->getSize().y) {

			for (auto& button : buttonList_) {
				button->processMouseInput(mouseInput);
			}
			return true;
		}
		return false;
	}

	void Toolbar::addButton(std::unique_ptr<vmf::UiButton> button) {
		buttonList_.push_back(std::move(button));
		recalculateLayout();
	}

	void Toolbar::render(ir::render::VertexRenderer& renderer) {
		rect_->setMode(ir::render::Mode::SOLID);
		rect_->setColor(sf::Color::Black);
		rect_->render(renderer);
		
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->setColor(sf::Color::White);
		rect_->render(renderer);

		for (auto& button : buttonList_) {
			button->render(renderer);
		}
	}
#pragma endregion

#pragma region Private member functions
	void Toolbar::recalculateLayout() {
		for (size_t i = 0; i < buttonList_.size(); i++) {
			ir::Vector position { 2.f, 2.f };
			ir::Vector size { rect_->getSize() - ir::Vector { 4.f, 4.f } };
			if (direction_ == Direction::HORIZONTAL) {
				position.x += (buttonSize_ + 4.f) * i;
				size.x = buttonSize_;
			}
			else if (direction_ == Direction::VERTICAL) {
				position.y += (buttonSize_ + 4.f) * i;
				size.y = buttonSize_;
			}
			buttonList_[i]->setDimensions(position + rect_->getPosition(), size);
		}
	}
#pragma endregion

#pragma region Mutators & accessors
	void Toolbar::setDimensions(ir::Vector topLeftCorner, ir::Vector size) {
		rect_->setPosition(topLeftCorner);
		rect_->setSize(size);
		recalculateLayout();
	}

	void Toolbar::setPosition(ir::Vector topLeftCorner) {
		rect_->setPosition(topLeftCorner);
		recalculateLayout();
	}

	void Toolbar::setSize(ir::Vector size) {
		rect_->setSize(size);
		recalculateLayout();
	}

	void Toolbar::setDirection(Direction dir) {
		direction_ = dir;
		recalculateLayout();
	}

	void Toolbar::setButtonSize(float size) {
		buttonSize_ = size;
		recalculateLayout();
	}

	ir::Vector Toolbar::getPosition() { return rect_->getPosition(); }
	ir::Vector Toolbar::getSize() { return rect_->getSize(); }
#pragma endregion
}