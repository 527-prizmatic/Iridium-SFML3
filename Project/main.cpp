#include "Project/core_state.hpp"
#include "Iridium/input/mouse.hpp"

/// @todo Replace all these free variables with an Application class
int main() {
	ir::ApplicationWindow window{ir::Vector{1280.f, 720.f}};
	window.setFPS(60u);

	ir::input::Mouse mouseInput;

	ir::StateMachine sm;
	sm.loadState<CoreState>();

	while (!sm.hasRequestedExit()) {
		window.reduceBackgroundResourceUsage();
		mouseInput.update(window);

		sm.initialize();
		sm.handleEvents(window);
		sm.update(window);
		sm.render(window);
	}

	sm.unload();
}