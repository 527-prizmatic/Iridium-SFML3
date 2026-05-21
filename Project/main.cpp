#include "Iridium/application.hpp"
#include "Project/core_state.hpp"

int main() {
	ir::log::startSession();
	ir::Application app;
	app.run<CoreState>();
	ir::log::endSession();
}