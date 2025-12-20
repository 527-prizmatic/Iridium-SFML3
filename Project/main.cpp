#include "Project/demo_state.hpp"
#include "Project/test_state.hpp"

int main() {
	Ir::ApplicationWindow window{Ir::Vector{1280.f, 720.f}};
	window.SetFPS(60u);
	Ir::MouseInput::Setup(window);

	Ir::StateMachine sm;
	sm.LoadState<DemoState>();

	while (!sm.HasRequestedExit()) {
		Ir::MouseInput::Update();

		sm.Initialize();
		sm.HandleEvents(window);
		sm.Update();
		sm.Render(window);
	}

	sm.Unload();
}