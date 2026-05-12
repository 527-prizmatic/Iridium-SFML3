#include "Iridium/rendering/shapes.hpp"
#include "Iridium/math.hpp"
#include "Iridium/render_target.hpp"

namespace iridium {
	namespace render {
		namespace detail {
			std::unique_ptr<sf::VertexArray> g_vertices;

			/// @brief Tries to initialize the internal vertex array used for rendering.
			/// Does strictly nothing if it was already initialized.
			void TryInitialize() {
				if (!iridium::render::detail::g_vertices)
					iridium::render::detail::g_vertices = std::make_unique<sf::VertexArray>();
			}

			void reset(sf::PrimitiveType _type = sf::PrimitiveType::LineStrip) {
				iridium::render::detail::g_vertices->setPrimitiveType(_type);
				iridium::render::detail::g_vertices->clear();
			}

			void Flush(iridium::RenderTarget& _target, const sf::Texture* _texture = nullptr) {
				_target.render(*iridium::render::detail::g_vertices, _texture);
			}

			/// @brief Adds a point with given position and color to the internal rendering buffer.
			void AddSinglePoint(iridium::Vector _position, sf::Color _color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), _color };
				iridium::render::detail::g_vertices->append(vertex);
			}

			/// @brief Adds a point with given position and texture coordinate to the internal rendering buffer.
			void AddSinglePoint(iridium::Vector _position, iridium::Vector _texture_coord) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), sf::Color::White, sf::Vector2f{ _texture_coord } };
				iridium::render::detail::g_vertices->append(vertex);
			}

			/// @brief Adds a point with given position and color to the internal rendering buffer.
			/// This functions adds it twice, for use with sf::PrimitiveType::Lines.
			void AddDoublePoint(iridium::Vector _position, sf::Color _color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), _color };
				iridium::render::detail::g_vertices->append(vertex);
				iridium::render::detail::g_vertices->append(vertex);
			}

			/// @brief Adds the first vertex of the buffer back at the end, for closing shapes.
			void CloseShape() {
				iridium::render::detail::g_vertices->append(iridium::render::detail::g_vertices->operator[](0));
			}
		}

		/// Shape

		Shape& Shape::setPosition(iridium::Vector _pos) {
			position_ = _pos;
			return *this;
		}

		Shape& Shape::setAngle(float _angle) {
			angle_ = _angle;
			return *this;
		}

		Shape& Shape::setAnchor(iridium::Vector _anchor) {
			anchor_ = _anchor;
			return *this;
		}

		Shape& Shape::setAnchor(float _x, float _y) {
			anchor_ = iridium::Vector { _x, _y };
			return *this;
		}

		Shape& Shape::setColor(sf::Color _color) {
			color_ = _color;
			return *this;
		}

		Shape &Shape::setMode(iridium::render::Mode _mode) {
			mode_ = _mode;
			return *this;
		}
		
		/// Rectangle

		Rectangle &Rectangle::setSize(iridium::Vector _size) {
			size_ = _size;
			return *this;
		}

		Rectangle &Rectangle::setSize(float _x, float _y) {
			size_ = iridium::Vector { _x, _y };
			return *this;
		}

		Rectangle& Rectangle::setCorners(iridium::Vector _top_left, iridium::Vector _bottom_right) {
			setPosition(_top_left);
			setSize(_bottom_right - _top_left);
			return *this;
		}

		void Rectangle::render(iridium::RenderTarget& _target) const {
			iridium::render::detail::TryInitialize();
			
			iridium::Vector point1 { -getAnchor() };
			iridium::Vector point2 { point1 + iridium::Vector{ size_.x, 0.f } };
			iridium::Vector point3 { point1 + size_ };
			iridium::Vector point4 { point1 + iridium::Vector{ 0.f, size_.y } };
			
			if (getMode() == iridium::render::Mode::WIREFRAME) {
				iridium::render::detail::reset(sf::PrimitiveType::LineStrip);

				iridium::render::detail::AddSinglePoint(getPosition() + point1.rotate(getAngle()), getColor());
				iridium::render::detail::AddSinglePoint(getPosition() + point2.rotate(getAngle()), getColor());
				iridium::render::detail::AddSinglePoint(getPosition() + point3.rotate(getAngle()), getColor());
				iridium::render::detail::AddSinglePoint(getPosition() + point4.rotate(getAngle()), getColor());
				iridium::render::detail::CloseShape();
			}
			
			else if (getMode() == iridium::render::Mode::SOLID) {
				iridium::render::detail::reset(sf::PrimitiveType::TriangleStrip);

				iridium::render::detail::AddSinglePoint(getPosition() + point1.rotate(getAngle()), getColor());
				iridium::render::detail::AddSinglePoint(getPosition() + point2.rotate(getAngle()), getColor());
				iridium::render::detail::AddSinglePoint(getPosition() + point4.rotate(getAngle()), getColor());
				iridium::render::detail::AddSinglePoint(getPosition() + point3.rotate(getAngle()), getColor());
			}

			iridium::render::detail::Flush(_target);
		}

		/// Quad

		Rectangle& Quad::setUVs(iridium::Vector _top_left, iridium::Vector _size) {
			uv_ = iridium::render::UV(_top_left, _size);
			return *this;
		}

		Rectangle& Quad::setUVs(iridium::render::UV _uv) {
			uv_ = _uv;
			return *this;
		}

		Rectangle& Quad::setTexture(const sf::Texture& _texture) {
			texture_ = &_texture;
			setSize(iridium::Vector::fromSFMLVector(_texture.getSize()));
			uv_ = iridium::render::UV{ iridium::Vector::kZero, getSize() };

			return *this;
		}

		void Quad::render(iridium::RenderTarget& _target) const {
			if (!texture_)
				return;
			
			iridium::render::detail::TryInitialize();
			iridium::render::detail::reset(sf::PrimitiveType::TriangleStrip);

			iridium::Vector pointTL { -getAnchor() };
			iridium::Vector pointTR { pointTL + iridium::Vector{ getSize().x, 0.f } };
			iridium::Vector pointBR { pointTL + iridium::Vector{ getSize().x, getSize().y } };
			iridium::Vector pointBL { pointTL + iridium::Vector{ 0.f, getSize().y } };

			iridium::render::detail::AddSinglePoint(getPosition() + pointTL.rotate(getAngle()), uv_.topLeftCorner());
			iridium::render::detail::AddSinglePoint(getPosition() + pointTR.rotate(getAngle()), uv_.topRightCorner());
			iridium::render::detail::AddSinglePoint(getPosition() + pointBL.rotate(getAngle()), uv_.bottomLeftCorner());
			iridium::render::detail::AddSinglePoint(getPosition() + pointBR.rotate(getAngle()), uv_.bottomRightCorner());

			iridium::render::detail::Flush(_target, texture_);
		}

		/// Circle
			
		Circle& Circle::SetRadius(float _rds) {
			m_radius = _rds;
			return *this;
		}

		Circle& Circle::SetVertexCount(unsigned int _count) {
			m_vertexCount = _count;
			m_vertexAngle = iridium::Math::tau / static_cast<float>(m_vertexCount);
			return *this;
		}

		void Circle::render(iridium::RenderTarget& _target) const {
			iridium::render::detail::TryInitialize();
			iridium::render::detail::reset();

			iridium::Vector center = getPosition() - getAnchor();

			for (unsigned int i = 0; i < m_vertexCount; i++) {
				iridium::Vector vertexPos { iridium::Vector::polar(m_radius, getAngle() + m_vertexAngle * static_cast<float>(i)) };
				iridium::render::detail::AddSinglePoint(center + vertexPos, getColor());
			}
			iridium::render::detail::CloseShape();

			iridium::render::detail::Flush(_target);
		}
	}
}