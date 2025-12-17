#include "Iridium/rendering/shapes.hpp"

namespace Ir {
	namespace Render {
		namespace _priv {
			std::unique_ptr<sf::VertexArray> _vertices;

			/// @brief Tries to initialize the internal vertex array used for rendering.
			/// Does strictly nothing if it was already initialized.
			void TryInitialize() {
				if (!Ir::Render::_priv::_vertices)
					Ir::Render::_priv::_vertices = std::make_unique<sf::VertexArray>();
			}

			void Reset(sf::PrimitiveType _type = sf::PrimitiveType::LineStrip) {
				Ir::Render::_priv::_vertices->setPrimitiveType(_type);
				Ir::Render::_priv::_vertices->clear();
			}

			void Flush(Ir::RenderTarget& _target) {
				_target.Render(*Ir::Render::_priv::_vertices);
			}

			void AddSinglePoint(Ir::Vector _position, sf::Color _color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), _color };
				Ir::Render::_priv::_vertices->append(vertex);
			}

			void AddDoublePoint(Ir::Vector _position, sf::Color _color = sf::Color::White) {
				sf::Vertex vertex { static_cast<sf::Vector2f>(_position), _color };
				Ir::Render::_priv::_vertices->append(vertex);
				Ir::Render::_priv::_vertices->append(vertex);
			}
		}

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

			Ir::Vector absolutePosition { this->GetPosition() - this->GetAnchor() };
			Ir::Render::_priv::AddSinglePoint(absolutePosition, this->GetColor());
			Ir::Render::_priv::AddSinglePoint(absolutePosition + Ir::Vector{ this->m_size.x, 0.f }, this->GetColor());
			Ir::Render::_priv::AddSinglePoint(absolutePosition + Ir::Vector{ this->m_size.x, this->m_size.y }, this->GetColor());
			Ir::Render::_priv::AddSinglePoint(absolutePosition + Ir::Vector{ 0.f, this->m_size.y }, this->GetColor());
			Ir::Render::_priv::AddSinglePoint(absolutePosition, this->GetColor());

			Ir::Render::_priv::Flush(_target);
		}
	}
}