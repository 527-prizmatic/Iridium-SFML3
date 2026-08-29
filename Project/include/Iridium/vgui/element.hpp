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
		using ClickEvent = std::function<void(void)>;
		
		class Element {
		public:
			Element();

			virtual bool update(ir::input::Mouse& mouseInput);
			virtual void render(ir::render::VertexRenderer& renderer) const;

			Element* getElement(std::string key) const;
			Element* operator[](std::string key) const;
			Element* operator[](const char* key) const;

			template <typename T>
			T* getElement(std::string key) const {
				ir::vgui::Element* elt { getElement(key) };
				if (elt) {
					return dynamic_cast<T*>(elt);
				}
				return nullptr;
			}

			virtual void setPosition(ir::Vector pos);
			virtual void setSize(ir::Vector size);

			ir::Vector getPosition() const;
			ir::Vector getSize() const;
			ir::Vector getAbsolutePosition() const;

			void addChildElement(std::string key, std::unique_ptr<ir::vgui::Element> child);
		//	void removeChildElement(std::string key);
		//	void removeChildElement(ir::vgui::Element* child);
		//	void removeParent();

		void registerClickEvent(ir::vgui::ClickEvent event);
			
		protected:
			void renderFrame(ir::render::VertexRenderer& renderer) const;
			void resizeRectangle() const;

			static void createRect(); 

			/// @brief Internal function defining behavior when not hovered by the mouse.
			virtual void onIdle();

			/// @brief Internal function defining behavior while hovered by the mouse.
			virtual void onHover();

			/// @brief Internal function defining behavior when clicked.
			virtual void onClick();

			/// @brief Internal function defining behavior when clicking away.
			virtual void onDeselect();

			static std::unique_ptr<ir::render::Rectangle> rect_;

			std::unordered_map<std::string, std::unique_ptr<ir::vgui::Element>> children_;
			ir::vgui::Element* parent_ { nullptr };

			ir::Vector pos_ { 0.f, 0.f };
			ir::Vector size_ { 100.f, 100.f };

			sf::Color clrBorder_ { sf::Color::White };
			sf::Color clrBackground_ { sf::Color::Blue };

			/// @brief Additional user-defined click events.
			std::vector<ir::vgui::ClickEvent> clickEvents {};
		};
	}
}

#endif // IRIDIUM_VGUI_ELEMENT_HPP_