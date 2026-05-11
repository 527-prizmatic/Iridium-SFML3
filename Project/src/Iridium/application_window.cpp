#include "Iridium/application_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/sub_window.hpp"

/// @todo Add support for other OSes
#if defined(_WIN32)
#include <windows.h>
#endif

namespace ir {
	ApplicationWindow::ApplicationWindow(ir::Vector size) {
		allocateResources(sf::Vector2u{ size });
	}
	
	void ApplicationWindow::setSize(ir::Vector size) {
		allocateResources(sf::Vector2u{ size });
	}

	ir::Vector ApplicationWindow::getSize() {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		return ir::Vector::fromSFMLVector(renderWindow_->getSize());
	}

	void ApplicationWindow::clear(sf::Color fillColor) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		renderWindow_->clear(sf::Color::Transparent);
		renderTexture_->clear(fillColor);
	}

	void ApplicationWindow::render(sf::Drawable &drawable, const sf::Texture* texture) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		renderTexture_->draw(drawable, texture);
	}

	void ApplicationWindow::render(ir::render::Shape& shape) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		shape.render(*this);
	}

	void ApplicationWindow::render(ir::RenderTarget &renderTarget) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		/// @todo Placeholder. Extract render target's internal buffer data and draw it onto renderTexture_
		//	renderTarget.setSize(renderTarget.GetSize());

		if (ir::SubWindow* sub = dynamic_cast<ir::SubWindow*>(&renderTarget)) {
			sub->flushToTarget(*this);
		}
	}

	void ApplicationWindow::flush() {
		renderWindow_->draw(*rect_);
		renderWindow_->display();
	}

	void ApplicationWindow::minimize() {
		sf::WindowHandle handle { renderWindow_->getNativeHandle() };

/// @todo Add support for other OSes, probably
#if defined(_WIN32)
		PostMessage(handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		std::cout << handle;
#endif
	}

	void ApplicationWindow::reduceBackgroundResourceUsage() {
		if (hasFocus())
			renderWindow_->setFramerateLimit(fps_);
		else
			renderWindow_->setFramerateLimit(10u);
	}

	void ApplicationWindow::allocateResources() {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		allocateResources(renderWindow_->getSize());
	}

	void ApplicationWindow::allocateResources(sf::Vector2u size) {
		if (renderWindow_ != nullptr) renderWindow_.reset();
		if (renderTexture_ != nullptr) renderTexture_.reset();

		sf::VideoMode vmode { sf::VideoMode::getDesktopMode() };
		vmode.size = size;
		renderWindow_ = std::make_shared<sf::RenderWindow>(vmode, "Window", sf::Style::None);
		renderTexture_ = std::make_unique<sf::RenderTexture>(size);
		if (rect_ == nullptr) rect_ = std::make_unique<sf::RectangleShape>(sf::Vector2f{size});
		configureRect();
	}

	void ApplicationWindow::configureRect() {
		rect_->setTexture(&renderTexture_->getTexture(), true);
		rect_->setScale({1.f, -1.f});
		rect_->setPosition({0.f, static_cast<float>(getSize().y)});
	}

	void ApplicationWindow::setFPS(unsigned int fps) {
		fps_ = fps;
		if (isValid())
			renderWindow_->setFramerateLimit(fps_);
	}

	[[nodiscard]] sf::Vector2i ApplicationWindow::getMouseCursorPosition() const {
		if (renderWindow_)
			return sf::Mouse::getPosition(*renderWindow_);
		else
			return sf::Mouse::getPosition();
	}

	[[nodiscard]] const std::optional<sf::Event> ApplicationWindow::pollNextEvent() {
		if (!isValid())
			return std::optional<sf::Event>();
			
		return renderWindow_->pollEvent();
	}
	
	void ApplicationWindow::setTitle(std::string title) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		renderWindow_->setTitle(title);
		windowTitle_ = title;
	}
		
	std::string ApplicationWindow::getTitle() {
		return windowTitle_;
	}
}