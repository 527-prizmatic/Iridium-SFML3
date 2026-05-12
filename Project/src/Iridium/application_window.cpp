#include "Iridium/application_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/sub_window.hpp"

/// @todo Add support for other OSes
#if defined(_WIN32)
#include <windows.h>
#endif

namespace iridium {
	ApplicationWindow::ApplicationWindow(iridium::Vector _size) {
		allocateResources(sf::Vector2u{ _size });
	}
	
	void ApplicationWindow::setSize(iridium::Vector _size) {
		allocateResources(sf::Vector2u{ _size });
	}

	iridium::Vector ApplicationWindow::getSize() {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		return iridium::Vector::fromSFMLVector(m_renderWindow->getSize());
	}

	void ApplicationWindow::clear(sf::Color _fill_color) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		m_renderWindow->clear(sf::Color::Transparent);
		renderTexture_->clear(_fill_color);
	}

	void ApplicationWindow::render(sf::Drawable &_drawable, const sf::Texture* _texture) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		renderTexture_->draw(_drawable, _texture);
	}

	void ApplicationWindow::render(iridium::render::Shape& _shape) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		_shape.render(*this);
	}

	void ApplicationWindow::render(iridium::RenderTarget &_render_target) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		/// @todo Placeholder. Extract render target's internal buffer data and draw it onto renderTexture_
	//	_render_target.setSize(_render_target.GetSize());

		if (iridium::SubWindow* sub = dynamic_cast<iridium::SubWindow*>(&_render_target)) {
			sub->flushToTarget(*this);
		}
	}

	void ApplicationWindow::Flush() {
		m_renderWindow->draw(*rect_);
		m_renderWindow->display();
	}

	void ApplicationWindow::Minimize() {
		sf::WindowHandle handle { m_renderWindow->getNativeHandle() };

/// @todo Add support for other OSes, probably
#if defined(_WIN32)
		PostMessage(handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		std::cout << handle;
#endif
	}

	void ApplicationWindow::ReduceBackgroundResourceUsage() {
		if (HasFocus())
			m_renderWindow->setFramerateLimit(m_fps);
		else
			m_renderWindow->setFramerateLimit(10u);
	}

	void ApplicationWindow::allocateResources() {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		allocateResources(m_renderWindow->getSize());
	}

	void ApplicationWindow::allocateResources(sf::Vector2u _size) {
		if (m_renderWindow != nullptr) m_renderWindow.reset();
		if (renderTexture_ != nullptr) renderTexture_.reset();

		sf::VideoMode vmode { sf::VideoMode::getDesktopMode() };
		vmode.size = _size;
		m_renderWindow = std::make_shared<sf::RenderWindow>(vmode, "Window", sf::Style::None);
		renderTexture_ = std::make_unique<sf::RenderTexture>(_size);
		if (rect_ == nullptr) rect_ = std::make_unique<sf::RectangleShape>(sf::Vector2f{_size});
		configureRect();
	}

	void ApplicationWindow::configureRect() {
		rect_->setTexture(&renderTexture_->getTexture(), true);
		rect_->setScale({1.f, -1.f});
		rect_->setPosition({0.f, static_cast<float>(getSize().y)});
	}

	void ApplicationWindow::SetFPS(unsigned int _fps) {
		m_fps = _fps;
		if (isValid())
			m_renderWindow->setFramerateLimit(m_fps);
	}

	[[nodiscard]] sf::Vector2i ApplicationWindow::GetMouseCursorPosition() const {
		if (m_renderWindow)
			return sf::Mouse::getPosition(*m_renderWindow);
		else
			return sf::Mouse::getPosition();
	}

	[[nodiscard]] const std::optional<sf::Event> ApplicationWindow::PollNextEvent() {
		if (!isValid())
			return std::optional<sf::Event>();
			
		return m_renderWindow->pollEvent();
	}
	
	void ApplicationWindow::SetTitle(std::string _title) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		m_renderWindow->setTitle(_title);
		m_windowTitle = _title;
	}
		
	std::string ApplicationWindow::GetTitle() {
		return m_windowTitle;
	}
}