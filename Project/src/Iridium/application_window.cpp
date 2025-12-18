#include "Iridium/application_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/sub_window.hpp"

namespace Ir {
	ApplicationWindow::ApplicationWindow(Ir::Vector _size) {
		this->AllocateResources(sf::Vector2u{ _size });
	}
	
	void ApplicationWindow::SetSize(Ir::Vector _size) {
		this->AllocateResources(sf::Vector2u{ _size });
	}

	Ir::Vector ApplicationWindow::GetSize() {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		return Ir::Vector::FromSFMLVector(this->m_renderWindow->getSize());
	}

	void ApplicationWindow::Clear(sf::Color _fill_color) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		this->m_renderWindow->clear(sf::Color::Transparent);
		this->m_renderTexture->clear(_fill_color);
	}

	void ApplicationWindow::Render(sf::Drawable &_drawable) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		this->m_renderTexture->draw(_drawable);
	}

	void ApplicationWindow::Render(Ir::Render::Shape& _shape) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		_shape.Render(*this);
	}

	void ApplicationWindow::Render(Ir::RenderTarget &_render_target) {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};
		
		/// @todo Placeholder. Extract render target's internal buffer data and draw it onto m_renderTexture
	//	_render_target.SetSize(_render_target.GetSize());

		if (Ir::SubWindow* sub = dynamic_cast<Ir::SubWindow*>(&_render_target)) {
			sub->FlushToTarget(*this);
		}
	}

	void ApplicationWindow::Flush() {
		this->m_renderWindow->draw(*this->m_rect);
		this->m_renderWindow->display();
	}

	void ApplicationWindow::AllocateResources() {
		if (!this->IsValid())
			throw Ir::Exceptions::InvalidRenderTarget{};

		this->AllocateResources(this->m_renderWindow->getSize());
	}

	void ApplicationWindow::AllocateResources(sf::Vector2u _size) {
		if (this->m_renderWindow != nullptr) this->m_renderWindow.reset();
		if (this->m_renderTexture != nullptr) this->m_renderTexture.reset();

		sf::VideoMode vmode { sf::VideoMode::getDesktopMode() };
		vmode.size = _size;
		this->m_renderWindow = std::make_unique<sf::RenderWindow>(vmode, "Window", sf::Style::None);
		this->m_renderTexture = std::make_unique<sf::RenderTexture>(_size);
		if (this->m_rect == nullptr) this->m_rect = std::make_unique<sf::RectangleShape>(sf::Vector2f{_size});
		this->ConfigureRect();
	}

	void ApplicationWindow::ConfigureRect() {
		this->m_rect->setTexture(&this->m_renderTexture->getTexture(), true);
		this->m_rect->setScale({1.f, -1.f});
		this->m_rect->setPosition({0.f, static_cast<float>(this->GetSize().y)});
	}

	void ApplicationWindow::SetFPS(unsigned int _fps) {
		this->m_fps = _fps;
		if (this->IsValid())
			this->m_renderWindow->setFramerateLimit(this->m_fps);
	}

	unsigned int ApplicationWindow::GetFPS() {
		return this->m_fps;
	}
}