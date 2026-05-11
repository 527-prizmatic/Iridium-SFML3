#include "Iridium/sub_window.hpp"
#include "Iridium/exceptions.hpp"
#include "Iridium/rendering/shapes.hpp"

namespace ir {
	SubWindow::SubWindow(ir::Vector size_) {
		allocateResources(size_);
	}
	
	void SubWindow::setSize(ir::Vector size_) {
		allocateResources(size_);
	}

	ir::Vector SubWindow::getSize() {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		return ir::Vector::fromSFMLVector(renderTexture_->getSize());
	}

	void SubWindow::clear(sf::Color fill_color) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		renderTexture_->clear(fill_color);
	}

	void SubWindow::render(sf::Drawable &drawable, const sf::Texture* texture) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
			
		renderTexture_->draw(drawable, texture);
	}

	void SubWindow::render(ir::render::Shape& shape) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		shape.render(*this);
	}

	void SubWindow::render(ir::RenderTarget &renderTarget) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		if (ir::SubWindow* sub = dynamic_cast<ir::SubWindow*>(&renderTarget)) {
			sub->flushToTarget(*this);
		}
	}
	
	void SubWindow::flushToTarget(ir::RenderTarget& renderTarget) {
		if (!renderTarget.isValid() || !isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		rect_->setPosition(position_ + ir::Vector{0.f, getSize().y});
		renderTarget.render(*rect_);
		if (renderFrame_) {
			frame_->setPosition(position_ + ir::Vector(1.f, 0.f));
			renderTarget.render(*frame_);
		}
	}

	void SubWindow::allocateResources() {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};

		allocateResources(ir::Vector::fromSFMLVector(renderTexture_->getSize()));
	}

	void SubWindow::allocateResources(ir::Vector size) {
		if (renderTexture_ != nullptr)
			renderTexture_.reset();
		renderTexture_ = std::make_unique<sf::RenderTexture>(sf::Vector2u{size});
		configureRect(size);
		configureFrame(size);
	}

	void SubWindow::configureRect(ir::Vector size) {
		if (rect_ == nullptr)
			rect_ = std::make_unique<ir::render::Quad>();

		rect_->setTexture(renderTexture_->getTexture());
		rect_->setSize(size.mirrorX());
	}
	
	void SubWindow::configureFrame(ir::Vector size) {
		if (frame_ == nullptr)
			frame_ = std::make_unique<ir::render::Rectangle>();
		frame_->setSize(size.x - 1.f, size.y - 1.f); /// -1 on each dimension so it precisely lines up with the edges of the subwindow
	}

	void SubWindow::setRenderFrameColor(sf::Color clr) {
		if (!isValid())
			throw ir::Exceptions::InvalidRenderTarget{};
		
		frame_->setColor(clr);
	}
}