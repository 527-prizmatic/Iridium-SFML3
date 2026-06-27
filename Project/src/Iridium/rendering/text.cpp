#include "Iridium/rendering/text.hpp"
#include <sstream>

namespace ir::render {
	std::unordered_map<char, std::unique_ptr<Model>> Text::modelSet_;

	std::string charToModelName(unsigned char c);
	unsigned char modelNameToChar(std::string name);

	void Text::setString(std::string str) {
		string_ = str;
		float offset { 0.f };
		model_ = Model();
		for (size_t i = 0; i < str.size(); i++) {
			if (modelSet_.contains(str[i])) {
				Model& letter = *modelSet_[str[i]];
				for (auto cmp : letter) {
					for (auto& v : cmp.vertices) {
						v.x += offset;
					}
					model_.addComponent(std::move(cmp));
				}
					offset += letter.getWidth() + 1.f;
			}
			else {
				offset += 5.f;
			}

		}
	}

	void Text::addVertexToBuffer(const Vertex& v, ir::render::VertexRenderer& renderer) const {
		Vertex vNew { v };
		vNew.color *= color_;
		ModelRenderer::addVertexToBuffer(vNew, renderer);
	}

	void Text::loadModels() {
		std::string folder { "..\\text\\" };
		unsigned char c = ' ';
		while (c != 255u) {
			std::string name = charToModelName(c);
			if (name != "lol_no") {
				Model model { Model::loadFromFile(folder + name) };
				modelSet_.emplace(c, std::make_unique<ir::render::Model>(std::move(model)));
			}
			c++;
		}
	}

	std::string charToModelName(unsigned char c) {
		std::stringstream sstr;

		if (c >= 'a' && c <= 'z') {
			sstr << static_cast<char>(c);
			sstr << "_lower";
		}
		else if (c >= 'A' && c <= 'Z') {
			sstr << static_cast<char>(c + 32u);
			sstr << "_upper";
		}
		else if (c >= '0' && c <= '9') {
			sstr << c;
		}
		else if (c == '_') {
			sstr << "underscore";
		}
		else {
			sstr << "lol_no";
		}
		return sstr.str();
	}

	unsigned char modelNameToChar(std::string name) {
		return 'a';
	}
}