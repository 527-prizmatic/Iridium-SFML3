#include "Iridium/application.hpp"
#include "Project/core_state.hpp"

namespace ir {
	Application::Application() {
		initializeComponent(appWindow_, ir::Vector{ 1280.f, 720.f });
		appWindow_->setFPS(60u);
		initializeComponent(vertexRenderer_, &*appWindow_);

		initializeComponent(gameClock_);
		gameClock_->zero();

		initializeComponent(mouseInput_);

		initializeComponent(assetManager_);
		initializeComponent(soundManager_, &*assetManager_);

		initializeComponent(stateMachine_);

		context_.appWindow = &*appWindow_;
		context_.gameClock = &*gameClock_;
		context_.mouseInput = &*mouseInput_;
		context_.vertexRenderer = &*vertexRenderer_;
		context_.assetManager = &*assetManager_;
		context_.soundManager = &*soundManager_;
		
		stateMachine_->registerContext(&context_);
	}

	void Application::runMainLoop() {
		expectInitialized();

		while (!stateMachine_->hasRequestedExit()) {
			gameClock_->startTick();
			appWindow_->reduceBackgroundResourceUsage();
			mouseInput_->update(*appWindow_);

			/// Keep StateMachine init last
			stateMachine_->initialize();
			stateMachine_->handleEvents();
			stateMachine_->update();
			stateMachine_->render();

			soundManager_->update();
		}

		stateMachine_->unload();
	}

	void Application::expectInitialized() {
		Expects(appWindow_ != nullptr);
		Expects(gameClock_ != nullptr);
		Expects(stateMachine_ != nullptr);
		Expects(mouseInput_ != nullptr);
		Expects(vertexRenderer_ != nullptr);
	}
}