#ifndef IRIDIUM_RENDERING_VERTEX_RENDERER_HPP_
#define IRIDIUM_RENDERING_VERTEX_RENDERER_HPP_

#include "Iridium/vector.hpp"

namespace ir {
	class RenderTarget;

	namespace render {
		class VertexRenderer {
		public:
			VertexRenderer() = delete;
			VertexRenderer(ir::RenderTarget* target);

			void reset(sf::PrimitiveType type = sf::PrimitiveType::Lines);

			void flush(const sf::Texture* texture = nullptr);

			void addPoint(ir::Vector position, sf::Color color = sf::Color::White);

			void addPoint(ir::Vector position, ir::Vector textureCoord);

			ir::RenderTarget* getTarget() { return target_; }

		private:
			ir::RenderTarget* target_;
			std::unique_ptr<sf::VertexArray> buffer_;
		};
	}
}


#endif