#ifndef IRIDIUM_ASSET_MANAGER_HPP_
#define IRIDIUM_ASSET_MANAGER_HPP_

#include "Iridium/libraries.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {
	using TextureHandle = uint32_t;
	using SoundHandle = uint32_t;
	using MusicHandle = uint32_t;

	using TextureAsset = sf::Texture;
	using SoundAsset = sf::SoundBuffer;
	using MusicAsset = sf::Music;

	class AssetManager {
	public:
		AssetManager();
/*
		template <typename T>
		registerAsset(ir::Asset&& asset, std::string_view name) {

		}
*/

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

	private:
		std::unordered_map<TextureHandle, std::unique_ptr<ir::TextureAsset>> textures_;
		std::unordered_map<SoundHandle, std::unique_ptr<ir::SoundAsset>> sounds_;
	};
}

#include "Iridium/assets/asset_manager.inl"

#endif // IRIDIUM_ASSET_MANAGER_HPP_