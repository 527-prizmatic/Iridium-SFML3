#ifndef IRIDIUM_VGUI_LABEL_HPP_
#define IRIDIUM_VGUI_LABEL_HPP_

#include <string>
#include "Iridium/vgui/element.hpp"
// #include "Iridium/rendering/text.hpp"

namespace ir {
	namespace render {
		class Text;
	}

	namespace vgui {
		class Label : public Element {
		public:
			enum class Anchor : unsigned char {
				LEFT,
				RIGHT,
				TOP,
				BOTTOM,
				OVER
			};

			Label(std::string text = "label");

			virtual bool update(ir::input::Mouse& mouseInput) override;
			virtual void render(ir::render::VertexRenderer& renderer) const override;

			void setScale(float scale);
			float getScale();

			void setLabel(std::string text);
			std::string getLabel();

			void setColor(sf::Color clr);
			sf::Color getColor();

			void setAnchor(Anchor anchor);
			Anchor getAnchor();
			
			virtual void setPosition(ir::Vector pos) override;

		protected:
			std::unique_ptr<ir::render::Text> label_;
			Anchor anchor_;
		};
	}
}
	
#endif // IRIDIUM_VGUI_LABEL_HPP_