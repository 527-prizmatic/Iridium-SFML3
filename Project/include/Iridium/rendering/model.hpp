#ifndef IRIDIUM_RENDERING_MODEL_HPP_
#define IRIDIUM_RENDERING_MODEL_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/rendering/shape.hpp"

namespace ir {
	namespace render {
		struct Vertex {
			short x;
			short y;
			sf::Color color;

			void setPosition(short x, short y) {
				this->x = x;
				this->y = y;
			}
		};

		struct Component {
			enum class Type : unsigned char {
				POINT = 0,
				LINE = 1,
				TRIANGLE = 2
			};
			Type type;
			std::vector<Vertex> vertices;

			Component();
			Component(Vertex& v1);
			Component(Vertex& v1, Vertex& v2);
			Component(Vertex& v1, Vertex& v2, Vertex& v3);

			void setPosition(size_t vertex, short x, short y) {
				vertices[vertex].setPosition(x, y);
			}

			void setColor(size_t vertex, sf::Color color) {
				vertices[vertex].color = color;
			}
		};

		class Model {
		public:
			Model() = default;
			
			void addComponent(Component&& cmp);

			static Model loadFromFile(std::string file);
			static Model testTriangle();

			/// @todo Implement saving-to-file static function directly in ir::render::Model

			size_t getComponentCount() const { return components_.size(); }
			const Component& getComponent(size_t index) const { return components_[index]; }

			auto begin() { return components_.begin(); }
			auto begin() const { return components_.begin(); }
			auto end() { return components_.end(); }
			auto end() const { return components_.end(); }

		private:
			std::vector<Component> components_;
		};
	}
}

#endif