#ifndef IRIDIUM_STATE_HPP_
#define IRIDIUM_STATE_HPP_

#include <typeinfo>

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"
#include "Iridium/state_machine.hpp"

#include "Iridium/detail/state.inl"

namespace ir {
	class ApplicationContext;

	/// @brief CRTP core for state classes.
	/// All states in use must derive from this one, using themselves as template argument.
	/// Ideally, no resources should be allocated during construction; everything should be done in onInitialize() instead.
	template <ir::detail::states::NoRttiReserved T>
	class StateBase {
	private:
		ir::StateMachine* stateMachine_;

	protected:
		ApplicationContext* context_;

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
		
		void onUpdate() {
			if constexpr (requires() { onUpdate(); }) {
				static_cast<T*>(this)->onUpdate();
			}
		}
		
		void onRender() {
			if constexpr (requires() { onRender(); }) {
				static_cast<T*>(this)->onRender();
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

		void meta_setContext(ApplicationContext* context) {
			context_ = context;
		}
	};
}

#endif // IRIDIUM_STATE_HPP_