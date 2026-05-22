#include "Iridium/application.hpp"
#include "Project/vmf_editor_state.hpp"

int main() {
	ir::log::startSession();
	ir::render::Text::loadModels();
	ir::Application app;
	app.run<VmfEditorState>();
	ir::log::endSession();
}