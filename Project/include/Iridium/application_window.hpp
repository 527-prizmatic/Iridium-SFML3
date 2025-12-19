#ifndef IRIDIUM_APPWINDOW_HPP_
#define IRIDIUM_APPWINDOW_HPP_

#include "Iridium/render_target.hpp"

namespace Ir {
	class ApplicationWindow: public Ir::RenderTarget {
	public:
		ApplicationWindow(Ir::Vector _size);

		/// @brief Deletes all internal resources and regenerates them with the provided size in pixels.
		/// Checking if the window is in an invalid state before calling this function is not necessary, as it will attempt to reallocate them anyway.
		/// @param _size New size of the internal window and render texture, in pixels.
		void SetSize(Ir::Vector _size);

		/// @return Size of the internal resources, in pixels
		/// @attention Attempting to call this function while the window is in an invalid state will throw an exception.
		Ir::Vector GetSize();

		/// @brief Clears the rendering buffer and fills it with the given color.
		/// @attention Attempting to call this function while the window is in an invalid state will throw an exception.
		void Clear(sf::Color _fill_color = sf::Color::Transparent);

		/// @brief Draws a SFML drawable object into the rendering buffer.
		/// @attention Attempting to call this function while the window is in an invalid state will throw an exception.
		void Render(sf::Drawable& _drawable);

		/// @brief Draws an Iridium drawable object into the rendering buffer.
		/// @attention Attempting to call this function while the window is in an invalid state will throw an exception.
		void Render(Ir::Render::Shape& _shape);

		/// @brief Draws the contents of another render target into this one.
		/// @attention Attempting to call this function while the window is in an invalid state will throw an exception.
		void Render(Ir::RenderTarget& _render_target);

		/// @brief Flushes the render texture onto the render window.
		/// This function will most likely be the last one called in the game loop.
		void Flush();

		/// @brief An application window contains two dynamically-allocated resources: a sf::renderWindow and a sf::RenderTexture.
		/// The object is considered valid if and only if both have been correctly allocated.
		/// @return Whether the application window has been properly initialized and is ready for rendering
		bool IsValid() {
			return this->m_renderWindow != nullptr && this->m_renderTexture != nullptr && this->m_rect != nullptr;
		}

		/// @brief Sets target FPS.
		/// The application window will force its thread to sleep to match the requested framerate,
		/// so use with caution in time-critical applications.
		void SetFPS(unsigned int _fps);

		/// @return Current target FPS
		[[nodiscard]] unsigned int GetFPS() { return this->m_fps; }

		/// @return Whether the application window has system focus
		[[nodiscard]] bool HasFocus() const { return this->m_renderWindow->hasFocus(); }

		/// @return Current position of the mouse cursor within the application window
		[[nodiscard]] sf::Vector2i GetMouseCursorPosition() const;

		/// @return Next queued SFML event
		[[nodiscard]] const std::optional<sf::Event> PollNextEvent();

	private:
		std::shared_ptr<sf::RenderWindow> m_renderWindow;
		std::unique_ptr<sf::RenderTexture> m_renderTexture;
		std::unique_ptr<sf::RectangleShape> m_rect; ///< Rectangle shape used for rendering the texture onto the window upon calling Flush()
		unsigned int m_fps; ///< Target FPS
		
		/// @brief Reallocates internal resources, deleting the previous ones if they existed.
		/// @attention This overload reuses the previously-allocated resources' size in pixels.
		/// Attempting to call this function while the texture is in an invalid state will throw an exception.
		void AllocateResources();

		/// @brief Reallocates internal resources, deleting the previous ones if they existed.
		/// @param _size Size of the newly-allocated resources, in pixels.
		void AllocateResources(sf::Vector2u _size);

		void ConfigureRect();
	};
}

#endif // IRIDIUM_APPWINDOW_HPP_