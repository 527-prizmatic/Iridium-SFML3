#ifndef IRIDIUM_SUBWINDOW_HPP_
#define IRIDIUM_SUBWINDOW_HPP_

#include "Iridium/render_target.hpp"

namespace Ir {
	class SubWindow: public Ir::RenderTarget {
	public:
		SubWindow(Ir::Vector _size);

		/// @brief Deletes all internal resources and regenerates them with the provided size in pixels.
		/// Checking if the window is in an invalid state before calling this function is not necessary, as it will attempt to reallocate them anyway.
		/// @param _size New size of the internal window and render texture, in pixels.
		void SetSize(Ir::Vector _size);

		/// @return Size of the internal resources, in pixels
		/// @attention Attempting to call this function while the window is in an invalid state will throw an exception.
		Ir::Vector GetSize();

		/// @brief Clears the rendering buffer and fills it with the given color.
		/// @attention Attempting to call this function while the buffer is in an invalid state will throw an exception.
		void Clear(sf::Color _fill_color = sf::Color::Transparent);

		/// @brief Draws a SFML drawable object into the rendering buffer.
		/// @attention Attempting to call this function while the buffer is in an invalid state will throw an exception.
		void Render(sf::Drawable& _drawable, const sf::Texture* _texture = nullptr);

		/// @brief Draws an Iridium drawable object into the rendering buffer.
		/// @attention Attempting to call this function while the buffer is in an invalid state will throw an exception.
		void Render(Ir::Render::Shape& _shape);

		/// @brief Draws the contents of another render target into this one.
		/// @attention Attempting to call this function while the buffer is in an invalid state will throw an exception.
		void Render(Ir::RenderTarget& _render_target);

		/// @brief Draws the contents of the subwindow's rendering buffer into another render target.
		/// @attention Attempting to call this function while either buffer is in an invalid state will throw an exception.
		void FlushToTarget(Ir::RenderTarget& _render_target);

		/// @brief Subwindows contain a sf::RenderTexture as their rendering buffer.
		/// The object is considered valid if it has been correctly allocated.
		/// @return Whether the subwindow has been properly initialized and is ready for rendering
		bool IsValid() {
			return this->m_renderTexture != nullptr && this->m_frame != nullptr;
		}

		/// @brief Whether a frame should be rendered around the subwindow upon calling FlushToTarget().
		void SetRenderFrame(bool _val) { this->m_renderFrame = _val; }

		/// @brief Sets the color of the frame to be rendered around the subwindow.
		void SetRenderFrameColor(sf::Color _clr);

		/// @brief Sets the position where the subwindow should be rendered, relative to the parent.
		void SetPosition(Ir::Vector _pos) { this->m_position = _pos; }
		Ir::Vector GetPosition() const { return this->m_position; }

	private:
		std::unique_ptr<sf::RenderTexture> m_renderTexture;
		std::unique_ptr<Ir::Render::Quad> m_rect; ///< Rectangle shape used for rendering the subwindow upon calling FlushToTarget()
		std::unique_ptr<Ir::Render::Rectangle> m_frame; ///< Rectangle shape used to render the frame
		Ir::Vector m_position; ///< Where to draw the subwindow relative to its parent

		bool m_renderFrame { true }; ///< Whether to draw a frame around the subwindow

		/// @brief Reallocates internal resources, deleting the previous ones if they existed.
		/// @attention This overload reuses the previously-allocated resources' size in pixels.
		/// Attempting to call this function while the window is in an invalid state will throw an exception.
		void AllocateResources();

		/// @brief Reallocates internal resources, deleting the previous ones if they existed.
		/// @param _size Size of the newly-allocated resources, in pixels.
		void AllocateResources(Ir::Vector _size);

		void ConfigureRect(Ir::Vector _size);
		void ConfigureFrame(Ir::Vector _size);
	};
}

#endif // IRIDIUM_SUBWINDOW_HPP_