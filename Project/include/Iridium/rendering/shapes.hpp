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
			Shape& SetAnchor(float _x, float _y);
			Shape& SetColor(sf::Color _color);
			
			inline Ir::Vector GetPosition() const { return this->m_position; }
			inline float GetAngle() const { return this->m_angle; }
			inline Ir::Vector GetAnchor() const { return this->m_anchor; }
			inline sf::Color GetColor() const { return this->m_color; }

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
			Rectangle& SetSize(float _x, float _y);
			Rectangle& SetCorners(Ir::Vector _top_left, Ir::Vector _bottom_right);

			inline Ir::Vector GetSize() const { return this->m_size; }

		private:
			Ir::Vector m_size;
		};
	}
};


#endif // IRIDIUM_RENDERING_SHAPES_HPP_