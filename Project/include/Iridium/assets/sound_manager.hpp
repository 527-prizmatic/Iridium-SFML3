#ifndef IRIDIUM_ASSETS_SOUND_MANAGER_HPP_
#define IRIDIUM_ASSETS_SOUND_MANAGER_HPP_

#include "Iridium/libraries.hpp"

namespace ir {
	class AssetManager;

	class SoundManager {
	public:
		SoundManager(ir::AssetManager* manager);

		void update();

		void playSound(ir::SoundHandle handle);

		void stopAllSounds();

	private:
		std::list<sf::Sound> playBuffer_;
		ir::AssetManager* manager_;
	};
}

#endif // IRIDIUM_ASSETS_SOUND_MANAGER_HPP_