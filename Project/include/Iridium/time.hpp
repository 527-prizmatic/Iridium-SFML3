#ifndef IRIDIUM_TIME_HPP_
#define IRIDIUM_TIME_HPP_

#include "Iridium/libraries.hpp"

namespace ir {
	/// @todo Replace this with a class
	namespace Time {
		/// @brief Resets the clock's internal states and restarts it.
		void reset();

		/// @brief Restarts the clock.
		void restart();

		/// @return Scaled time elapsed since last restart() call.
		/// This function takes time scale into account.
		float deltaTime();

		/// @return Real time elapsed since last restart() call.
		/// This function does not take time scale into account.
		float unscaledDeltaTime();
		
		/// @brief Sets time scale to a value different than 1.
		/// Time scale directly influences the value of deltaTime(), but not that of unscaledDeltaTime().
		void setTimeScale(float scale);
		
		/// @return Current time scale (default value is 1)
		float getTimeScale();

		/// @brief Resets time scale to 1.
		void resetTimeScale();
	}

	/// @brief Simple utility class for handling timers
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