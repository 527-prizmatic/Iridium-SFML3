#include "Iridium/rendering/shapes.hpp"
#include "Iridium/math.hpp"
#include "Iridium/render_target.hpp"

namespace Ir {
	namespace Render {
		namespace _priv {
			std::unique_ptr<sf::VertexArray> g_vertices;

			/// @brief Tries to initialize the internal vertex array used for rendering.
			/// Does strictly nothing if it was already initialized.
			void TryInitialize() {
				if (!Ir::Render::_priv::g_vertices)
					Ir::Render::_priv::g_vertices = std::make_unique<sf::VertexArray>();
			}

			void Reset(sf::PrimitiveType _type = sf::PrimitiveType::LineStrip) {
				Ir::Render::_priv::g_vertices->setPrimitiveType(_type);
				Ir::Render::_priv::g_vertices->clear();
			}

			void Flush(Ir::RenderTarget& _target, const sf::Texture* _texture = nullptr) {
				_target.Render(*Ir::Render::_priv::g_vertices, _texture);
			}

			/// @brief Adds a point with given position and color to the internal rendering buffer.
			void AddSinglePoint(Ir::Vector _position, sf::Color _color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), _color };
				Ir::Render::_priv::g_vertices->append(vertex);
			}

			/// @brief Adds a point with given position and texture coordinate to the internal rendering buffer.
			void AddSinglePoint(Ir::Vector _position, Ir::Vector _texture_coord) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), sf::Color::White, sf::Vector2f{ _texture_coord } };
				Ir::Render::_priv::g_vertices->append(vertex);
			}

			/// @brief Adds a point with given position and color to the internal rendering buffer.
			/// This functions adds it twice, for use with sf::PrimitiveType::Lines.
			void AddDoublePoint(Ir::Vector _position, sf::Color _color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), _color };
				Ir::Render::_priv::g_vertices->append(vertex);
				Ir::Render::_priv::g_vertices->append(vertex);
			}

			/// @brief Adds the first vertex of the buffer back at the end, for closing shapes.
			void CloseShape() {
				Ir::Render::_priv::g_vertices->append(Ir::Render::_priv::g_vertices->operator[](0));
			}
		}

		/// Shape

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

		Shape& Shape::SetAnchor(float _x, float _y) {
			this->m_anchor = Ir::Vector { _x, _y };
			return *this;
		}

		Shape& Shape::SetColor(sf::Color _color) {
			this->m_color = _color;
			return *this;
		}

		/// Rectangle

		Rectangle &Rectangle::SetSize(Ir::Vector _size) {
			this->m_size = _size;
			return *this;
		}

		Rectangle &Rectangle::SetSize(float _x, float _y) {
			this->m_size = Ir::Vector { _x, _y };
			return *this;
		}

		Rectangle& Rectangle::SetCorners(Ir::Vector _top_left, Ir::Vector _bottom_right) {
			this->SetPosition(_top_left);
			this->SetSize(_bottom_right - _top_left);
			return *this;
		}

		void Rectangle::Render(Ir::RenderTarget& _target) const {
			Ir::Render::_priv::TryInitialize();
			Ir::Render::_priv::Reset();

			Ir::Vector point1 { -this->GetAnchor() };
			Ir::Vector point2 { point1 + Ir::Vector{ this->m_size.x, 0.f } };
			Ir::Vector point3 { point1 + this->m_size };
			Ir::Vector point4 { point1 + Ir::Vector{ 0.f, this->m_size.y } };

			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + point1.Rotate(this->GetAngle()), this->GetColor());
			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + point2.Rotate(this->GetAngle()), this->GetColor());
			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + point3.Rotate(this->GetAngle()), this->GetColor());
			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + point4.Rotate(this->GetAngle()), this->GetColor());
			Ir::Render::_priv::CloseShape();

			Ir::Render::_priv::Flush(_target);
		}

		/// Quad

		Rectangle& Quad::SetUVs(Ir::Vector _top_left, Ir::Vector _size) {
			this->m_uv = Ir::Render::UV(_top_left, _size);
			return *this;
		}

		Rectangle& Quad::SetUVs(Ir::Render::UV _uv) {
			this->m_uv = _uv;
			return *this;
		}

		Rectangle& Quad::SetTexture(const sf::Texture& _texture) {
			this->m_texture = &_texture;
			this->SetSize(Ir::Vector::FromSFMLVector(_texture.getSize()));
			this->m_uv = Ir::Render::UV{ Ir::Vector::zero, this->GetSize() };

			return *this;
		}

		void Quad::Render(Ir::RenderTarget& _target) const {
			if (!this->m_texture)
				return;
			
			Ir::Render::_priv::TryInitialize();
			Ir::Render::_priv::Reset(sf::PrimitiveType::TriangleStrip);

			Ir::Vector pointTL { -this->GetAnchor() };
			Ir::Vector pointTR { pointTL + Ir::Vector{ this->GetSize().x, 0.f } };
			Ir::Vector pointBR { pointTL + Ir::Vector{ this->GetSize().x, this->GetSize().y } };
			Ir::Vector pointBL { pointTL + Ir::Vector{ 0.f, this->GetSize().y } };

			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + pointTL.Rotate(this->GetAngle()), this->m_uv.TopLeftCorner());
			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + pointTR.Rotate(this->GetAngle()), this->m_uv.TopRightCorner());
			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + pointBL.Rotate(this->GetAngle()), this->m_uv.BottomLeftCorner());
			Ir::Render::_priv::AddSinglePoint(this->GetPosition() + pointBR.Rotate(this->GetAngle()), this->m_uv.BottomRightCorner());

			Ir::Render::_priv::Flush(_target, this->m_texture);
		}

		/// Circle
			
		Circle& Circle::SetRadius(float _rds) {
			this->m_radius = _rds;
			return *this;
		}

		Circle& Circle::SetVertexCount(unsigned int _count) {
			this->m_vertexCount = _count;
			this->m_vertexAngle = Ir::Math::tau / static_cast<float>(this->m_vertexCount);
			return *this;
		}

		void Circle::Render(Ir::RenderTarget& _target) const {
			Ir::Render::_priv::TryInitialize();
			Ir::Render::_priv::Reset();

			Ir::Vector center = this->GetPosition() - this->GetAnchor();

			for (unsigned int i = 0; i < this->m_vertexCount; i++) {
				Ir::Vector vertexPos { Ir::Vector::Polar(this->m_radius, this->GetAngle() + this->m_vertexAngle * static_cast<float>(i)) };
				Ir::Render::_priv::AddSinglePoint(center + vertexPos, this->GetColor());
			}
			Ir::Render::_priv::CloseShape();

			Ir::Render::_priv::Flush(_target);
		}
	}
}