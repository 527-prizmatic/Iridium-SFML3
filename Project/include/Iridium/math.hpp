#ifndef IRIDIUM_MATH_HPP_
#define IRIDIUM_MATH_HPP_

#include "Iridium/libraries.hpp"

namespace Ir {
	namespace Math {
		inline constexpr float pi = 3.14159; /// @brief Circle constant
		inline constexpr float tau = 2.f * pi; /// @brief Double the circle constant
		inline constexpr float euler = 2.71828; /// @brief Exponential constant
		inline constexpr float phi = 1.61803; /// @brief Golden ratio
		inline constexpr float degToRadRatio = Math::pi / 180.f; /// @brief Conversion ratio from degrees to radians
		inline constexpr float radToDegRatio = 180.f / Math::pi; /// @brief Conversion ratio from radians to degrees

	/// @brief Verifies if a variable is an arithmetic type (int, char, short, float, double, etc. and CV-qualified variants).
		template <typename T> concept Number = std::is_arithmetic<T>::value;

		template <Number T> [[nodiscard]] constexpr bool IsZero(T _n) noexcept {
			return abs(_n) <= std::numeric_limits<T>::epsilon();
		}

		template <Number T> [[nodiscard]] constexpr T Powi(T _a, int _exp) noexcept {
			Expects(_exp >= 0);
			if (!_exp) [[unlikely]] return { 1 };

			T result { 1. };
			while (1) {
				if (_exp & 0b1)
					result *= _a;
				_exp >>= 1;
				if (!_exp)
					break;
				_a *= _a;
			}

			return result;
		}

		/// @brief Quick square function, using straightforward multiplications to avoid the more complex operations of Math::powi.
		template <Number T> [[nodiscard]] constexpr T Pow2(const T _a) { return _a * _a; }
		/// @brief Quick cube function, using straightforward multiplications to avoid the more complex operations of Math::powi.
		template <Number T> [[nodiscard]] constexpr T Pow3(const T _a) { return _a * _a * _a; }

		/// @brief Clamps a value between two bounds.
		template <Number T> [[nodiscard]] constexpr T Clamp(const T _val, const T _lower, const T _upper) noexcept {
			if (_lower > _upper) [[unlikely]] return _val;
			if (_lower == _upper) [[unlikely]] return _lower;
			if (_val < _lower) return _lower; 
			if (_val > _upper) return _upper;
			return _val;
		}

		/// @brief Compares two numbers of the same type and returns the smallest one.
		template <Number T> [[nodiscard]] constexpr T Min(const T _a, const T _b) noexcept { return std::min(_a, _b); }
		/// @brief Compares a set of numbers of the same type and returns the smallest one.
		template <Number T, typename... Args> [[nodiscard]] constexpr T Min(const T _a, Args... _args) noexcept {
			return Ir::Math::Min(_a, Ir::Math::Min(_args...));
		}

		/// @brief Compares two numbers of the same type and returns the greatest one.
		template <Number T> constexpr T Max(const T _a, const T _b) noexcept { return std::max(_a, _b); }
		/// @brief Compares a set of numbers of the same type and returns the greatest one.
		template <Number T, typename... Args> [[nodiscard]] constexpr T Max(const T _a, Args... _args) noexcept {
			return Ir::Math::Max(_a, Ir::Math::Max(_args...));
		}

		/// @brief Converts an angle from degrees to radians.
		[[nodiscard]] inline constexpr float DegToRad(float _degrees) noexcept {
			return _degrees * Ir::Math::degToRadRatio;
		}
		
		/// @brief Converts an angle from radians to degrees.
		[[nodiscard]] inline constexpr float RadToDeg(float _radians) noexcept {
			return _radians * Ir::Math::radToDegRatio;
		}
	}
}
		
/// @brief Converts into radians a number assumed to be an angle in degrees.
[[nodiscard]] inline constexpr float operator ""_rad(long double _angle) noexcept {
	return Ir::Math::DegToRad(_angle);
}

/// @brief Converts into degrees a number assumed to be an angle in radians.
[[nodiscard]] inline constexpr float operator ""_deg(long double _angle) noexcept {
	return Ir::Math::RadToDeg(_angle);
}

#endif // IRIDIUM_MATH_HPP_