#ifndef PROJECT_EDITOR_LOAD_POPUP_HPP_
#define PROJECT_EDITOR_LOAD_POPUP_HPP_

#include "Project/vmf_editor/context.hpp"
#include "Iridium/vgui/input_field.hpp"

namespace vmf {
	class LoadPopup {
	public:
		LoadPopup(vmf::Context* context, ir::Vector pos);

		void processEvent(const sf::Event& event);
		bool update(ir::input::Mouse* mouseInput);
		void render(ir::render::VertexRenderer& renderer);

		void setValue(const std::string val);
		std::string getValue() const;

		void focus();

		void setColor(const sf::Color clr);

	private:
		std::unique_ptr<ir::vgui::FramedElement> loadPopup_;
		vmf::Context* context_;

		ir::vgui::TextField* textField_;
	};
}

#endif // PROJECT_EDITOR_LOAD_POPUP_HPP_