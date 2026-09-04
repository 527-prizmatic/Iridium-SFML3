#ifndef IRIDIUM_VGUI_INFIELD_HPP_
#define IRIDIUM_VGUI_INFIELD_HPP_

#include <string>
#include "Iridium/vgui/element.hpp"

namespace ir {
	namespace render {
		class Text;
	}

	namespace vgui {
		template <typename T>
		class InputField : public Element {
		public:
			using DataType = T;

			InputField(T defaultValue);

			virtual bool update(ir::input::Mouse& mouseInput) override;
			virtual void render(ir::render::VertexRenderer& renderer) const override;

		//	virtual void onIdle() override;
			virtual void onClick() override;
			virtual void onDeselect() override;
			virtual void onSfEvent(const sf::Event& e) override;

			void setValue(T value);
			T getValue() const;

			void setMaxChars(unsigned int max);
			unsigned int getMaxChars() const;

			void setScale(float scale);
			float getScale() const;

			void setLabelColor(sf::Color clr);
			sf::Color getLabelColor() const;

			void setColorUnfocused(sf::Color clr);
			sf::Color getColorUnfocused() const;

			void setColorFocused(sf::Color clr);
			sf::Color getColorFocused() const;

			bool hasFocus() const;
			void focus();

		private:
			std::unique_ptr<ir::render::Text> label_;
			T value_ {};
			bool focused_ { false };
			unsigned int maxChars_ { 20 };

			sf::Color clrUnfocused_ { sf::Color::Blue };
			sf::Color clrFocused_ { sf::Color::Green };
		};

		using TextField = ir::vgui::InputField<std::string>;
		using IntField = ir::vgui::InputField<int>;
	}
}

#include "Iridium/detail/vgui/input_field.inl"

#endif // IRIDIUM_VGUI_INFIELD_HPP_