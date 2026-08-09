#include "Iridium/vgui/checkbox.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace ir::vgui {
	void Checkbox::onIdle() {
		clrBackground_ = sf::Color::Transparent;
	}

	void Checkbox::onHover() {
		clrBackground_ = sf::Color(255, 255, 255, 64);
	}

	void Checkbox::onClick() {
		enabled_ = !enabled_;
	}

	void Checkbox::render(ir::render::VertexRenderer& renderer) const {
		Element::render(renderer);
		if (enabled_) {
			renderCheckbox(renderer);
		}
	}

	void Checkbox::renderCheckbox(ir::render::VertexRenderer& renderer) const {
		ir::Vector absPos { getAbsolutePosition() };

		renderer.reset();
		renderer.addPoint(absPos + ir::Vector { 0.f, size_.y * .5f }, clrBorder_);
		renderer.addPoint(absPos + ir::Vector { size_.x * .5f, size_.y }, clrBorder_);

		renderer.addPoint(absPos + ir::Vector { size_.x * .5f, size_.y }, clrBorder_);
		renderer.addPoint(absPos + ir::Vector { size_.x, size_.y * .5f }, clrBorder_);

		renderer.addPoint(absPos + ir::Vector { size_.x, size_.y * .5f }, clrBorder_);
		renderer.addPoint(absPos + ir::Vector { size_.x * .5f, 0.f }, clrBorder_);

		renderer.addPoint(absPos + ir::Vector { size_.x * .5f, 0.f }, clrBorder_);
		renderer.addPoint(absPos + ir::Vector { 0.f, size_.y * .5f }, clrBorder_);

		renderer.flush();
	}
}