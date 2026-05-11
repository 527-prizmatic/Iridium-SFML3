#include "Iridium/time.hpp"

namespace ir {
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
			ir::Time::detail::gDeltaUnscaled = 0.f;
			ir::Time::detail::gDeltaScaled = 0.f;
			ir::Time::detail::gClock = ClockType{};
			ir::Time::detail::gFirstTick = true;
		}

		void restart() {
			Timestamp now = ir::Time::detail::gClock.now();
			if (!ir::Time::detail::gFirstTick) /// Removing this safeguard causes issues as last is zero-initialized, causing a half-century-long first tick
				ir::Time::detail::gDeltaUnscaled = static_cast<float>((now - ir::Time::detail::gLast).count() * 1e-9f); /// Multiplying by one billionth because nanoseconds
			ir::Time::detail::gLast = now;

			ir::Time::detail::gDeltaScaled = ir::Time::detail::gDeltaUnscaled * ir::Time::detail::gScale;

			ir::Time::detail::gClock = ClockType{};
			ir::Time::detail::gFirstTick = false;
		}

		float deltaTime() {
			return ir::Time::detail::gDeltaScaled;
		}

		float unscaledDeltaTime() {
			return ir::Time::detail::gDeltaUnscaled;
		}

		void setTimeScale(float scale) {
			ir::Time::detail::gScale = scale;
			ir::Time::detail::gDeltaScaled = ir::Time::detail::gDeltaUnscaled * ir::Time::detail::gScale;
		}

		float getTimeScale() {
			return ir::Time::detail::gScale;
		}

		void resetTimeScale() {
			ir::Time::setTimeScale(1.f);
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
			time += ir::Time::unscaledDeltaTime();
		else
			time += ir::Time::deltaTime();
	}
}
