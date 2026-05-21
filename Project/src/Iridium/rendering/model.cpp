#include "Iridium/rendering/model.hpp"
#include <fstream>

namespace ir {
	namespace render {
		Component::Component() {
			vertices.resize(3);
		}

		Component::Component(Vertex& v1) {
			vertices.resize(1);
			type = Component::Type::POINT;
			vertices[0] = v1;
		}

		Component::Component(Vertex& v1, Vertex& v2) {
			vertices.resize(2);
			type = Component::Type::LINE;
			vertices[0] = v1;
			vertices[1] = v2;
		}

		Component::Component(Vertex& v1, Vertex& v2, Vertex& v3) {
			vertices.resize(3);
			type = Component::Type::TRIANGLE;
			vertices[0] = v1;
			vertices[1] = v2;
			vertices[2] = v3;
		}

		void Model::addComponent(Component&& cmp) {
			components_.push_back(cmp);
		}

		Model Model::loadFromFile(std::string file) {
			std::filesystem::path path = "..\\resources\\models\\" + file + ".vmf";

			std::ifstream stream(path, std::ios::binary);
			LOG_INFO(path.string());
			if (stream.fail()) {
				throw "pavouk";
			}

			Model model;

			char c;
			while (!stream.eof()) {
				stream.read(&c, 1);
				if (stream.eof()) {
					break;
				}

				if (*reinterpret_cast<unsigned char*>(&c) > 2) {
					throw "domaci";
				}

				Component cmp;
				cmp.type = static_cast<ir::render::Component::Type>(c);

				size_t iterations = c;
				for (size_t i = 0; i <= iterations; i++) {
					Vertex v { 0, 0, sf::Color::White };
					char c = 0;
					stream.read(&c, 1);
					v.x = static_cast<short>(c);
					stream.read(&c, 1);
					v.y = static_cast<short>(c);
					stream.read(reinterpret_cast<char*>(&v.color.r), 1);
					stream.read(reinterpret_cast<char*>(&v.color.g), 1);
					stream.read(reinterpret_cast<char*>(&v.color.b), 1);
					stream.read(reinterpret_cast<char*>(&v.color.a), 1);
					cmp.vertices[i] = v;
				}

				model.addComponent(std::move(cmp));
			}

			return model;
		}

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