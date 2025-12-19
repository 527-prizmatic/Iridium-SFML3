#include "Iridium/sub_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/rendering/shapes.hpp"

namespace Ir {
	SubWindow::SubWindow(Ir::Vector _size) {
		this->AllocateResources(sf::Vector2u{ _size });
	}
	
	void SubWindow::SetSize(Ir::Vector _size) {
		this->AllocateResources(sf::Vector2u{ _size });
	}

	Ir::Vector SubWindow::GetSize() {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		return Ir::Vector::FromSFMLVector(this->m_renderTexture->getSize());
	}

	void SubWindow::Clear(sf::Color _fill_color) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		this->m_renderTexture->clear(_fill_color);
	}

	void SubWindow::Render(sf::Drawable &_drawable) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		this->m_renderTexture->draw(_drawable);
	}

	void SubWindow::Render(Ir::Render::Shape& _shape) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		_shape.Render(*this);
	}

	void SubWindow::Render(Ir::RenderTarget &_render_target) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		if (Ir::SubWindow* sub = dynamic_cast<Ir::SubWindow*>(&_render_target)) {
			sub->FlushToTarget(*this);
		}
	}
	
	void SubWindow::FlushToTarget(Ir::RenderTarget& _render_target) {
		if (!_render_target.IsValid() || !this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		this->m_rect->setPosition(sf::Vector2f { this->m_position });
		_render_target.Render(*this->m_rect);
		if (this->m_renderFrame) {
			Ir::Render::Rectangle rect;
			rect.SetSize(this->GetSize() - Ir::Vector(1.f, 1.f));
			rect.SetPosition(this->m_position + Ir::Vector(1.f, 0.f));
			rect.SetColor(sf::Color(0, 255, 0, 64));
			_render_target.Render(rect);
		}
	}

	void SubWindow::AllocateResources() {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		this->AllocateResources(this->m_renderTexture->getSize());
	}

	void SubWindow::AllocateResources(sf::Vector2u _size) {
		if (this->m_renderTexture != nullptr) this->m_renderTexture.reset();
		this->m_renderTexture = std::make_unique<sf::RenderTexture>(_size);
		if (this->m_rect == nullptr) this->m_rect = std::make_unique<sf::RectangleShape>(sf::Vector2f{_size});
		this->ConfigureRect();
	}

	void SubWindow::ConfigureRect() {
		this->m_rect->setTexture(&this->m_renderTexture->getTexture(), true);
	//	this->m_rect->setScale({1.f, -1.f});
	//	this->m_rect->setPosition({0.f, static_cast<float>(this->GetSize().y)});
	}
}