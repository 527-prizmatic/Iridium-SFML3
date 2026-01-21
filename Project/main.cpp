#include "Project/core_state.hpp"
#include "Iridium/input/mouse.hpp"

int main() {
	Ir::ApplicationWindow window{Ir::Vector{1280.f, 720.f}};
	window.SetFPS(60u);
	Ir::MouseInput::Setup(window);

	Ir::StateMachine sm;
	sm.LoadState<CoreState>();

	while (!sm.HasRequestedExit()) {
		window.ReduceBackgroundResourceUsage();
		Ir::MouseInput::Update();

		sm.Initialize();
		sm.HandleEvents(window);
		sm.Update(window);
		sm.Render(window);
	}

	sm.Unload();
}