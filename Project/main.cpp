#include "Project/core_state.hpp"
#include "Iridium/input/mouse.hpp"

int main() {
	ir::ApplicationWindow window{ir::Vector{1280.f, 720.f}};
	window.setFPS(60u);
	ir::MouseInput::setup(window);

	ir::StateMachine sm;
	sm.loadState<CoreState>();

	while (!sm.hasRequestedExit()) {
		window.reduceBackgroundResourceUsage();
		ir::MouseInput::update();

		sm.initialize();
		sm.handleEvents(window);
		sm.update(window);
		sm.render(window);
	}

	sm.unload();
}