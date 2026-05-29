namespace ir {
#pragma region sf::Texture
	template <>
	ir::TextureHandle AssetManager::registerAsset<ir::TextureAsset>(std::string_view name) {
		TextureHandle handle = std::hash<std::string>{}(name.data());
		if (textures_.find(handle) != textures_.end()) {
			throw name.data();
		}
		textures_[handle] = std::make_unique<ir::TextureAsset>("..\\resources\\textures\\" + std::string(name.data()));
	}

	template <>
	sf::Texture* AssetManager::getAsset(ir::TextureHandle handle) {
		if (textures_.find(handle) == textures_.end()) {
			return nullptr;
		}
		return &*textures_.at(handle);
	}
#pragma endregion

#pragma region sf::SoundBuffer
	template <>
	ir::TextureHandle AssetManager::registerAsset<ir::SoundAsset>(std::string_view name) {
		TextureHandle handle = std::hash<std::string>{}(name.data());
		if (sounds_.find(handle) != sounds_.end()) {
			throw name.data();
		}
		sounds_[handle] = std::make_unique<ir::SoundAsset>("..\\resources\\sounds\\" + std::string(name.data()));
	}

	template <>
	sf::SoundBuffer* AssetManager::getAsset(ir::SoundHandle handle) {
		if (sounds_.find(handle) == sounds_.end()) {
			return nullptr;
		}
		return &*sounds_.at(handle);
	}
#pragma endregion
}