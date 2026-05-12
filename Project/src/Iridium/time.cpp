#include "Iridium/time.hpp"

namespace iridium {
	namespace Time {
		using ClockType = std::chrono::steady_clock;
    	using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

		namespace detail {
			ClockType gClock;
			Timestamp gLast;
			float gDeltaUnscaled { 0.f };
			float gDeltaScaled { 0.f };
			float gScale { 1.f };
			bool gFirstTick { true };
		}

		void reset() {
			iridium::Time::detail::gDeltaUnscaled = 0.f;
			iridium::Time::detail::gDeltaScaled = 0.f;
			iridium::Time::detail::gClock = ClockType{};
			iridium::Time::detail::gFirstTick = true;
		}

		void restart() {
			Timestamp now = iridium::Time::detail::gClock.now();
			if (!iridium::Time::detail::gFirstTick) /// Removing this safeguard causes issues as _last is zero-initialized, causing a half-century-long first tick
				iridium::Time::detail::gDeltaUnscaled = static_cast<float>((now - iridium::Time::detail::gLast).count() * 1e-9f); /// Multiplying by one billionth because nanoseconds
			iridium::Time::detail::gLast = now;

			iridium::Time::detail::gDeltaScaled = iridium::Time::detail::gDeltaUnscaled * iridium::Time::detail::gScale;

			iridium::Time::detail::gClock = ClockType{};
			iridium::Time::detail::gFirstTick = false;
		}

		float deltaTime() {
			return iridium::Time::detail::gDeltaScaled;
		}

		float unscaledDeltaTime() {
			return iridium::Time::detail::gDeltaUnscaled;
		}

		void setTimeScale(float _new_scale) {
			iridium::Time::detail::gScale = _new_scale;
			iridium::Time::detail::gDeltaScaled = iridium::Time::detail::gDeltaUnscaled * iridium::Time::detail::gScale;
		}

		float getTimeScale() {
			return iridium::Time::detail::gScale;
		}

		void resetTimeScale() {
			iridium::Time::setTimeScale(1.f);
		}
	}

	void LocalClock::Stop() {
		ticking = false;
		reset();
	}

	void LocalClock::reset() {
		time = 0.f;
	}

	void LocalClock::update() {
		if (!ticking)
			return;
		
		if (usesUnscaledTime)
			time += iridium::Time::unscaledDeltaTime();
		else
			time += iridium::Time::deltaTime();
	}
}
