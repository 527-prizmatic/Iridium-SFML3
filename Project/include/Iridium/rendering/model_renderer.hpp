#ifndef IRIDIUM_RENDERING_MODEL_RENDERER_HPP_
#define IRIDIUM_RENDERING_MODEL_RENDERER_HPP_

#include "Iridium/rendering/shape.hpp"
#include "Iridium/rendering/model.hpp"

namespace ir {
	namespace render {
		class ModelRenderer : public Shape {
		public:
			virtual void render(ir::render::VertexRenderer& renderer) const;

			void setModel(Model&& model) { model_ = model; }
			Model& getModel() { return model_; }

			void setScale(float scale) { scale_ = scale; }
			float getScale() { return scale_; }

		private:
			float scale_;
			Model model_;
		};
	}
}





#endif