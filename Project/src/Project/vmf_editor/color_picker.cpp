#include "Project/vmf_editor/color_picker.hpp"

#include "Iridium/rendering/rectangle.hpp"
#include "Iridium/rendering/text.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

#include "Iridium/input/mouse.hpp"
#include "Iridium/math.hpp"

#include "Iridium/vgui/label.hpp"

namespace vmf {
	ColorPicker::ColorPicker(vmf::Context* context) : context_(context) {
		rect_ = std::make_unique<ir::render::Rectangle>();

		addToPalette(sf::Color::White);
		addToPalette(sf::Color{ 255u, 255u, 255u, 64u });

		frame_ = std::make_unique<ir::vgui::FramedElement>();
		frame_->setSize(ir::Vector { 100.f, 120.f });
		frame_->setBackgroundColor(sf::Color::Black);
		frame_->setFrameColor(sf::Color::White);

		for (size_t i = 0; i < 4; i++) {
			std::string rgba { "RGBA" };
			std::array<sf::Color, 4> clr { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color{ 255u, 255u, 255u, 64u } };

			auto s = std::make_unique<ir::vgui::Slider>(0, 255);
			s->setPosition(ir::Vector { 0.f, i * 24.f });
			s->setSize(ir::Vector { 100.f, 24.f });
			s->setFrameColor(sf::Color::White);
			s->setValue(255);
			s->setBackgroundColor(clr[i]);

			auto l = std::make_unique<ir::vgui::Label>("0");
			l->setScale(15.f);
			l->setAnchor(ir::vgui::Label::Anchor::RIGHT);
			l->setColor(clr[i]);

			s->addChildElement("label", std::move(l));
			frame_->addChildElement(std::string { "Slider" } + rgba.at(i), std::move(s));
		}

		{
			auto f = std::make_unique<ir::vgui::FramedElement>();
			f->setPosition(ir::Vector { 2.f, 98.f });
			f->setSize(ir::Vector { 96.f, 20.f });
			f->setFrameColor(sf::Color::White);

			frame_->addChildElement("ColorField", std::move(f));
		}

		sliderR_ = frame_->getChild<ir::vgui::Slider>("SliderR");
		sliderG_ = frame_->getChild<ir::vgui::Slider>("SliderG");
		sliderB_ = frame_->getChild<ir::vgui::Slider>("SliderB");
		sliderA_ = frame_->getChild<ir::vgui::Slider>("SliderA");

		setPosition(ir::Vector{ 0.f, 50.f });
	}

	bool ColorPicker::processMouseInput(ir::input::Mouse* mouseInput) {
		const ir::Vector mousePos = mouseInput->getCursorPosition();

		/// Checks whether the mouse cursor is within the palette cell with given ID
		auto isOnPalette = [&](ir::Vector pos, size_t id) {
			ir::Vector offset { frame_->getAbsolutePosition() + ir::Vector { frame_->getSize().x + id * 20.f, frame_->getSize().y - 20.f }};
			return  pos.x >= offset.x &&
					pos.y >= offset.y &&
					pos.x < offset.x + 20.f &&
					pos.y < offset.y + 20.f;
		};

		/// Detection of palette clicks
		if (mouseInput->isPressed(sf::Mouse::Button::Left)) {
			for (size_t i = 0; i < palette_.size(); i++) {
				if (isOnPalette(mousePos, i)) {
					context_->drawColor = palette_[i];

					sliderR_->setValue(context_->drawColor.r);
					sliderG_->setValue(context_->drawColor.g);
					sliderB_->setValue(context_->drawColor.b);
					sliderA_->setValue(context_->drawColor.a);

					return true;
				}
			}
		}

		/// Main UI updating
		bool ret { frame_->update(*mouseInput) };

		auto updateLabel = [&](ir::vgui::Slider* s) { s->getChild<ir::vgui::Label>("label")->setLabel(std::to_string(s->getValue())); };
		updateLabel(sliderR_);
		updateLabel(sliderG_);
		updateLabel(sliderB_);
		updateLabel(sliderA_);

		context_->drawColor.r = sliderR_->getValue();
		context_->drawColor.g = sliderG_->getValue();
		context_->drawColor.b = sliderB_->getValue();
		context_->drawColor.a = sliderA_->getValue();

		frame_->getChild<ir::vgui::FramedElement>("ColorField")->setBackgroundColor(context_->drawColor);

		return ret;
	}

	void ColorPicker::render(ir::render::VertexRenderer& renderer) {
		frame_->render(renderer);
		drawPalette(renderer);
	}

	void ColorPicker::setPosition(ir::Vector topLeftCorner) {
		frame_->setPosition(topLeftCorner);
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

	void ColorPicker::drawPalette(ir::render::VertexRenderer& renderer) {
		for (size_t pos = 0; pos < palette_.size(); pos++) {
			drawPaletteColor(renderer, palette_[pos], pos);
		}
	}

	void ColorPicker::drawPaletteColor(ir::render::VertexRenderer& renderer, sf::Color clr, unsigned int pos) {
		ir::Vector offset { frame_->getSize().x + pos * 20.f, frame_->getSize().y - 20.f };
		rect_->setMode(ir::render::Mode::SOLID);

		if (clr.a != 255u) {
			// Base background rect
			rect_->setPosition(frame_->getAbsolutePosition() + ir::Vector { 2.f, 2.f } + offset);
			rect_->setSize(ir::Vector { 16.f, 16.f });
			rect_->setColor(sf::Color { 160u, 160u, 160u, 255u });
			rect_->render(renderer);
			
			// Checkered background 1
			rect_->setSize(ir::Vector { 8.f, 8.f });
			rect_->setColor(sf::Color { 96u, 96u, 96u, 255u });
			rect_->render(renderer);
			
			// Checkered background 2
			rect_->setPosition(frame_->getAbsolutePosition() + ir::Vector { 10.f, 10.f } + offset);
			rect_->render(renderer);
		}

		// Color
		rect_->setPosition(frame_->getAbsolutePosition() + ir::Vector { 2.f, 2.f } + offset);
		rect_->setSize(ir::Vector { 16.f, 16.f });
		rect_->setColor(clr);
		rect_->render(renderer);

		// Frame
		rect_->setMode(ir::render::Mode::WIREFRAME);
		rect_->setColor(sf::Color::White);
		rect_->render(renderer);
	}
}