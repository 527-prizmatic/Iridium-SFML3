#ifndef PROJECT_EDITOR_MODEL_HPP_
#define PROJECT_EDITOR_MODEL_HPP_

#include "Project/ir_fwd.hpp"
#include "Project/vmf_editor/context.hpp"

namespace vmf {
	class EditorModel {
	public:
		EditorModel(vmf::Context* context);

		void render(ir::render::VertexRenderer& renderer);

		void addComponent(ir::render::Component cmp);
		void removeLastComponent();
		void clear();

	private:
		vmf::Context* context_;

		std::unique_ptr<ir::render::Model> model_;
		std::unique_ptr<ir::render::ModelRenderer> renderer_;
	};
}

#endif // PROJECT_EDITOR_MODEL_HPP_