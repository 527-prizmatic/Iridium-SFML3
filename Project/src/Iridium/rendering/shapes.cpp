#include "Iridium/rendering/shapes.hpp"

namespace Ir {
	namespace Render {
		Shape& Shape::SetPosition(Ir::Vector _pos) {
			this->m_position = _pos;
			return *this;
		}

		Shape& Shape::SetAngle(float _angle) {
			this->m_angle = _angle;
			return *this;
		}

		Shape& Shape::SetAnchor(Ir::Vector _anchor) {
			this->m_anchor = _anchor;
			return *this;
		}

		Rectangle& Rectangle::SetSize(Ir::Vector _size) {
			this->m_size = _size;
			return *this;
		}
			
		Rectangle& Rectangle::SetCorners(Ir::Vector _top_left, Ir::Vector _bottom_right) {
			this->SetPosition(_top_left);
			this->SetSize(_bottom_right - _top_left);
		}

		void Rectangle::Render(Ir::RenderTarget& _target) const {
			
		}
	}
}