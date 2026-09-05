#ifndef IRIDIUM_VGUI_ICON_HPP_
#define IRIDIUM_VGUI_ICON_HPP_

#include "Iridium/vgui/element.hpp"
#include <string>

namespace ir {
	namespace render {
		class ModelRenderer;
	}

	namespace vgui {
		class Icon : public Element {
		public:
			Icon();
			Icon(std::string filename);

			virtual bool update(ir::input::Mouse& mouseInput) override;
			virtual void render(ir::render::VertexRenderer& renderer) const override;

			void setScale(float scale);
			float getScale();

			void setIcon(std::string text);

		private:
			std::unique_ptr<ir::render::ModelRenderer> modelRenderer_;

			float scale_ { 25.f };
		};
	}
}

#endif // IRIDIUM_VGUI_ICON_HPP_