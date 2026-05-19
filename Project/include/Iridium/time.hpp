#ifndef IRIDIUM_TIME_HPP_
#define IRIDIUM_TIME_HPP_

#include "Iridium/libraries.hpp"

namespace ir {	
	using ClockType = std::chrono::steady_clock;
	using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

	class GameClock {
	public:
		GameClock();

		void zero(bool resetTimeScale = false);
		void startTick();

		void setTimeScale(float timeScale);

		float getDeltaTime();
		float getDeltaTimeUnscaled();
		float getTimeScale();

	private:
		ClockType clock_;
		Timestamp last_;
		float deltaUnscaled_ { 0.f };
		float deltaScaled_ { 0.f };
		float timeScale_ { 1.f };
		bool isFirstTick_ { true };
	};
}

#endif // IRIDIUM_TIME_HPP_