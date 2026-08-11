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

		/// @brief This override of setScale takes into account letter model height, so that a scale of 10 means a height of 10 pixels.
		void setScale(float scale) override;
		/// @brief This override of getScale takes into account letter model height, so that a scale of 10 means a height of 10 pixels.
		float getScale() override;

	private:
		std::string string_;
		sf::Color color_ { sf::Color::White };

		static std::unordered_map<char, std::unique_ptr<Model>> modelSet_;

		void addVertexToBuffer(const Vertex& v, ir::render::VertexRenderer& renderer) const override;
	};
}

#endif // IRIDIUM_RENDERING_TEXT_HPP_