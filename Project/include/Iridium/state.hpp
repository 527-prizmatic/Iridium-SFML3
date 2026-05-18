#ifndef IRIDIUM_STATE_HPP_
#define IRIDIUM_STATE_HPP_

#include <typeinfo>

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"
#include "Iridium/state_machine.hpp"

#include "Iridium/state.inl"

namespace ir {

	/// @brief CRTP core for state classes.
	/// All states in use must derive from this one, using themselves as template argument.
	/// Ideally, no resources should be allocated during construction; everything should be done in onInitialize() instead.
	template <ir::detail::states::NoRttiReserved T>
	class StateBase {
	private:
		ir::StateMachine* stateMachine_;
	
	public:
		void onInitialize() {
			if constexpr (requires() { onInitialize(); }) {
				static_cast<T*>(this)->onInitialize();
			}
		}
		
		void onReceiveEvent(const sf::Event& event) {
			if constexpr (requires(const sf::Event& event) { onReceiveEvent(event); }) {
				static_cast<T*>(this)->onReceiveEvent(event);
			}
		}
		
		void onUpdate(ir::ApplicationWindow& window) {
			if constexpr (requires(ir::ApplicationWindow& window) { onUpdate(window); }) {
				static_cast<T*>(this)->onUpdate(window);
			}
		}
		
		void onRender(ir::ApplicationWindow& window) {
			if constexpr (requires(ir::ApplicationWindow& window) { onRender(window); }) {
				static_cast<T*>(this)->onRender(window);
			}
		}
		
		void onEnd() {
			if constexpr (requires() { onEnd(); }) {
				static_cast<T*>(this)->onEnd();
			}
		}

		static std::string meta_name() {
			return typeid(T).name();
		}

		template <typename U>
		void meta_load() {
			stateMachine_->loadState<U>();
		}

		void meta_setStateMachine(ir::StateMachine* sm) {
			stateMachine_ = sm;
		}
	
		void meta_exit() {
			stateMachine_->requestExit();
		}
	};
}

#endif // IRIDIUM_STATE_HPP_