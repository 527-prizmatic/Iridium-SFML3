#ifndef PROJECT_EDITOR_SAVE_POPUP_HPP_
#define PROJECT_EDITOR_SAVE_POPUP_HPP_

#include "Project/vmf_editor/context.hpp"
#include "Iridium/vgui/input_field.hpp"

namespace vmf {
	class SavePopup {
	public:
		SavePopup(vmf::Context* context, ir::Vector pos);

		void processEvent(const sf::Event& event);
		bool update(ir::input::Mouse* mouseInput);
		void render(ir::render::VertexRenderer& renderer);

		void setValue(const std::string val);
		std::string getValue() const;

		void focus();

	private:
		std::unique_ptr<ir::vgui::FramedElement> savePopup_;
		vmf::Context* context_;

		ir::vgui::TextField* textField_;
	};
}

#endif // PROJECT_EDITOR_SAVE_POPUP_HPP_