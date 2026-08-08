#include "Iridium/rendering/model.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {
	namespace render {
		Component::Component() {
			vertices.resize(3);
		}

		Component::Component(Vertex v1) {
			vertices.resize(1);
			type = Component::Type::POINT;
			vertices[0] = v1;
		}

		Component::Component(Vertex v1, Vertex v2) {
			vertices.resize(2);
			type = Component::Type::LINE;
			vertices[0] = v1;
			vertices[1] = v2;
		}

		Component::Component(Vertex v1, Vertex v2, Vertex v3) {
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
				throw ir::Exceptions::BadModelName(file);
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
					stream.read(reinterpret_cast<char*>(&v), sizeof(v));
					cmp.vertices[i] = v;
				}

				model.addComponent(std::move(cmp));
			}
			stream.close();

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
		
		float Model::getWidth() {
			short min { 32767 }, max { -32768 };
			
			for (auto& c : components_) {
				for (auto& v : c) {
					if (v.x < min) {
						min = v.x;
					}
					if (v.x > max) {
						max = v.x;
					}
				}
			}	

			return max - min;

		}

		float Model::getHeight() {
			short min { 32767 }, max { -32768 };

			for (auto& c : components_) {
				for (auto& v : c) {
					if (v.y < min) {
						min = v.y;
					}
					if (v.y > max) {
						max = v.y;
					}
				}
			}	

			return max - min;
		}
	}
}