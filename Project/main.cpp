#include "Iridium/application.hpp"
#include "Project/vmf_editor_state.hpp"

int main() {
	ir::log::startSession();
	try {
		ir::render::Text::loadModels();
		ir::Application app;
		app.run<VmfEditorState>();
	}
	catch (...) {
		LOG_ERROR("Something terrible happened (caught unhandled exception, exiting)");
	}
	ir::log::endSession();
}