#include "Iridium/random.hpp"
#include "Iridium/math.hpp"

namespace iridium {
	namespace Random {
		namespace detail {
			std::mt19937 _generator { static_cast<unsigned int>(std::time(nullptr)) };
		}

		int integer32() {
			return iridium::Random::detail::_generator();
		}

		int range(int _max) {
			if (_max <= 0)
				return 0;
			return iridium::Random::detail::_generator() % _max;
		}

		int range(int _min, int _max) {
			if (_max <= _min + 1)
				return _min;
			return _min + iridium::Random::detail::_generator() % (_max - _min);
		}

		bool chance(float _chance) {
			return iridium::Random::range(1'000'000) < static_cast<int>(iridium::Math::clamp(_chance, 0.f, 1.f) * 1'000'000);
		}

		int diceRoll(int _count, int _size) {
			if (_count <= 0 || _size <= 2) return 0;
			int result { 0 };
			for (int i { 0 }; i < _count; i++) {
				result += iridium::Random::range(1, _size + 1);
			}
			return result;
		}

		int diceRoll(std::string _roll) {
			std::size_t position = _roll.find('d');
			Ensures(position != _roll.npos);
			try {
				int count = position == 0 ? 1 : std::stoi(_roll.substr(0, position));
				int size = std::stoi(_roll.substr(position + 1));
				return iridium::Random::diceRoll(count, size);
			}
			catch (std::exception& _e) {
				return 0;
			}
		}
	}
}