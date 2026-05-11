#ifndef IRIDIUM_RENDERING_SHAPES_HPP_
#define IRIDIUM_RENDERING_SHAPES_HPP_

#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"

namespace ir {
	class RenderTarget;

	namespace render {
		/// @brief Data holder for texture UVs, comprising a starting position and a size.
		struct UV {
			ir::Vector topLeft {}; ///< Top-left corner of the UV rectangle
			ir::Vector size {}; ///< Size of the UV rectangle

			UV() {}

			UV(ir::Vector topLeft, ir::Vector size) : topLeft { topLeft }, size { size } {}

			ir::Vector topLeftCorner() const { return topLeft; }
			ir::Vector topRightCorner() const { return topLeft + ir::Vector { size.x, 0.f }; }
			ir::Vector bottomLeftCorner() const { return topLeft + ir::Vector { 0.f, size.y }; }
			ir::Vector bottomRightCorner() const { return topLeft + size; }
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
			virtual void render(ir::RenderTarget& target) const = 0;

			Shape& setPosition(ir::Vector pos); ///< @brief Sets screen position, in pixels
			Shape& setAngle(float angle); ///< @brief Sets rotation about the anchor point, CCW in radians
			Shape& setAnchor(ir::Vector anchor); ///< @brief Sets anchor point, in pixels
			Shape& setAnchor(float x, float y); ///< @brief Sets anchor point, in pixels
			Shape& setColor(sf::Color color); ///< @brief Sets object color
			Shape& setMode(ir::render::Mode mode); ///< @brief Sets rendering mode

			inline ir::Vector getPosition() const { return position_; } ///< @return Screen position, in pixels
			inline float getAngle() const { return angle_; } ///< @return Rotation about the anchor point, in radians
			inline ir::Vector getAnchor() const { return anchor_; } ///< @return Anchor point, in pixels
			inline sf::Color getColor() const { return color_; } ///< @return Object color
			inline ir::render::Mode getMode() const { return mode_; } ///< @return Rendering mode

		private:
			ir::Vector position_ { 0.f, 0.f }; ///< Screen position
			float angle_ { 0.f }; ///< Angle, in radians
			ir::Vector anchor_ { 0.f, 0.f }; ///< Anchor point
			sf::Color color_ { sf::Color::White }; ///< Object color
			ir::render::Mode mode_ { ir::render::Mode::WIREFRAME }; ///< Rendering mode
		};

		/// @brief Utility class for drawing wireframe rectangles.
		/// For rectangles, position is considered to be the top-left corner.
		class Rectangle : public Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(ir::RenderTarget& target) const;
			
			Rectangle& setSize(ir::Vector size); ///< @brief Sets size, in pixels
			Rectangle& setSize(float x, float y); ///< @brief Sets size, in pixels
			Rectangle& setCorners(ir::Vector topLeft, ir::Vector bottomRight); ///< @brief Sets rectangle's corners as screen positions

			inline ir::Vector getSize() const { return size_; } ///< @return Rectangle size, in pixels

		private:
			ir::Vector size_ { 0.f, 0.f }; ///< Size
		};

		/// @brief Utility class for drawing quads (textured objects).
		/// For rectangles, position is considered to be the top-left corner.
		/// @todo Integrate this with a future resource manager, when there will be one
		class Quad : public Rectangle {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(ir::RenderTarget& target) const override;

			Rectangle& setUVs(ir::Vector top_left, ir::Vector size); ///< Sets UVs, in texture pixels
			Rectangle& setUVs(ir::render::UV uv); ///< Sets UVs, in texture pixels
			Rectangle& setTexture(const sf::Texture& texture); ///< Sets texture resource

			ir::render::UV getUVs() { return uv_; } ///< @return UVs, in texture pixels

		private:
			ir::render::UV uv_ {}; ///< Texture UVs
			const sf::Texture* texture_ {}; ///< Texture to use in rendering
		};

		/// @brief Utility class for drawing wireframe circles.
		/// Also usable for regular polygons, as circles are essentially just polygons with many vertices.
		/// For such shapes, position is considered to be the center.
		class Circle : public Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(ir::RenderTarget& target) const;
			
			Circle& setRadius(float rds); ///< @brief Sets radius, in pixels
			Circle& setVertexCount(unsigned int count); ///< @brief Sets vertex count

			inline float getRadius() const { return radius_; } ///< @return Radius, in pixels
			inline unsigned int getVertexCount() const { return vertexCount_; } ///< @return Vertex count

		private:
			float radius_ { 0.f }; ///< Radius
			unsigned int vertexCount_ { 32u }; ///< Vertex count
			float vertexAngle_ { ir::math::tau / 32.f }; ///< Angle between two vertices. Used internally for reducing calculations in render calls.
		};
	}
}

#endif // IRIDIUM_RENDERING_SHAPES_HPP_