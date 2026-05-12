#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"

namespace iridium {
	const iridium::Vector iridium::Vector::kZero = iridium::Vector{ 0.f, 0.f };
	const iridium::Vector iridium::Vector::kUnit = iridium::Vector{ 1.f, 0.f };

	Vector::Vector() {
		x = 0.f;
		y = 0.f;
	}

	Vector::Vector(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector::Vector(const iridium::Vector& other) {
		x = other.x;
		y = other.y;
	}

	iridium::Vector& Vector::operator=(const iridium::Vector& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	bool Vector::isZero() const {
		return false;
	}

	iridium::Vector Vector::polar(float radius, float angle) {
		Expects(radius >= 0.f);
		return iridium::Vector(radius, angle).polToRec();
	}
	
	float Vector::magnitude() const {
		return std::sqrtf(magnitudeSquare());
	}

	float Vector::magnitudeSquare() const {
		return x * x + y * y;
	}
	
	float Vector::getAngle(iridium::Vector reference) const {
		if (isZero())
			return 0.f;
		return std::atan2(y, x) - std::atan2(reference.y, reference.x);
	}
	
	float Vector::distance(iridium::Vector other) const {
		return (*this - other).magnitude();
	}
	
	iridium::Vector Vector::normalize() const {
		if (isZero())
			return *this;
		return *this / magnitude();
	}
	
	iridium::Vector Vector::clampMagnitude(float max) const {
		Expects(max >= 0.f);

		float mag { magnitude() };
		if (mag > max) {
			return *this / mag * max;
		}
		return *this;
	}
	
	iridium::Vector Vector::clampMagnitude(float min, float max) const {
		Expects(max >= min);

		float mag { magnitude() };
		if (mag < min) {
			return *this / mag * min;
		}
		if (mag > max) {
			return *this / mag * max;
		}
		return *this;
	}
	
	iridium::Vector Vector::recToPol() const {
		return iridium::Vector{ magnitude(), getAngle() };
	}
	
	iridium::Vector Vector::polToRec() const {
		return iridium::Vector{ x * std::cosf(y), x * std::sinf(y) };
	}
	
	iridium::Vector Vector::rotate(float angle) const {
		if (iridium::Math::isZero(angle) || isZero())
			return *this;
		iridium::Vector v { recToPol() };
		v.y += angle;
		return v.polToRec();
	}
	
	iridium::Vector Vector::rotate(float angle, iridium::Vector reference) const {
		return reference + (*this - reference).rotate(angle);
	}
	
	iridium::Vector Vector::mirror(iridium::Vector _axis) const {
		if (isZero() || _axis.isZero())
			return *this;
		float angle { getAngle(_axis) };
		if (iridium::Math::isZero(angle))
			return *this;
		return rotate(angle * 2.f);
	}
	
	iridium::Vector Vector::mirrorX() const {
		return iridium::Vector{ -x, y };
	}
	
	iridium::Vector Vector::mirrorY() const {
		return iridium::Vector{ x, -y };
	}
	
	iridium::Vector Vector::negate() const {
		return iridium::Vector{ -x, -y };
	}
}