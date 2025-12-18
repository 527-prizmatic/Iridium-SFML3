#include "Iridium/time.hpp"

namespace Ir {
	namespace Time {
		using ClockType = std::chrono::steady_clock;
    	using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

		namespace _priv {
			ClockType g_clock;
			Timestamp g_last;
			float g_deltaUnscaled { 0.f };
			float g_deltaScaled { 0.f };
			float g_scale { 1.f };
			bool g_firstTick { true };
		}

		void Reset() {
			Ir::Time::_priv::g_deltaUnscaled = 0.f;
			Ir::Time::_priv::g_deltaScaled = 0.f;
			Ir::Time::_priv::g_clock = ClockType{};
			Ir::Time::_priv::g_firstTick = true;
		}

		void Restart() {
			Timestamp now = Ir::Time::_priv::g_clock.now();
			if (!Ir::Time::_priv::g_firstTick) /// Removing this safeguard causes issues as _last is zero-initialized, causing a half-century-long first tick
				Ir::Time::_priv::g_deltaUnscaled = static_cast<float>((now - Ir::Time::_priv::g_last).count() * 1e-9f); /// Multiplying by one billionth for nanoseconds
			Ir::Time::_priv::g_last = now;

			Ir::Time::_priv::g_deltaScaled = Ir::Time::_priv::g_deltaUnscaled * Ir::Time::_priv::g_scale;

			Ir::Time::_priv::g_clock = ClockType{};
			Ir::Time::_priv::g_firstTick = false;
		}

		float Delta() {
			return Ir::Time::_priv::g_deltaScaled;
		}

		float DeltaUnscaled() {
			return Ir::Time::_priv::g_deltaUnscaled;
		}

		void SetTimeScale(float _new_scale) {
			Ir::Time::_priv::g_scale = _new_scale;
			Ir::Time::_priv::g_deltaScaled = Ir::Time::_priv::g_deltaUnscaled * Ir::Time::_priv::g_scale;
		}

		float GetTimeScale() {
			return Ir::Time::_priv::g_scale;
		}

		void ResetTimeScale() {
			Ir::Time::SetTimeScale(1.f);
		}
	}

	void LocalClock::Stop() {
		this->ticking = false;
		this->Reset();
	}

	void LocalClock::Reset() {
		this->time = 0.f;
	}

	void LocalClock::Update() {
		if (!this->ticking)
			return;
		
		if (this->usesUnscaledTime)
			this->time += Ir::Time::DeltaUnscaled();
		else
			this->time += Ir::Time::Delta();
	}
}
