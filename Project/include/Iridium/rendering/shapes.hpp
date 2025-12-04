#ifndef IRIDIUM_RENDERING_SHAPES_HPP_
#define IRIDIUM_RENDERING_SHAPES_HPP_

#include "Iridium/vector.hpp"
#include "Iridium/render_target.hpp"

namespace Ir {
	namespace Render {
		class Shape {
		public:
			virtual void Render(Ir::RenderTarget& _target) const = 0;

			Shape& SetPosition(Ir::Vector _pos);
			Shape& SetAngle(float _angle);
			Shape& SetAnchor(Ir::Vector _anchor);
			
			inline Ir::Vector GetPosition() const { return this->m_position; }
			inline float GetAngle() { return this->m_angle; }
			inline Ir::Vector GetAnchor() { return this->m_anchor; }

		private:
			Ir::Vector m_position;
			float m_angle;
			Ir::Vector m_anchor;
			sf::Color m_color;
		};

		class Rectangle : public Shape {
		public:
			virtual void Render(Ir::RenderTarget& _target) const;
			
			Rectangle& SetSize(Ir::Vector _size);
			Rectangle& SetCorners(Ir::Vector _top_left, Ir::Vector _bottom_right);

			inline Ir::Vector GetSize() { return this->m_size; }

		private:
			Ir::Vector m_size;
		};
	}
};


#endif // IRIDIUM_RENDERING_SHAPES_HPP_