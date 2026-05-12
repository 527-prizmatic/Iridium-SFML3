/// @brief Used to declare derived classes of iridium::State.
/// Also contains a set of functions for smooth integration with the state machine.
#define IRIDIUM_STATE_CLASS(s)						\
class s : public iridium::State {						\
private:											\
	static std::string ir_m_typeName;				\
	iridium::StateMachine* ir_m_machine;					\
													\
public:												\
	static std::string getStateName() {				\
		return typeid(s).name();					\
	}												\
													\
	template <typename T>							\
	void loadState() {								\
		this->ir_m_machine->loadState<T>();			\
}													\
													\
	void setStateMachine(iridium::StateMachine* _sm) {	\
		this->ir_m_machine = _sm;					\
	}												\
													\
	void requestExit() {							\
		this->ir_m_machine->requestExit();			\
	}
