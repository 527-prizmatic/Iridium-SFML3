#include "Iridium/rendering/shapes.hpp"
#include "Iridium/math.hpp"
#include "Iridium/render_target.hpp"

namespace ir {
	namespace render {
		// @todo Refactor this (needs to be public to other rendering files)
		namespace detail {
			std::unique_ptr<sf::VertexArray> g_vertices;

			/// @brief Tries to initialize the internal vertex array used for rendering.
			/// Does strictly nothing if it was already initialized.
			void tryInitialize() {
				if (!ir::render::detail::g_vertices) {
					ir::render::detail::g_vertices = std::make_unique<sf::VertexArray>();
				}
			}

			void reset(sf::PrimitiveType type = sf::PrimitiveType::LineStrip) {
				ir::render::detail::g_vertices->setPrimitiveType(type);
				ir::render::detail::g_vertices->clear();
			}

			void flush(ir::RenderTarget& target, const sf::Texture* texture = nullptr) {
				target.render(*ir::render::detail::g_vertices, texture);
			}

			/// @brief Adds a point with given position and color to the internal rendering buffer.
			void addSinglePoint(ir::Vector position, sf::Color color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(position), color };
				ir::render::detail::g_vertices->append(vertex);
			}

			/// @brief Adds a point with given position and texture coordinate to the internal rendering buffer.
			void addSinglePoint(ir::Vector position, ir::Vector textureCoord) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(position), sf::Color::White, sf::Vector2f{ textureCoord } };
				ir::render::detail::g_vertices->append(vertex);
			}

			/// @brief Adds a point with given position and color to the internal rendering buffer.
			/// This functions adds it twice, for use with sf::PrimitiveType::Lines.
			void addDoublePoint(ir::Vector position, sf::Color color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(position), color };
				ir::render::detail::g_vertices->append(vertex);
				ir::render::detail::g_vertices->append(vertex);
			}

			/// @brief Adds the first vertex of the buffer back at the end, for closing shapes.
			void closeShape() {
				ir::render::detail::g_vertices->append(ir::render::detail::g_vertices->operator[](0));
			}
		}

		/// Shape

		Shape& Shape::setPosition(ir::Vector pos) {
			position_ = pos;
			return *this;
		}

		Shape& Shape::setAngle(float angle) {
			angle_ = angle;
			return *this;
		}

		Shape& Shape::setAnchor(ir::Vector anchor) {
			anchor_ = anchor;
			return *this;
		}

		Shape& Shape::setAnchor(float x, float y) {
			anchor_ = ir::Vector { x, y };
			return *this;
		}

		Shape& Shape::setColor(sf::Color color) {
			color_ = color;
			return *this;
		}

		Shape &Shape::setMode(ir::render::Mode mode) {
			mode_ = mode;
			return *this;
		}
		
		/// Rectangle

		Rectangle &Rectangle::setSize(ir::Vector size) {
			size_ = size;
			return *this;
		}

		Rectangle &Rectangle::setSize(float x, float y) {
			size_ = ir::Vector { x, y };
			return *this;
		}

		Rectangle& Rectangle::setCorners(ir::Vector topLeft, ir::Vector bottomRight) {
			setPosition(topLeft);
			setSize(bottomRight - topLeft);
			return *this;
		}

		void Rectangle::render(ir::RenderTarget& target) const {
			ir::render::detail::tryInitialize();
			
			ir::Vector point1 { -getAnchor() };
			ir::Vector point2 { point1 + ir::Vector{ size_.x, 0.f } };
			ir::Vector point3 { point1 + size_ };
			ir::Vector point4 { point1 + ir::Vector{ 0.f, size_.y } };
			
			if (getMode() == ir::render::Mode::WIREFRAME) {
				ir::render::detail::reset(sf::PrimitiveType::LineStrip);

				ir::render::detail::addSinglePoint(getPosition() + point1.rotate(getAngle()), getColor());
				ir::render::detail::addSinglePoint(getPosition() + point2.rotate(getAngle()), getColor());
				ir::render::detail::addSinglePoint(getPosition() + point3.rotate(getAngle()), getColor());
				ir::render::detail::addSinglePoint(getPosition() + point4.rotate(getAngle()), getColor());
				ir::render::detail::closeShape();
			}
			
			else if (getMode() == ir::render::Mode::SOLID) {
				ir::render::detail::reset(sf::PrimitiveType::TriangleStrip);

				ir::render::detail::addSinglePoint(getPosition() + point1.rotate(getAngle()), getColor());
				ir::render::detail::addSinglePoint(getPosition() + point2.rotate(getAngle()), getColor());
				ir::render::detail::addSinglePoint(getPosition() + point4.rotate(getAngle()), getColor());
				ir::render::detail::addSinglePoint(getPosition() + point3.rotate(getAngle()), getColor());
			}

			ir::render::detail::flush(target);
		}

		/// Quad

		Rectangle& Quad::setUVs(ir::Vector topLeft, ir::Vector size) {
			uv_ = ir::render::UV(topLeft, size);
			return *this;
		}

		Rectangle& Quad::setUVs(ir::render::UV uv) {
			uv_ = uv;
			return *this;
		}

		Rectangle& Quad::setTexture(const sf::Texture& texture) {
			texture_ = &texture;
			setSize(ir::Vector::fromSFMLVector(texture.getSize()));
			uv_ = ir::render::UV{ ir::Vector::kZero, getSize() };

			return *this;
		}

		void Quad::render(ir::RenderTarget& target) const {
			if (!texture_) {
				return;
			}
			
			ir::render::detail::tryInitialize();
			ir::render::detail::reset(sf::PrimitiveType::TriangleStrip);

			ir::Vector pointTL { -getAnchor() };
			ir::Vector pointTR { pointTL + ir::Vector{ getSize().x, 0.f } };
			ir::Vector pointBR { pointTL + ir::Vector{ getSize().x, getSize().y } };
			ir::Vector pointBL { pointTL + ir::Vector{ 0.f, getSize().y } };

			ir::render::detail::addSinglePoint(getPosition() + pointTL.rotate(getAngle()), uv_.topLeftCorner());
			ir::render::detail::addSinglePoint(getPosition() + pointTR.rotate(getAngle()), uv_.topRightCorner());
			ir::render::detail::addSinglePoint(getPosition() + pointBL.rotate(getAngle()), uv_.bottomLeftCorner());
			ir::render::detail::addSinglePoint(getPosition() + pointBR.rotate(getAngle()), uv_.bottomRightCorner());

			ir::render::detail::flush(target, texture_);
		}

		/// Circle
			
		Circle& Circle::setRadius(float rds) {
			radius_ = rds;
			return *this;
		}

		Circle& Circle::setVertexCount(unsigned int count) {
			vertexCount_ = count;
			vertexAngle_ = ir::math::tau / static_cast<float>(vertexCount_);
			return *this;
		}

		void Circle::render(ir::RenderTarget& target) const {
			ir::render::detail::tryInitialize();
			ir::render::detail::reset();

			ir::Vector center = getPosition() - getAnchor();

			for (unsigned int i = 0; i < vertexCount_; i++) {
				ir::Vector vertexPos { ir::Vector::polar(radius_, getAngle() + vertexAngle_ * static_cast<float>(i)) };
				ir::render::detail::addSinglePoint(center + vertexPos, getColor());
			}
			ir::render::detail::closeShape();

			ir::render::detail::flush(target);
		}
	}
}