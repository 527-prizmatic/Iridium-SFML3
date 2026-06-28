#include "Project/vmf_editor/color_picker.hpp"

#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

#include "Iridium/input/mouse.hpp"
#include "Iridium/math.hpp"

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

		addToPalette(sf::Color::White);
		addToPalette(sf::Color{ 255u, 255u, 255u, 64u });
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

		auto isOnPalette = [&](ir::Vector pos, size_t id) {
			ir::Vector offset { position_ + ir::Vector { 100.f + id * 20.f, 80.f }};
			return  pos.x >= offset.x &&
					pos.y >= offset.y &&
					pos.x < offset.x + 20.f &&
					pos.y < offset.y + 20.f;
		};

		if (mouseInput->isPressed(Button::Left)) {
			for (size_t i = 0; i < palette_.size(); i++) {
				if (isOnPalette(mousePos, i)) {
					context_->drawColor = palette_[i];
					return true;
				}
			}

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

		context_->drawColor.r = ir::math::clamp(static_cast<unsigned int>(sliderPosToChar(knobPos_[0].x - 6.f + sliderSize_.x * .5f - position_.x)), 0u, 255u);
		context_->drawColor.g = ir::math::clamp(static_cast<unsigned int>(sliderPosToChar(knobPos_[1].x - 6.f + sliderSize_.x * .5f - position_.x)), 0u, 255u);
		context_->drawColor.b = ir::math::clamp(static_cast<unsigned int>(sliderPosToChar(knobPos_[2].x - 6.f + sliderSize_.x * .5f - position_.x)), 0u, 255u);
		context_->drawColor.a = ir::math::clamp(static_cast<unsigned int>(sliderPosToChar(knobPos_[3].x - 6.f + sliderSize_.x * .5f - position_.x)), 0u, 255u);

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

		drawPalette(renderer);
	}

	void ColorPicker::setPosition(ir::Vector topLeftCorner) {
		position_ = topLeftCorner;
	}

	void ColorPicker::addToPalette() { 
		addToPalette(context_->drawColor);
	}

	void ColorPicker::addToPalette(sf::Color clr) {
		for (size_t i = 0; i < palette_.size(); i++) {
			if (palette_[i] == clr) {
				while (i > 0) {
					std::swap(palette_[i], palette_[i-1]);
					i--;
				}
				return;
			}
		}

		palette_.insert(palette_.begin(), clr);
		while (palette_.size() > 10) {
			palette_.pop_back();
		}
	}

	void ColorPicker::computeKnobPositions() {
		knobPos_[0] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.r), 10.f } - sliderSize_ * .5f;
		knobPos_[1] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.g), 30.f } - sliderSize_ * .5f;
		knobPos_[2] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.b), 50.f } - sliderSize_ * .5f;
		knobPos_[3] = position_ + ir::Vector{ 6.f + charToSliderPos(context_->drawColor.a), 70.f } - sliderSize_ * .5f;
	}

	void ColorPicker::drawPalette(ir::render::VertexRenderer& renderer) {
		for (size_t pos = 0; pos < palette_.size(); pos++) {
			drawPaletteColor(renderer, palette_[pos], pos);
		}
	}

	void ColorPicker::drawPaletteColor(ir::render::VertexRenderer& renderer, sf::Color clr, unsigned int pos) {
		ir::Vector offset { 100.f + pos * 20.f, 80.f };
		rect_->setMode(ir::render::Mode::SOLID);

		if (clr.a != 255u) {
			// Base background rect
			rect_->setPosition(position_ + ir::Vector { 2.f, 2.f } + offset);
			rect_->setSize(ir::Vector { 16.f, 16.f });
			rect_->setColor(sf::Color { 160u, 160u, 160u, 255u });
			rect_->render(renderer);
			
			// Checkered background 1
			rect_->setSize(ir::Vector { 8.f, 8.f });
			rect_->setColor(sf::Color { 96u, 96u, 96u, 255u });
			rect_->render(renderer);
			
			// Checkered background 2
			rect_->setPosition(position_ + ir::Vector { 10.f, 10.f } + offset);
			rect_->render(renderer);
		}

		// Color
		rect_->setPosition(position_ + ir::Vector { 2.f, 2.f } + offset);
		rect_->setSize(ir::Vector { 16.f, 16.f });
		rect_->setColor(clr);
		rect_->render(renderer);

		// Frame
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->setColor(sf::Color::White);
		rect_->render(renderer);
	}
}