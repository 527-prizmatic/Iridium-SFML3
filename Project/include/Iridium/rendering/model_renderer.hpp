#ifndef IRIDIUM_RENDERING_MODEL_RENDERER_HPP_
#define IRIDIUM_RENDERING_MODEL_RENDERER_HPP_

#include "Iridium/rendering/shape.hpp"
#include "Iridium/rendering/model.hpp"

namespace ir {
	namespace render {
		class ModelRenderer : public Shape {
		public:
			virtual void render(ir::render::VertexRenderer& renderer) const;

			void setModel(Model& model) { model_ = model; }
			void setModel(Model&& model) { model_ = model; }
			Model& getModel() { return model_; }

			virtual void setScale(float scale) { scale_ = scale; }
			virtual float getScale() { return scale_; }

			ir::Vector getBoundingBoxSize();

		protected:
			float scale_ { 1.f };
			/// @todo Find a way to replace this with a reference or pointer
			/// This would require a solid memory management system though, to avoid leaks in case the renderer ever gains ownership of the model one way or another
			/// (Though ideally it should never do so)
			Model model_;

			virtual void addVertexToBuffer(const Vertex& v, ir::render::VertexRenderer& renderer) const;
		};
	}
}





#endif