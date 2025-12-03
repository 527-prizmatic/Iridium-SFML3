#ifndef IRIDIUM_RENDERTARGET_HPP_
#define IRIDIUM_RENDERTARGET_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/vector.hpp"

namespace Ir {
	/// @brief Base class for various rendering buffers.
	/// They are typically implemented as wrappers for a sf::RenderTexture,
	/// coming with various utilities for ease of manipulation by the end user.
	class RenderTarget {
	public:
		/// @brief Resizes the render target's internal buffer.
		virtual void SetSize(Ir::Vector _size) = 0;

		/// @return Size of the render target's buffer
		virtual Ir::Vector GetSize() = 0;

		/// @brief Completely clears the render target's buffer and fills it with the given color.
		virtual void Clear(sf::Color _fill_color = sf::Color::Transparent) = 0;

		/// @brief Renders the given object onto the render target.
		virtual void Render(sf::Drawable& _drawable) = 0;

		/// @brief Renders the contents of the given render target's buffer onto this one.
		virtual void Render(Ir::RenderTarget& _render_target) = 0;

		/// @return Whether the render target has been properly initialized and is ready for rendering
		virtual bool IsValid() = 0;
	};
};

#endif // IRIDIUM_RENDERTARGET_HPP_