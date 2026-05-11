/// @brief Used to declare derived classes of Ir::State.
/// Also contains a set of functions for smooth integration with the state machine.
#define IRIDIUM_STATE_CLASS(s)						\
class s : public Ir::State {						\
private:											\
	static std::string ir_m_typeName;				\
	Ir::StateMachine* ir_m_machine;					\
													\
public:												\
	static std::string GetStateName() {				\
		return typeid(s).name();					\
	}												\
													\
	template <typename T>							\
	void LoadState() {								\
		this->ir_m_machine->LoadState<T>();			\
}													\
													\
	void SetStateMachine(Ir::StateMachine* _sm) {	\
		this->ir_m_machine = _sm;					\
	}												\
													\
	void RequestExit() {							\
		this->ir_m_machine->RequestExit();			\
	}
