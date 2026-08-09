#ifndef IRIDIUM_VGUI_ELEMENT_HPP_
#define IRIDIUM_VGUI_ELEMENT_HPP_

#include <memory>
#include <vector>
#include "Iridium/vector.hpp"

namespace ir {
	namespace input {
		class Mouse;
	}

	namespace render {
		class VertexRenderer;
		class Rectangle;
	}

	namespace vgui {
		
		class Element {
		public:
			Element();

			virtual bool update(ir::input::Mouse& mouseInput);

			virtual void render(ir::render::VertexRenderer& renderer) const;

			Element* getElement(std::string key) const;
			Element* operator[](std::string key) const;
			Element* operator[](const char* key) const;

			void setPosition(ir::Vector pos);
			void setSize(ir::Vector size);

			ir::Vector getPosition() const;
			ir::Vector getSize() const;
			ir::Vector getAbsolutePosition() const;

			void addChildElement(std::string key, std::unique_ptr<ir::vgui::Element> child);
		//	void removeChildElement(std::string key);
		//	void removeChildElement(ir::vgui::Element* child);
		//	void removeParent();

		/// @brief Function to execute every frame when the item is not being hovered by the mouse.
		virtual void onIdle();

		/// @brief Function to execute every frame when the item is being hovered by the mouse.
		virtual void onHover();

		/// @brief Function to execute at the frame the item is being clicked on.
		virtual void onClick();

			
		protected:
			void renderFrame(ir::render::VertexRenderer& renderer) const;
			void resizeRectangle() const;

			static void createRect(); 

			static std::unique_ptr<ir::render::Rectangle> rect_;

			std::unordered_map<std::string, std::unique_ptr<ir::vgui::Element>> children_;
			ir::vgui::Element* parent_ { nullptr };

			ir::Vector pos_ { 0.f, 0.f };
			ir::Vector size_ { 100.f, 100.f };

			sf::Color clrBorder_ { sf::Color::White };
			sf::Color clrBackground_ { sf::Color::Blue };
		};
	}
}

#endif // IRIDIUM_VGUI_ELEMENT_HPP_