#ifndef IRIDIUM_RENDERING_MODEL_RENDERER_HPP_
#define IRIDIUM_RENDERING_MODEL_RENDERER_HPP_

#include "Iridium/rendering/shape.hpp"
#include "Iridium/rendering/model.hpp"

namespace ir {
	namespace render {
		class ModelRenderer : public Shape {
		public:
			virtual void render(ir::render::VertexRenderer& renderer) const;

			void setModel(Model model) { model_ = model; }
			Model& getModel() { return model_; }

			void setScale(float scale) { scale_ = scale; }
			float getScale() { return scale_; }

		protected:
			float scale_ { 1.f };
			Model model_;

			virtual void addVertexToBuffer(const Vertex& v, ir::render::VertexRenderer& renderer) const;
		};
	}
}





#endif