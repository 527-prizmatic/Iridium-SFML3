#ifndef IRIDIUM_VECTOR_HPP_
#define IRIDIUM_VECTOR_HPP_

namespace Ir {
	struct Vector {
	public:
		float x; /// x component
		float y; /// y component

		Vector();

		/// @brief Constructs a vector from cartesian coordinates.
		Vector(float _x, float _y);

		/// @brief Constructs a vector from a SFML vector.
		template <typename T> static Ir::Vector FromSFMLVector(sf::Vector2<T> _other) {
			return Ir::Vector(static_cast<float>(_other.x), static_cast<float>(_other.y));
		}

		/// @brief Copies a vector
		Vector(const Ir::Vector& _other);

		Ir::Vector& operator=(const Ir::Vector& _other);
		
		/// @brief Constructs a cartesian-space vector from polar coordinates.
		[[nodiscard]] static Ir::Vector Polar(float _radius, float _angle);

		/// @return Whether both the vector's components are equal to zero 
		[[nodiscard]] bool IsZero() const;

		/// @return Vector's magnitude
		/// @note As computing magnitude requires an expensive square root, consider using MagnitudeSquare if possible.
		[[nodiscard]] float Magnitude() const;

		/// @return Vector's square magnitude
		[[nodiscard]] float MagnitudeSquare() const;

		/// @return Angle between the vector and another one. If no reference vector is provided, the angle returned will be relative to the X axis.
		[[nodiscard]] float Angle(Ir::Vector _reference = Ir::Vector{1.f, 0.f}) const;

		/// @return Distance between this vector and another one
		[[nodiscard]] float Distance(Ir::Vector _other) const;
		
		/// @return This vector, normalized
		[[nodiscard]] Ir::Vector Normalize() const;

		/// @brief Clamps the vector's magnitude below the given threshold.
		[[nodiscard]] Ir::Vector ClampMagnitude(float _max) const;

		/// @brief Clamps the vector's magnitude between the given thresholds.
		[[nodiscard]] Ir::Vector ClampMagnitude(float _min, float _max) const;

		/// @brief Converts a cartesian-space vector into polar vector space.
		[[nodiscard]] Ir::Vector RecToPol() const;
		
		/// @brief Converts a polar-space vector into cartesian vector space.
		[[nodiscard]] Ir::Vector PolToRec() const;

		/// @brief Rotates about the given angle.
		[[nodiscard]] Ir::Vector Rotate(float _angle) const;

		/// @brief Rotates about the given angle, using a point as reference.
		[[nodiscard]] Ir::Vector Rotate(float _angle, Ir::Vector _reference) const;

		/// @return Axial mirror image of the vector about the given symmetry axis
		[[nodiscard]] Ir::Vector Mirror(Ir::Vector _axis) const;

		/// @return Axial mirror image of the vector about the X axis
		[[nodiscard]] Ir::Vector MirrorX() const;

		/// @return Axial mirror image of the vector about the Y axis
		[[nodiscard]] Ir::Vector MirrorY() const;

		/// @return Opposite of the vector
		[[nodiscard]] Ir::Vector Negate() const;

		template <typename T>
		[[nodiscard]] explicit operator sf::Vector2<T>() const {
			return sf::Vector2<T>{ static_cast<T>(this->x), static_cast<T>(this->y) };
		}
		
		[[nodiscard]] operator std::string() const {
			return '(' + std::to_string(this->x) + ' ' + std::to_string(this->y) + ')';
		}

		// [[nodiscard]] inline explicit operator sf::Vector2i() const {
		// 	return sf::Vector2i{ static_cast<int>(this->x), static_cast<int>(this->y) };
		// }

		// [[nodiscard]] inline explicit operator sf::Vector2u() const {
		// 	return sf::Vector2u{ static_cast<unsigned int>(this->x), static_cast<unsigned int>(this->y) };
		// }
		
		// [[nodiscard]] inline explicit operator sf::Vector2f() const {
		// 	return sf::Vector2f{ this->x, this->y };
		// }
		
		[[nodiscard]] inline Ir::Vector operator+(const Ir::Vector& _other) const {
			return Ir::Vector { this->x + _other.x, this->y + _other.y };
		}
		
		[[nodiscard]] inline Ir::Vector operator-(const Ir::Vector& _other) const {
			return Ir::Vector { this->x - _other.x, this->y - _other.y };
		}
		
		[[nodiscard]] inline Ir::Vector operator-() const {
			return Ir::Vector { -this->x, -this->y };
		}
		
		[[nodiscard]] inline Ir::Vector operator*(const float _other) const {
			return Ir::Vector { this->x * _other, this->y * _other };
		}
		
		[[nodiscard]] inline Ir::Vector operator/(const float _other) const {
			return Ir::Vector { this->x / _other, this->y / _other };
		}
		
		[[nodiscard]] inline float operator*(const Ir::Vector& _other) const {
			return this->x * _other.x + this->y * _other.y;
		}
		
		
		inline void operator+=(const Ir::Vector& _other) {
			this->x += _other.x;
			this->y += _other.y;
		}
		
		inline void operator-=(const Ir::Vector& _other) {
			this->x -= _other.x;
			this->y -= _other.y;
		}
		
		inline void operator*=(const float _other) {
			this->x *= _other;
			this->y *= _other;
		}
		
		inline void operator/=(const float _other) {
			this->x /= _other;
			this->y /= _other;
		}
		
		[[nodiscard]] inline bool operator==(const Ir::Vector& _other) const {
			return (*this - _other).IsZero();
		}

		static const Ir::Vector zero;
		static const Ir::Vector unit;
	};
}

#endif // IRIDIUM_VECTOR_HPP_