#ifndef IRIDIUM_ASSET_MANAGER_HPP_
#define IRIDIUM_ASSET_MANAGER_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {

	class AssetManager {
	public:
		AssetManager();

		template <typename T, typename U>
		U registerAsset(std::string_view name) {
			throw ir::Exceptions::BadAssetType(typeid(T).name());
		}

		template <typename T>
		void deleteAsset(T handle) {}

		template <typename T, typename U>
		T* getAsset(U handle) {
			return nullptr;
		}

		ir::TextureHandle registerTexture(std::string_view name);
		ir::SoundHandle registerSound(std::string_view name);

		ir::TextureAsset* getTexture(ir::TextureHandle name);
		ir::SoundAsset* getSound(ir::SoundHandle name);

	private:
		std::unordered_map<TextureHandle, std::unique_ptr<ir::TextureAsset>> textures_;
		std::unordered_map<SoundHandle, std::unique_ptr<ir::SoundAsset>> sounds_;
	};

	template <>	ir::TextureHandle AssetManager::registerAsset<ir::TextureAsset, ir::TextureHandle>(std::string_view name);
	template <>	sf::Texture* AssetManager::getAsset<ir::TextureAsset, ir::TextureHandle>(ir::TextureHandle handle) ;
	
	template <> ir::SoundHandle AssetManager::registerAsset<ir::SoundAsset, ir::SoundHandle>(std::string_view name);
	template <> sf::SoundBuffer* AssetManager::getAsset<ir::SoundAsset, ir::SoundHandle>(ir::SoundHandle handle);


}

#endif // IRIDIUM_ASSET_MANAGER_HPP_