#include "Vector3.h"
#include <inc/natives.h>

#include "valarray"

Vector3::Vector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	
	Vector3::Vector3(const float x, const float y, const float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 Vector3::Cross(const Vector3 left, const Vector3 right)
	{
		Vector3 result;
		result.x = left.y * right.z - left.z * right.y;
		result.y = left.z * right.x - left.x * right.z;
		result.z = left.x * right.y - left.y * right.x;
		return result;
	}

	Vector3 Vector3::ThisVector() const
	{ return Vector3(this->x, this->y, this->z); }
	
	float Vector3::Length() const
	{ return std::sqrt((x * x) + (y * y) + (z * z)); }

	float Vector3::LengthSquared() const
	{ return (x * x) + (y * y) + (z * z); }
	
	void Vector3::Normalize()
	{
		const float length = Length();
		if(length == 0)
		{ return; }

		const float num = 1 / length;
		x *= num;
		y *= num;
		z *= num;
	}

	float Vector3::DistanceTo(const Vector3 position) const
	{ return (ThisVector() - position).Length(); }

	float Vector3::DistanceToSquared(const Vector3 position) const
	{ return DistanceSquared(position, ThisVector()); }

	float Vector3::DistanceTo2D(const Vector3 position) const
	{
		const auto left = Vector3(x, y, 0.0f);
		const auto right = Vector3(position.x, position.y, 0.0f);
		
		return Distance(left, right);
	}

	float Vector3::DistanceToSquared2D(const Vector3 position) const
	{
		const auto left = Vector3(x, y, 0.0f);
		const auto right = Vector3(position.x, position.y, 0.0f);
		
		return DistanceSquared(left, right);
	}

	float Vector3::ToHeading() const
	{ return MISC::GET_HEADING_FROM_VECTOR_2D(x, y); }

	float Vector3::Distance(const Vector3 aPos, const Vector3 bPos)
	{ return (aPos - bPos).Length(); }

	float Vector3::DistanceSquared(const Vector3 aPos, const Vector3 bPos)
	{ return (aPos - bPos).LengthSquared(); }

	float Vector3::Distance2D(const Vector3 aPos, const Vector3 bPos)
	{
		const auto a = Vector3(aPos.x, aPos.y, 0.0f);
		const auto b = Vector3(bPos.x, bPos.y, 0.0f);
		
		return (a - b).Length();
	}

	float Vector3::Distance2DSquared(const Vector3 aPos, const Vector3 bPos)
	{
		const auto a = Vector3(aPos.x, aPos.y, 0.0f);
		const auto b = Vector3(bPos.x, bPos.y, 0.0f);
		
		return (a - b).LengthSquared();
	}

	float Vector3::Angle(Vector3 from, Vector3 to)
	{
		// TODO: Implement
		return 0.0f;
	}

	Vector3 Vector3::Subtract(const Vector3 left, const Vector3 right)
	{ return Vector3(left.x - right.x, left.y - right.y, left.z - right.z); }
	
	Vector3 Vector3::operator+(const Vector3 other) const
	{ return Vector3(x + other.x, y + other.y, z + other.z); }

	Vector3 Vector3::operator-(const Vector3 other) const
	{ return Vector3(x - other.x, y - other.y, z - other.z); }

	Vector3 Vector3::operator*(const Vector3 scale) const
	{ return Vector3(x * scale.x, y * scale.y, z * scale.z); }

	Vector3 Vector3::operator*(const float scale) const
	{ return Vector3(x * scale, y * scale, z * scale); }

	Vector3 Vector3::operator/(const float scale) const
	{
		const float invScale = 1.0f / scale;
		return Vector3(x * invScale, y * invScale, z * invScale);
	}

	bool Vector3::operator==(const Vector3 other) const
	{ return x == other.x && y == other.y && z == other.z; }

	bool Vector3::operator!=(const Vector3 other) const
	{ return x != other.x || y != other.y || z != other.z; }