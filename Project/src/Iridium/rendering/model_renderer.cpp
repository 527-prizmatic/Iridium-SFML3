#include "Iridium/rendering/model_renderer.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"

namespace ir {
	namespace render {
		void ModelRenderer::render(ir::render::VertexRenderer& renderer) const {
			for (auto& cmp : model_) {
				if (cmp.type == Component::Type::POINT) {
					renderer.reset(sf::PrimitiveType::Points);
					addVertexToBuffer(cmp.vertices[0], renderer);

				} else if (cmp.type == Component::Type::LINE) {
					renderer.reset(sf::PrimitiveType::Lines);
					addVertexToBuffer(cmp.vertices[0], renderer);
					addVertexToBuffer(cmp.vertices[1], renderer);

				} else if (cmp.type == Component::Type::TRIANGLE) {
					renderer.reset(sf::PrimitiveType::Triangles);
					addVertexToBuffer(cmp.vertices[0], renderer);
					addVertexToBuffer(cmp.vertices[1], renderer);
					addVertexToBuffer(cmp.vertices[2], renderer);
				}
				renderer.flush();
			}
		}
		
		void ModelRenderer::addVertexToBuffer(const Vertex &v, ir::render::VertexRenderer& renderer) const {
			ir::Vector position { static_cast<float>(v.x), static_cast<float>(v.y) };
			position = position.rotate(angle_) * scale_;
			position += position_ - anchor_;
			
			renderer.addPoint(position, v.color);
		}
	}
}