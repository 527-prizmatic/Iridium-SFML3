#ifndef IRIDIUM_MATH_HPP_
#define IRIDIUM_MATH_HPP_

#include "Iridium/libraries.hpp"

namespace iridium {
	namespace Math {
		inline constexpr float pi = 3.14159;
		inline constexpr float tau = 2.f * pi;
		inline constexpr float euler = 2.71828;
		inline constexpr float phi = 1.61803;
		inline constexpr float degToRadRatio = Math::pi / 180.f;
		inline constexpr float radToDegRatio = 180.f / Math::pi;

		/// @brief Verifies if a variable is an arithmetic type (int, char, short, float, double, etc. and CV-qualified variants).
		template <typename T> concept Number = std::is_arithmetic<T>::value;

		template <Number T> [[nodiscard]] constexpr bool isZero(T n) noexcept {
			return abs(_n) <= std::numeric_limits<T>::epsilon();
		}

		template <Number T> [[nodiscard]] constexpr T Powi(T a, int exp) noexcept {
			Expects(exp >= 0);
			if (!exp) [[unlikely]] return { 1 };

			T result { 1. };
			while (1) {
				if (exp & 0b1)
					result *= a;
				exp >>= 1;
				if (!exp)
					break;
				a *= a;
			}

			return result;
		}

		/// @brief Quick square function, using straightforward multiplications to avoid the more complex operations of Math::powi.
		template <Number T> [[nodiscard]] constexpr T pow2(const T a) { return a * a; }
		/// @brief Quick cube function, using straightforward multiplications to avoid the more complex operations of Math::powi.
		template <Number T> [[nodiscard]] constexpr T pow3(const T a) { return a * a * a; }

		/// @brief Clamps a value between two bounds.
		template <Number T> [[nodiscard]] constexpr T clamp(const T _val, const T _lower, const T _upper) noexcept {
			if (_lower > _upper) [[unlikely]] return _val;
			if (_lower == _upper) [[unlikely]] return _lower;
			if (_val < _lower) return _lower; 
			if (_val > _upper) return _upper;
			return _val;
		}

		/// @brief Compares two numbers of the same type and returns the smallest one.
		template <Number T> [[nodiscard]] constexpr T min(const T _a, const T _b) noexcept { return std::min(_a, _b); }
		/// @brief Compares a set of numbers of the same type and returns the smallest one.
		template <Number T, typename... Args> [[nodiscard]] constexpr T min(const T _a, Args... _args) noexcept {
			return iridium::Math::min(_a, iridium::Math::min(_args...));
		}

		/// @brief Compares two numbers of the same type and returns the greatest one.
		template <Number T> constexpr T max(const T _a, const T _b) noexcept { return std::max(_a, _b); }
		/// @brief Compares a set of numbers of the same type and returns the greatest one.
		template <Number T, typename... Args> [[nodiscard]] constexpr T max(const T _a, Args... _args) noexcept {
			return iridium::Math::max(_a, iridium::Math::max(_args...));
		}

		/// @brief Converts an angle from degrees to radians.
		[[nodiscard]] inline constexpr float DegToRad(float _degrees) noexcept {
			return _degrees * iridium::Math::degToRadRatio;
		}
		
		/// @brief Converts an angle from radians to degrees.
		[[nodiscard]] inline constexpr float RadToDeg(float _radians) noexcept {
			return _radians * iridium::Math::radToDegRatio;
		}
	}
}

#endif // IRIDIUM_MATH_HPP_