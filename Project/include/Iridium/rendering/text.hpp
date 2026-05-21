#ifndef IRIDIUM_RENDERING_TEXT_HPP_
#define IRIDIUM_RENDERING_TEXT_HPP_

#include "Iridium/rendering/model_renderer.hpp"

namespace ir::render {
	class Text : public ModelRenderer {
	public:
		void setString(std::string str);
		std::string getString() { return string_; }

		void setColor(sf::Color color) { color_ = color; }
		sf::Color getColor() { return color_; }

		static void loadModels();

		void setModel(Model&& model) = delete;
		Model& getModel() = delete;

	private:
		std::string string_;
		sf::Color color_ { sf::Color::White };

		static std::unordered_map<char, std::unique_ptr<Model>> modelSet_;

		void addVertexToBuffer(const Vertex& v, ir::render::VertexRenderer& renderer) const override;
	};
}

#endif // IRIDIUM_RENDERING_TEXT_HPP_