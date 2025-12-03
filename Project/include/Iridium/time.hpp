#ifndef IRIDIUM_TIME_HPP_
#define IRIDIUM_TIME_HPP_

#include "Iridium/libraries.hpp"

namespace Ir {
	namespace Time {
		/// @brief Resets the clock's internal states and restarts it.
		void Reset();

		/// @brief Restarts the clock.
		void Restart();

		/// @return Scaled time elapsed since last Restart() call.
		/// This function takes time scale into account.
		float Delta();

		/// @return Real time elapsed since last Restart() call.
		/// This function does not take time scale into account.
		float DeltaUnscaled();
		
		/// @brief Sets time scale to a value different than 1.
		/// Time scale directly influences the value of Delta(), but not that of DeltaUnscaled().
		void SetTimeScale(float _new_scale);
		
		/// @return Current time scale (default value is 1)
		float GetTimeScale();

		/// @brief Resets time scale to 1.
		void ResetTimeScale();
	}

	/// @brief Simple utility class for handling timers
	struct LocalClock {
	public:
		/// @brief Disables ticking and resets the clock to zero.
		void Stop();

		/// @brief Resets the clock to zero.
		void Reset();

		/// @brief Ticks the clock.
		void Update();

		float time { 0 }; /// Time since started. Can be mofidied, although ticking is handled by Update()
		bool ticking = false; /// Whether the clock is currently ticking
		bool usesUnscaledTime { false }; /// Whether the clock should use unscaled or scaled time
	};
}

#endif IRIDIUM_TIME_HPP_