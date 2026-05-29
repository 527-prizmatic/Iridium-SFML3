#include "Iridium/assets/asset_manager.hpp"

namespace ir {
	AssetManager::AssetManager() {
		
	}

	#pragma region sf::Texture
	template <>
	ir::TextureHandle AssetManager::registerAsset<ir::TextureAsset, ir::TextureHandle>(std::string_view name) {
		ir::TextureHandle handle = std::hash<std::string>{}(name.data());
		if (textures_.find(handle) != textures_.end()) {
			throw name.data();
		}
		textures_[handle] = std::make_unique<ir::TextureAsset>("..\\resources\\textures\\" + std::string(name.data()));
		return handle;
	}

	template <>
	sf::Texture* AssetManager::getAsset<ir::TextureAsset, ir::TextureHandle>(ir::TextureHandle handle) {
		if (textures_.find(handle) == textures_.end()) {
			return nullptr;
		}
		return &*textures_.at(handle);
	}
	
	ir::TextureHandle AssetManager::registerTexture(std::string_view name) { return registerAsset<ir::TextureAsset, ir::TextureHandle>(name); }
	ir::TextureAsset* AssetManager::getTexture(ir::TextureHandle name) { return getAsset<ir::TextureAsset, ir::TextureHandle>(name); }
#pragma endregion

#pragma region sf::SoundBuffer
	template <>
	ir::SoundHandle AssetManager::registerAsset<ir::SoundAsset, ir::SoundHandle>(std::string_view name) {
		ir::SoundHandle handle = std::hash<std::string>{}(name.data());
		if (sounds_.find(handle) != sounds_.end()) {
			throw name.data();
		}
		sounds_[handle] = std::make_unique<ir::SoundAsset>("..\\resources\\sounds\\" + std::string(name.data()));
		return handle;
	}

	template <>
	sf::SoundBuffer* AssetManager::getAsset<ir::SoundAsset, ir::SoundHandle>(ir::SoundHandle handle) {
		if (sounds_.find(handle) == sounds_.end()) {
			return nullptr;
		}
		return &*sounds_.at(handle);
	}
	
	ir::SoundHandle AssetManager::registerSound(std::string_view name) { return registerAsset<ir::SoundAsset, ir::SoundHandle>(name); }
	ir::SoundAsset* AssetManager::getSound(ir::SoundHandle name) { return getAsset<ir::SoundAsset, ir::SoundHandle>(name); }
#pragma endregion
}