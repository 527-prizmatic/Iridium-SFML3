#ifndef PROJECT_EDITOR_ICON_BUTTON_HPP_
#define PROJECT_EDITOR_ICON_BUTTON_HPP_

#include "Project/vmf_editor/ui_button.hpp"

namespace vmf {
	class IconButton : public UiButton {
	public:
		IconButton(vmf::Context* context, std::string_view model = "square");

		void render(ir::render::VertexRenderer& renderer);

		void setDimensions(ir::Vector topLeftCorner, ir::Vector size);
		void setIcon(std::string_view model);
		void setIconScale(float scale);

		float getIconScale();

	private:
		void recenterIcon();
		void setColor(sf::Color color);

		std::unique_ptr<ir::render::ModelRenderer> icon_;
	};
}

#endif // PROJECT_EDITOR_ICON_BUTTON_HPP_