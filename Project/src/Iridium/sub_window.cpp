#include "Iridium/sub_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/rendering/shapes.hpp"

namespace Ir {
	SubWindow::SubWindow(Ir::Vector _size) {
		this->AllocateResources(_size);
	}
	
	void SubWindow::SetSize(Ir::Vector _size) {
		this->AllocateResources(_size);
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

	void SubWindow::Render(sf::Drawable &_drawable, const sf::Texture* _texture) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
			
		this->m_renderTexture->draw(_drawable, _texture);
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
		
		this->m_rect->SetPosition(this->m_position + Ir::Vector{0.f, this->GetSize().y});
		_render_target.Render(*this->m_rect);
		if (this->m_renderFrame) {
			this->m_frame->SetPosition(this->m_position + Ir::Vector(1.f, 0.f));
			_render_target.Render(*this->m_frame);
		}
	}

	void SubWindow::AllocateResources() {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		this->AllocateResources(Ir::Vector::FromSFMLVector(this->m_renderTexture->getSize()));
	}

	void SubWindow::AllocateResources(Ir::Vector _size) {
		if (this->m_renderTexture != nullptr)
			this->m_renderTexture.reset();
		this->m_renderTexture = std::make_unique<sf::RenderTexture>(sf::Vector2u{_size});
		this->ConfigureRect(_size);
		this->ConfigureFrame(_size);
	}

	void SubWindow::ConfigureRect(Ir::Vector _size) {
		if (this->m_rect == nullptr)
			this->m_rect = std::make_unique<Ir::Render::Quad>();

		this->m_rect->SetTexture(this->m_renderTexture->getTexture());
		this->m_rect->SetSize(_size.MirrorX());
	}
	
	void SubWindow::ConfigureFrame(Ir::Vector _size) {
		if (this->m_frame == nullptr)
			this->m_frame = std::make_unique<Ir::Render::Rectangle>();
		this->m_frame->SetSize(_size.x - 1.f, _size.y - 1.f); /// -1 on each dimension so it precisely lines up with the edges of the subwindow
	}

	void SubWindow::SetRenderFrameColor(sf::Color _clr) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		this->m_frame->SetColor(_clr);
	}
}