/// @brief Used to declare derived classes of iridium::State.
/// Also contains a set of functions for smooth integration with the state machine.
/// @todo Replace this with CRTP (ew jreg)
#define IRIDIUM_STATE_CLASS(s)							\
class s : public ir::State {							\
private:												\
	iridium::StateMachine* ir_machine_;					\
														\
public:													\
	static std::string ir_getStateName() {				\
		return typeid(s).name();						\
	}													\
														\
	template <typename T>								\
	void loadState() {									\
		ir_machine_->loadState<T>();					\
}														\
														\
	void ir_setStateMachine(iridium::StateMachine* sm) {\
		ir_machine_ = sm;								\
	}													\
														\
	void requestExit() {								\
		ir_machine_->requestExit();						\
	}
