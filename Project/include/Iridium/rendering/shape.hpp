#ifndef IRIDIUM_RENDERING_SHAPE_HPP_
#define IRIDIUM_RENDERING_SHAPE_HPP_

#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"
#include "Iridium/colors.hpp"

namespace ir {
	class RenderTarget;

	namespace render {
		class VertexRenderer;

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

		/// @brief Generic base class for vertex-based drawable objects. Can be freely derived by the user.
		/// All mutators should return a reference to this, allowing for chaining mutators.
		class Shape {
		public:
			/// @brief Draws the object on the given render target.
			virtual void render(ir::render::VertexRenderer& renderer) const = 0;

			Shape& setPosition(ir::Vector pos); ///< @brief Sets screen position, in pixels
			Shape& setAngle(float angle); ///< @brief Sets rotation about the anchor point, CW in radians (0 degrees is up)
			Shape& setAnchor(ir::Vector anchor); ///< @brief Sets anchor point, in pixels
			Shape& setAnchor(float x, float y); ///< @brief Sets anchor point, in pixels
			Shape& setColor(sf::Color color); ///< @brief Sets object color
			Shape& setMode(ir::render::Mode mode); ///< @brief Sets rendering mode

			inline ir::Vector getPosition() const { return position_; } ///< @return Screen position, in pixels
			inline float getAngle() const { return angle_; } ///< @return Rotation about the anchor point, in radians
			inline ir::Vector getAnchor() const { return anchor_; } ///< @return Anchor point, in pixels
			inline sf::Color getColor() const { return color_; } ///< @return Object color
			inline ir::render::Mode getMode() const { return mode_; } ///< @return Rendering mode

		protected:
			ir::Vector position_ { 0.f, 0.f }; ///< Screen position
			float angle_ { 0.f }; ///< Angle, in radians
			ir::Vector anchor_ { 0.f, 0.f }; ///< Anchor point
			sf::Color color_ { sf::Color::White }; ///< Object color
			ir::render::Mode mode_ { ir::render::Mode::WIREFRAME }; ///< Rendering mode
		};
	}
}

#endif // IRIDIUM_RENDERING_SHAPE_HPP_