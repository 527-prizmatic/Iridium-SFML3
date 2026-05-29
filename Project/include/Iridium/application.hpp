#ifndef IRIDIUM_APPLICATION_HPP_
#define IRIDIUM_APPLICATION_HPP_

#include "Iridium/state_machine.hpp"
#include "Iridium/time.hpp"
#include "Iridium/input/mouse.hpp"
#include "Iridium/rendering/vertex_renderer.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {
	class AssetManager;
	class SoundManager;

	struct ApplicationContext {
		ir::ApplicationWindow* appWindow {};
		ir::GameClock* gameClock {};
		ir::input::Mouse* mouseInput {};
		ir::render::VertexRenderer* vertexRenderer {};
		ir::AssetManager* assetManager {};
		ir::SoundManager* soundManager {};

		float deltaTime() {
			return gameClock->getDeltaTime();
		}

		float deltaTimeUnscaled() {
			return gameClock->getDeltaTimeUnscaled();
		}
	};

	class Application {
	public:
		Application();

		/// @brief Starts up the application.
		/// @tparam T Any derivative of ir::StateBase, for use as the initial StateMachine state
		template <typename T>
		void run() {
			expectInitialized();
			stateMachine_->loadState<T>();
			runMainLoop();
		}

	private:
		std::unique_ptr<ir::StateMachine> stateMachine_;
		std::unique_ptr<ir::ApplicationWindow> appWindow_;
		std::unique_ptr<ir::GameClock> gameClock_;
		std::unique_ptr<ir::input::Mouse> mouseInput_;
		std::unique_ptr<ir::render::VertexRenderer> vertexRenderer_;
		std::unique_ptr<ir::AssetManager> assetManager_;
		std::unique_ptr<ir::SoundManager> soundManager_;

		template <typename T, typename... Args>
		void initializeComponent(std::unique_ptr<T>& component, Args... args) {
			component = std::make_unique<T>(args...);
			if (component == nullptr) {
				throw ir::Exceptions::InitializationError(std::string{typeid(T).name()} + " component of Application");
			}
		}

		void expectInitialized();
		void runMainLoop();

		ApplicationContext context_ {};
	};
}






#endif