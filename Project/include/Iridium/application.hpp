#ifndef IRIDIUM_APPLICATION_HPP_
#define IRIDIUM_APPLICATION_HPP_

#include "Iridium/state_machine.hpp"
#include "Iridium/time.hpp"
#include "Iridium/input/mouse.hpp"
#include "Iridium/exceptions.hpp"

namespace ir {
	class Application {
	public:
		Application();
		void run();

	private:
		std::unique_ptr<ir::ApplicationWindow> appWindow_;
		std::unique_ptr<ir::GameClock> gameClock_;
		std::unique_ptr<ir::StateMachine> stateMachine_;
		std::unique_ptr<ir::input::Mouse> mouseInput_;

		void expectInitialized();

		template <typename T, typename... Args>
		void initializeComponent(std::unique_ptr<T>& component, Args... args) {
			component = std::make_unique<T>(args...);
			if (component == nullptr) {
				throw ir::Exceptions::InitializationError(std::string{typeid(T).name()} + " component of Application");
			}
		}
	};

}






#endif