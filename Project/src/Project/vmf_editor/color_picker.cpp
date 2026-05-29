#include "Project/vmf_editor/color_picker.hpp"

#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

#include "Iridium/input/mouse.hpp"

namespace vmf {
	namespace {
		float charToSliderPos(unsigned char val) {
			return static_cast<float>(val) * 88.f / 255.f;
		}

		unsigned char sliderPosToChar(float pos) {
			return static_cast<unsigned char>(pos * 255.f / 88.f);
		}
	}

	ColorPicker::ColorPicker(vmf::Context* context) : context_(context) {
		rect_ = std::make_unique<ir::render::Rectangle>();
		text_ = std::make_unique<ir::render::Text>();
		setPosition(ir::Vector{ 0.f, 50.f });
	}

	bool ColorPicker::processMouseInput(ir::input::Mouse* mouseInput) {
		using namespace sf::Mouse;

		const ir::Vector mousePos = mouseInput->getCursorPosition();
		const ir::Vector sliderSize { 8.f, 16.f };

		computeKnobPositions();

		auto isOnKnob = [&](ir::Vector pos, size_t id) {
			return	pos.x >= knobPos_[id].x &&
					pos.y >= knobPos_[id].y &&
					pos.x <= (knobPos_[id] + sliderSize_).x &&
					pos.y <= (knobPos_[id] + sliderSize_).y;
		};

		if (mouseInput->isPressed(Button::Left)) {
			selected = -1;
			for (size_t i = 0; i < 4; i++) {
				if (isOnKnob(mousePos, i)) {
					selected = static_cast<char>(i);
					break;
				}
			}
		}

		if (mouseInput->isActive(Button::Left)) {
			for (char i = 0; i < 4; i++) {
				if (selected == i) {
					knobPos_[i].x = ir::math::clamp(mousePos.x, position_.x + 6.f, position_.x + 94.f) - sliderSize_.x * .5f;
				}
			}
		}

		context_->drawColor.r = ir::math::clamp(sliderPosToChar(knobPos_[0].x - 6.f + sliderSize_.x * .5f - position_.x), 0u, 255u);
		context_->drawColor.g = ir::math::clamp(sliderPosToChar(knobPos_[1].x - 6.f + sliderSize_.x * .5f - position_.x), 0u, 255u);
		context_->drawColor.b = ir::math::clamp(sliderPosToChar(knobPos_[2].x - 6.f + sliderSize_.x * .5f - position_.x), 0u, 255u);
		context_->drawColor.a = ir::math::clamp(sliderPosToChar(knobPos_[3].x - 6.f + sliderSize_.x * .5f - position_.x), 0u, 255u);

		LOG_INFO(std::to_string(context_->drawColor.r));

		return	mousePos.x >= position_.x &&
				mousePos.y >= position_.y &&
				mousePos.x <= position_.x + 100.f &&
				mousePos.y <= position_.y + 100.f;
	}

	void ColorPicker::render(ir::render::VertexRenderer& renderer) {
		// Render base
		rect_->setPosition(position_);
		rect_->setSize(100.f, 100.f);
		rect_->setColor(sf::Color::Black);
		rect_->setMode(ir::render::Mode::SOLID);
		rect_->render(renderer);

		rect_->setColor(sf::Color::White);
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->render(renderer);

		// Render color sliders
		renderer.reset();
		renderer.addPoint(position_ + ir::Vector{ 6.f, 10.f }, sf::Color::Black);
		renderer.addPoint(position_ + ir::Vector{ 94.f, 10.f }, sf::Color::Red);
		renderer.addPoint(position_ + ir::Vector{ 6.f, 30.f }, sf::Color::Black);
		renderer.addPoint(position_ + ir::Vector{ 94.f, 30.f }, sf::Color::Green);
		renderer.addPoint(position_ + ir::Vector{ 6.f, 50.f }, sf::Color::Black);
		renderer.addPoint(position_ + ir::Vector{ 94.f, 50.f }, sf::Color::Blue);
		renderer.addPoint(position_ + ir::Vector{ 6.f, 70.f }, sf::Color::Black);
		renderer.addPoint(position_ + ir::Vector{ 94.f, 70.f }, sf::Color::White);
		renderer.flush();

		// Render color slider knobs
		rect_->setSize(sliderSize_);

		rect_->setPosition(knobPos_[0]);
		rect_->setColor(sf::Color::Red);
		rect_->render(renderer);
		rect_->setPosition(knobPos_[1]);
		rect_->setColor(sf::Color::Green);
		rect_->render(renderer);
		rect_->setPosition(knobPos_[2]);
		rect_->setColor(sf::Color::Blue);
		rect_->render(renderer);
		rect_->setPosition(knobPos_[3]);
		rect_->setColor(sf::Color::White);
		rect_->render(renderer);

		// Render color field
		rect_->setPosition(position_ + ir::Vector{ 2.f, 82.f });
		rect_->setSize(ir::Vector{ 96.f, 16.f });
		rect_->setColor(context_->drawColor);
		rect_->setMode(ir::render::Mode::SOLID);
		rect_->render(renderer);
		
		rect_->setColor(sf::Color::White);
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->render(renderer);
	}

	void ColorPicker::setPosition(ir::Vector topLeftCorner) {
		position_ = topLeftCorner;
	}

	void ColorPicker::computeKnobPositions() {
		knobPos_[0] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.r), 10.f } - sliderSize_ * .5f;
		knobPos_[1] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.g), 30.f } - sliderSize_ * .5f;
		knobPos_[2] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.b), 50.f } - sliderSize_ * .5f;
		knobPos_[3] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.a), 70.f } - sliderSize_ * .5f;
	}
}