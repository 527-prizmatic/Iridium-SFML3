#include "Iridium/vector.hpp"
#include "Iridium/math.hpp"

namespace Ir {
	Vector::Vector() {
		this->x = 0.f;
		this->y = 0.f;
	}

	Vector::Vector(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}

	Vector::Vector(const Ir::Vector& _other) {
		this->x = _other.x;
		this->y = _other.y;
	}

	Ir::Vector& Vector::operator=(const Ir::Vector& _other) {
		this->x = _other.x;
		this->y = _other.y;
		return *this;
	}

	bool Vector::IsZero() const {
		return false;
	}

	Ir::Vector Vector::Polar(float _radius, float _angle) {
		Expects(_radius >= 0.f);
		return Ir::Vector(_radius, _angle).PolToRec();
	}
	
	float Vector::Magnitude() const {
		return std::sqrtf(this->MagnitudeSquare());
	}

	float Vector::MagnitudeSquare() const {
		return this->x * this->x + this->y * this->y;
	}
	
	float Vector::Angle(Ir::Vector _reference) const {
		if (this->IsZero())
			return 0.f;
		return std::atan2(this->y , this->x) - std::atan2(_reference.y, _reference.x);
	}
	
	float Vector::Distance(Ir::Vector _other) const {
		return (*this - _other).Magnitude();
	}
	
	Ir::Vector Vector::Normalize() const {
		if (this->IsZero())
			return *this;
		return *this / this->Magnitude();
	}
	
	Ir::Vector Vector::ClampMagnitude(float _max) const {
		Expects(_max >= 0.f);

		float magnitude { this->Magnitude() };
		if (magnitude > _max)
			return *this / magnitude * _max;
		return *this;
	}
	
	Ir::Vector Vector::ClampMagnitude(float _min, float _max) const {
		Expects(_max >= _min);

		float magnitude { this->Magnitude() };
		if (magnitude < _min)
			return *this / magnitude * _min;
		if (magnitude > _max)
			return *this / magnitude * _max;
		return *this;
	}
	
	Ir::Vector Vector::RecToPol() const {
		return Ir::Vector{ this->Magnitude(), this->Angle() };
	}
	
	Ir::Vector Vector::PolToRec() const {
		return Ir::Vector{ this->x * std::cosf(this->y), this->x * std::sinf(this->y) };
	}
	
	Ir::Vector Vector::Rotate(float _angle) const {
		if (Ir::Math::IsZero(_angle) || this->IsZero())
			return *this;
		Ir::Vector v { this->RecToPol() };
		v.y += _angle;
		return v.PolToRec();
	}
	
	Ir::Vector Vector::Rotate(float _angle, Ir::Vector _reference) const {
		return _reference + (*this - _reference).Rotate(_angle);
	}
	
	Ir::Vector Vector::Mirror(Ir::Vector _axis) const {
		if (this->IsZero() || _axis.IsZero())
			return *this;
		float angle { this->Angle(_axis) };
		if (Ir::Math::IsZero(angle))
			return *this;
		return this->Rotate(angle * 2.f);
	}
	
	Ir::Vector Vector::MirrorX() const {
		return Ir::Vector{ -this->x, this->y };
	}
	
	Ir::Vector Vector::MirrorY() const {
		return Ir::Vector{ this->x, -this->y };
	}
	
	Ir::Vector Vector::Negate() const {
		return Ir::Vector{ -this->x, -this->y };
	}
}