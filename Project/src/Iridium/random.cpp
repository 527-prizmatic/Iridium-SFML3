#include "Iridium/random.hpp"
#include "Iridium/math.hpp"

namespace Ir {
	namespace Random {
		namespace _priv {
			std::mt19937 g_generator { static_cast<unsigned int>(std::time(nullptr)) };
		}

		int Integer32() {
			return Ir::Random::_priv::g_generator();
		}

		int Range(int _max) {
			if (_max <= 0)
				return 0;
			return Ir::Random::_priv::g_generator() % _max;
		}

		int Range(int _min, int _max) {
			if (_max <= _min + 1)
				return _min;
			return _min + Ir::Random::_priv::g_generator() % (_max - _min);
		}

		bool Chance(float _chance) {
			return Ir::Random::Range(1'000'000) < static_cast<int>(Ir::Math::Clamp(_chance, 0.f, 1.f) * 1'000'000);
		}

		int DiceRoll(int _count, int _size) {
			if (_count <= 0 || _size <= 2) return 0;
			int result { 0 };
			for (int i { 0 }; i < _count; i++) {
				result += Ir::Random::Range(1, _size + 1);
			}
			return result;
		}

		int DiceRoll(std::string _roll) {
			std::size_t position = _roll.find('d');
			Ensures(position != _roll.npos);
			try {
				int count = position == 0 ? 1 : std::stoi(_roll.substr(0, position));
				int size = std::stoi(_roll.substr(position + 1));
				return Ir::Random::DiceRoll(count, size);
			}
			catch (std::exception& _e) {
				return 0;
			}
		}
	}
}