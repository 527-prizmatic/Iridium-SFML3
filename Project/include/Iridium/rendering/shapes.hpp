#ifndef IRIDIUM_RENDERING_SHAPES_HPP_
#define IRIDIUM_RENDERING_SHAPES_HPP_

#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"

namespace iridium {
	class RenderTarget;

	namespace render {
		/// @brief Data holder for texture UVs, comprising a starting position and a size.
		struct UV {
			iridium::Vector topLeft {}; ///< Top-left corner of the UV rectangle
			iridium::Vector size {}; ///< Size of the UV rectangle

			UV() {}

			UV(iridium::Vector topLeft, iridium::Vector size) : topLeft { topLeft }, size { size } {}

			iridium::Vector topLeftCorner() const { return topLeft; }
			iridium::Vector topRightCorner() const { return topLeft + iridium::Vector { size.x, 0.f }; }
			iridium::Vector bottomLeftCorner() const { return topLeft + iridium::Vector { 0.f, size.y }; }
			iridium::Vector bottomRightCorner() const { return topLeft + size; }
		};

		enum Mode : unsigned char {
			WIREFRAME,
			SOLID
		};

		/// @brief Generic base class for vertex-based drawable objects.
		/// Can be freely derived by the user.
		/// All mutators should return a reference to this, allowing for chaining mutators.
		class Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(iridium::RenderTarget& _target) const = 0;

			Shape& setPosition(iridium::Vector pos); ///< @brief Sets screen position, in pixels
			Shape& setAngle(float angle); ///< @brief Sets rotation about the anchor point, CCW in radians
			Shape& setAnchor(iridium::Vector anchor); ///< @brief Sets anchor point, in pixels
			Shape& setAnchor(float x, float y); ///< @brief Sets anchor point, in pixels
			Shape& setColor(sf::Color color); ///< @brief Sets object color
			Shape& setMode(iridium::render::Mode mode); ///< @brief Sets rendering mode

			inline iridium::Vector getPosition() const { return position_; } ///< @return Screen position, in pixels
			inline float getAngle() const { return angle_; } ///< @return Rotation about the anchor point, in radians
			inline iridium::Vector getAnchor() const { return anchor_; } ///< @return Anchor point, in pixels
			inline sf::Color getColor() const { return color_; } ///< @return Object color
			inline iridium::render::Mode getMode() const { return mode_; } ///< @return Rendering mode

		private:
			iridium::Vector position_ { 0.f, 0.f }; ///< Screen position
			float angle_ { 0.f }; ///< Angle, in radians
			iridium::Vector anchor_ { 0.f, 0.f }; ///< Anchor point
			sf::Color color_ { sf::Color::White }; ///< Object color
			iridium::render::Mode mode_ { iridium::render::Mode::WIREFRAME }; ///< Rendering mode
		};

		/// @brief Utility class for drawing wireframe rectangles.
		/// For rectangles, position is considered to be the top-left corner.
		class Rectangle : public Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(iridium::RenderTarget& target) const;
			
			Rectangle& setSize(iridium::Vector size); ///< @brief Sets size, in pixels
			Rectangle& setSize(float x, float y); ///< @brief Sets size, in pixels
			Rectangle& setCorners(iridium::Vector topLeft, iridium::Vector bottomRight); ///< @brief Sets rectangle's corners as screen positions

			inline iridium::Vector getSize() const { return size_; } ///< @return Rectangle size, in pixels

		private:
			iridium::Vector size_ { 0.f, 0.f }; ///< Size
		};

		/// @brief Utility class for drawing quads (textured objects).
		/// For rectangles, position is considered to be the top-left corner.
		/// @todo Integrate this with a future resource manager, when there will be one
		class Quad : public Rectangle {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(iridium::RenderTarget& _target) const override;

			Rectangle& setUVs(iridium::Vector _top_left, iridium::Vector _size); ///< Sets UVs, in texture pixels
			Rectangle& setUVs(iridium::render::UV _uv); ///< Sets UVs, in texture pixels
			Rectangle& setTexture(const sf::Texture& _texture); ///< Sets texture resource

			iridium::render::UV getUVs() { return this->uv_; } ///< @return UVs, in texture pixels

		private:
			iridium::render::UV uv_ {}; ///< Texture UVs
			const sf::Texture* texture_ {}; ///< Texture to use in rendering
		};

		/// @brief Utility class for drawing wireframe circles.
		/// Also usable for regular polygons, as circles are essentially just polygons with many vertices.
		/// For such shapes, position is considered to be the center.
		class Circle : public Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(iridium::RenderTarget& _target) const;
			
			Circle& SetRadius(float _rds); ///< @brief Sets radius, in pixels
			Circle& SetVertexCount(unsigned int _count); ///< @brief Sets vertex count

			inline float GetRadius() const { return this->m_radius; } ///< @return Radius, in pixels
			inline unsigned int GetVertexCount() const { return this->m_vertexCount; } ///< @return Vertex count

		private:
			float m_radius { 0.f }; ///< Radius
			unsigned int m_vertexCount { 32u }; ///< Vertex count
			float m_vertexAngle { iridium::Math::tau / 32.f }; ///< Angle between two vertices. Used internally for reducing calculations in render calls.
		};
	}
}

#endif // IRIDIUM_RENDERING_SHAPES_HPP_