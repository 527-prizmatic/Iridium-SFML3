#ifndef IRIDIUM_RENDERING_SHAPES_HPP_
#define IRIDIUM_RENDERING_SHAPES_HPP_

#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"

namespace Ir {
	class RenderTarget;

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
			Ir::Vector m_position { 0.f, 0.f };
			float m_angle { 0.f };
			Ir::Vector m_anchor { 0.f, 0.f };
			sf::Color m_color { sf::Color::White };
		};

		class Rectangle : public Shape {
		public:
			virtual void Render(Ir::RenderTarget& _target) const;
			
			Rectangle& SetSize(Ir::Vector _size);
			Rectangle& SetSize(float _x, float _y);
			Rectangle& SetCorners(Ir::Vector _top_left, Ir::Vector _bottom_right);

			inline Ir::Vector GetSize() const { return this->m_size; }

		private:
			Ir::Vector m_size { 0.f, 0.f };
		};

		/// @brief All-round vertex-based circle rendering class.
		/// Also usable for regular polygons, as circles are essentially just polygons with many vertices.
		class Circle : public Shape {
		public:
			virtual void Render(Ir::RenderTarget& _target) const;
			
			Circle& SetRadius(float _rds);
			Circle& SetVertexCount(unsigned int _count);

			inline float GetRadius() const { return this->m_radius; }
			inline unsigned int GetVertexCount() const { return this->m_vertexCount; }

		private:
			float m_radius { 0.f };
			unsigned int m_vertexCount { 32u };
			float m_vertexAngle { Ir::Math::tau / 32.f };
		};
	}
};


#endif // IRIDIUM_RENDERING_SHAPES_HPP_