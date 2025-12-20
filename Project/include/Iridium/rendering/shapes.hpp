#ifndef IRIDIUM_RENDERING_SHAPES_HPP_
#define IRIDIUM_RENDERING_SHAPES_HPP_

#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"

namespace Ir {
	class RenderTarget;

	namespace Render {
		/// @brief Generic base class for vertex-based drawable objects.
		/// Can be freely derived by the user.
		class Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void Render(Ir::RenderTarget& _target) const = 0;

			Shape& SetPosition(Ir::Vector _pos); ///< @brief Sets screen position, in pixels
			Shape& SetAngle(float _angle); ///< @brief Sets rotation about the anchor point, CCW in radians
			Shape& SetAnchor(Ir::Vector _anchor); ///< @brief Sets anchor point, in pixels
			Shape& SetAnchor(float _x, float _y); ///< @brief Sets anchor point, in pixels
			Shape& SetColor(sf::Color _color); ///< @brief Sets object color
			
			inline Ir::Vector GetPosition() const { return this->m_position; } ///< @return Screen position, in pixels
			inline float GetAngle() const { return this->m_angle; } ///< @return Rotation about the anchor point, in radians
			inline Ir::Vector GetAnchor() const { return this->m_anchor; } ///< @return Anchor point, in pixels
			inline sf::Color GetColor() const { return this->m_color; } ///< @return Object color

		private:
			Ir::Vector m_position { 0.f, 0.f }; ///< Screen position
			float m_angle { 0.f }; ///< Angle, in radians
			Ir::Vector m_anchor { 0.f, 0.f }; ///< Anchor point
			sf::Color m_color { sf::Color::White }; ///< Object color
		};

		/// @brief Utility class for drawing wireframe rectangles.
		/// For rectangles, position is considered to be the top-left corner.
		class Rectangle : public Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void Render(Ir::RenderTarget& _target) const;
			
			Rectangle& SetSize(Ir::Vector _size); ///< @brief Sets size, in pixels
			Rectangle& SetSize(float _x, float _y); ///< @brief Sets size, in pixels
			Rectangle& SetCorners(Ir::Vector _top_left, Ir::Vector _bottom_right); ///< @brief Sets rectangle's corners as screen positions

			inline Ir::Vector GetSize() const { return this->m_size; } ///< @return Rectangle size, in pixels

		private:
			Ir::Vector m_size { 0.f, 0.f }; ///< Size
		};

		/// @brief Utility class for drawing wireframe circles.
		/// Also usable for regular polygons, as circles are essentially just polygons with many vertices.
		/// For such shapes, position is considered to be the center.
		class Circle : public Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void Render(Ir::RenderTarget& _target) const;
			
			Circle& SetRadius(float _rds); ///< @brief Sets radius, in pixels
			Circle& SetVertexCount(unsigned int _count); ///< @brief Sets vertex count

			inline float GetRadius() const { return this->m_radius; } ///< @return Radius, in pixels
			inline unsigned int GetVertexCount() const { return this->m_vertexCount; } ///< @return Vertex count

		private:
			float m_radius { 0.f }; ///< Radius
			unsigned int m_vertexCount { 32u }; ///< Vertex count
			float m_vertexAngle { Ir::Math::tau / 32.f }; ///< Angle between two vertices. Used internally for reducing calculations in render calls.
		};
	}
}

#endif // IRIDIUM_RENDERING_SHAPES_HPP_