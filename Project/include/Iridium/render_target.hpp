#ifndef IRIDIUM_RENDERTARGET_HPP_
#define IRIDIUM_RENDERTARGET_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/rendering/shapes.hpp"

namespace iridium {
	/// @brief Base class for various rendering buffers.
	/// They are typically implemented as wrappers for a sf::RenderTexture,
	/// coming with various utilities for ease of manipulation by the end user.
	class RenderTarget {
	public:
		/// @brief Resizes the render target's internal buffer.
		virtual void setSize(iridium::Vector _size) = 0;

		/// @return Size of the render target's buffer
		virtual iridium::Vector getSize() = 0;

		/// @brief Completely clears the render target's buffer and fills it with the given color.
		virtual void clear(sf::Color _fill_color = sf::Color::Transparent) = 0;

		/// @brief Renders the given object onto the render target.
		virtual void render(sf::Drawable& _drawable, const sf::Texture* _texture = nullptr) = 0;
		
		/// @brief Renders the given object onto the render target.
		virtual void render(iridium::render::Shape& _shape) = 0;

		/// @brief Renders the contents of the given render target's buffer onto this one.
		virtual void render(iridium::RenderTarget& _render_target) = 0;

		/// @return Whether the render target has been properly initialized and is ready for rendering
		virtual bool isValid() = 0;
	};
};

#endif // IRIDIUM_RENDERTARGET_HPP_