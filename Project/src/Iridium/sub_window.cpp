#include "Iridium/sub_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/rendering/shapes.hpp"

namespace iridium {
	SubWindow::SubWindow(iridium::Vector size_) {
		allocateResources(size_);
	}
	
	void SubWindow::setSize(iridium::Vector size_) {
		allocateResources(size_);
	}

	iridium::Vector SubWindow::getSize() {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		return iridium::Vector::fromSFMLVector(renderTexture_->getSize());
	}

	void SubWindow::clear(sf::Color _fill_color) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		renderTexture_->clear(_fill_color);
	}

	void SubWindow::render(sf::Drawable &_drawable, const sf::Texture* _texture) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
			
		renderTexture_->draw(_drawable, _texture);
	}

	void SubWindow::render(iridium::render::Shape& _shape) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		_shape.render(*this);
	}

	void SubWindow::render(iridium::RenderTarget &renderTarget) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		if (iridium::SubWindow* sub = dynamic_cast<iridium::SubWindow*>(&renderTarget)) {
			sub->flushToTarget(*this);
		}
	}
	
	void SubWindow::flushToTarget(iridium::RenderTarget& renderTarget) {
		if (!renderTarget.isValid() || !isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		rect_->setPosition(position_ + iridium::Vector{0.f, getSize().y});
		renderTarget.render(*rect_);
		if (renderFrame_) {
			frame_->setPosition(position_ + iridium::Vector(1.f, 0.f));
			renderTarget.render(*frame_);
		}
	}

	void SubWindow::allocateResources() {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};

		allocateResources(iridium::Vector::fromSFMLVector(renderTexture_->getSize()));
	}

	void SubWindow::allocateResources(iridium::Vector _size) {
		if (renderTexture_ != nullptr)
			renderTexture_.reset();
		renderTexture_ = std::make_unique<sf::RenderTexture>(sf::Vector2u{_size});
		configureRect(_size);
		configureFrame(_size);
	}

	void SubWindow::configureRect(iridium::Vector _size) {
		if (rect_ == nullptr)
			rect_ = std::make_unique<iridium::render::Quad>();

		rect_->setTexture(renderTexture_->getTexture());
		rect_->setSize(_size.mirrorX());
	}
	
	void SubWindow::configureFrame(iridium::Vector _size) {
		if (frame_ == nullptr)
			frame_ = std::make_unique<iridium::render::Rectangle>();
		frame_->setSize(_size.x - 1.f, _size.y - 1.f); /// -1 on each dimension so it precisely lines up with the edges of the subwindow
	}

	void SubWindow::setRenderFrameColor(sf::Color _clr) {
		if (!isValid())
			throw iridium::Exceptions::InvalidRenderTarget{};
		
		frame_->setColor(_clr);
	}
}