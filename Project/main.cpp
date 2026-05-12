#include "Project/core_state.hpp"
#include "Iridium/input/mouse.hpp"

int main() {
	iridium::ApplicationWindow window{iridium::Vector{1280.f, 720.f}};
	window.SetFPS(60u);
	iridium::MouseInput::Setup(window);

	iridium::StateMachine sm;
	sm.loadState<CoreState>();

	while (!sm.hasRequestedExit()) {
		window.ReduceBackgroundResourceUsage();
		iridium::MouseInput::update();

		sm.initialize();
		sm.handleEvents(window);
		sm.update(window);
		sm.render(window);
	}

	sm.unload();
}