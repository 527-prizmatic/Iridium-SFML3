#include "Project/demo_state.hpp"
#include "Project/test_state.hpp"

int main() {
	Ir::ApplicationWindow window{Ir::Vector{1280.f, 720.f}};
	window.SetFPS(60u);
	Ir::MouseInput::Setup(window);

#ifdef USING_IMGUI
	ImGui::SFML::Init(window.GetWindow(), true);
#endif

	Ir::StateMachine sm;
	sm.LoadState<DemoState>();

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