#include "Iridium/application.hpp"
#include "Project/core_state.hpp"

int main() {
	ir::Application app;
	app.run<CoreState>();
}