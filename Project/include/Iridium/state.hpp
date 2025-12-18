#ifndef IRIDIUM_STATE_HPP_
#define IRIDIUM_STATE_HPP_

#include <typeinfo>

#include "Iridium/libraries.hpp"
#include "Iridium/application_window.hpp"
#include "Iridium/state_machine.hpp"

/// @todo Edit this macro to also add state machine functions and the like
#define IRIDIUM_STATE_CLASS(s)							\
class s : public Ir::State {							\
private:												\
	static std::string ir_m_typeName;					\
	Ir::StateMachine* ir_m_machine;						\
														\
public:													\
	static std::string GetStateName() {					\
		return typeid(s).name();						\
	}													\
														\
	template <typename T>								\
	bool LoadState() {									\
		return this->ir_m_machine->LoadState<T>();		\
	}													\
														\
	void SetStateMachine(Ir::StateMachine* _sm) {		\
		this->ir_m_machine = _sm;						\
	}													\


namespace Ir {
	/// @brief Core state machine state class for main game logic.
	/// All states in use should derive from this one, as well as include the STATE_GENERATED_BODY.
	/// Ideally, no resources should be initialized during construction; everything should be done in OnInitialize() instead.
	class State {
	private:
		
	public:
		State() = default;
		~State() = default;

		virtual void OnInitialize() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnReceiveEvent(const sf::Event& _e) = 0;
		virtual void OnRender(Ir::ApplicationWindow& _window) = 0;
		virtual void OnEnd() = 0;
	
	};
}




#endif // IRIDIUM_STATE_HPP_