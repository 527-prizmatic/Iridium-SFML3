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

	/// @brief Simple utility class for handling timers
	/// @todo Decide whether this class is worth keeping (think of use cases, make prototypes, and such)
	struct LocalClock {
	public:
		/// @brief Disables ticking and resets the clock to zero.
		void Stop();

		/// @brief Resets the clock to zero.
		void reset();

		/// @brief Ticks the clock.
		void update();

		float time { 0 }; /// Time since started. Can be mofidied, although ticking is handled by update()
		bool ticking = false; /// Whether the clock is currently ticking
		bool usesUnscaledTime { false }; /// Whether the clock should use unscaled or scaled time
	};
}

#endif // IRIDIUM_TIME_HPP_