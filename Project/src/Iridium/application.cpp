#include "Iridium/application.hpp"
#include "Project/core_state.hpp"

namespace ir {
	Application::Application() {
		initializeComponent(appWindow_, ir::Vector{ 1280.f, 720.f });
		appWindow_->setFPS(60u);

		initializeComponent(gameClock_);
		gameClock_->zero();

		initializeComponent(stateMachine_);
		initializeComponent(mouseInput_);
	}

	void Application::run() {
		expectInitialized();
		/// @todo Extract this template argument into a template function
		stateMachine_->loadState<CoreState>();

		while (!stateMachine_->hasRequestedExit()) {
			gameClock_->startTick();
			appWindow_->reduceBackgroundResourceUsage();
			mouseInput_->update(*appWindow_);

			stateMachine_->initialize();
			stateMachine_->handleEvents(*appWindow_);
			stateMachine_->update(*appWindow_);
			stateMachine_->render(*appWindow_);
		}

		stateMachine_->unload();
	}

	void Application::expectInitialized() {
		Expects(appWindow_ != nullptr);
		Expects(gameClock_ != nullptr);
		Expects(stateMachine_ != nullptr);
		Expects(mouseInput_ != nullptr);
	}
}