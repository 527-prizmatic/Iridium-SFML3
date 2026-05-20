#include "Iridium/rendering/model.hpp"

namespace ir {
	namespace render {
		Component::Component() {
			vertices.reserve(3);
		}

		Component::Component(Vertex& v1) {
			vertices.reserve(1);
			type = Component::Type::POINT;
			vertices[0] = v1;
		}

		Component::Component(Vertex& v1, Vertex& v2) {
			vertices.reserve(2);
			type = Component::Type::LINE;
			vertices[0] = v1;
			vertices[1] = v2;
		}

		Component::Component(Vertex& v1, Vertex& v2, Vertex& v3) {
			vertices.reserve(3);
			type = Component::Type::TRIANGLE;
			vertices[0] = v1;
			vertices[1] = v2;
			vertices[2] = v3;
		}

		void Model::addComponent(Component&& cmp) {
			components_.push_back(cmp);
		}

		// @todo Implement file loading and parsing
//		Model Model::loadFromFile(std::filesystem::path file) {
//
//		}

		Model Model::testTriangle() {
			Model model;

			Vertex v1(-100, 0, sf::Color(255, 0, 0, 64));
			Vertex v2(50, 83, sf::Color(0, 255, 0, 64));
			Vertex v3(50, -83, sf::Color(0, 0, 255, 64));

			model.addComponent(std::move(Component(v1, v2, v3)));
			model.addComponent(std::move(Component(v1, v2)));
			model.addComponent(std::move(Component(v2, v3)));
			model.addComponent(std::move(Component(v1, v3)));

			return model;
		}
	}
}