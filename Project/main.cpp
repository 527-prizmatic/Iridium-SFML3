#include "Project/demo_state.hpp"
#include "Project/test_state.hpp"

int main() {
	Ir::ApplicationWindow window{Ir::Vector{1280.f, 720.f}};
	window.SetFPS(60u);
	Ir::MouseInput::Setup(window);

	Ir::StateMachine sm;
	sm.LoadState<DemoState>();

	while (1) {
		Ir::MouseInput::Update();

		sm.Initialize();
		sm.HandleEvents(window);
		sm.Update();
		sm.Render(window);
	}

	sm.Unload();
}