#include "Vector3.h"
#include <shsdk/natives.h>

#include "valarray"

Vector3::Vector3()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vector3::Vector3(const float x, const float y, const float z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector3 Vector3::Cross(const Vector3 left, const Vector3 right)
{
	Vector3 result;
	result.X = left.Y * right.Z - left.Z * right.Y;
	result.Y = left.Z * right.X - left.X * right.Z;
	result.Z = left.X * right.Y - left.Y * right.X;
	return result;
}

Vector3 Vector3::ThisVector() const
{
	return {this->X, this->Y, this->Z};
}

float Vector3::Length() const
{
	return std::sqrt((X * X) + (Y * Y) + (Z * Z));
}

float Vector3::LengthSquared() const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

void Vector3::Normalize()
{
	const float length = Length();
	if (length <= 0.00000001f)
	{ return; }

	const float num = 1.0f / length;
	X *= num;
	Y *= num;
	Z *= num;
}

float Vector3::DistanceTo(const Vector3 position) const
{
	return (ThisVector() - position).Length();
}

float Vector3::DistanceToSquared(const Vector3 position) const
{
	return DistanceSquared(position, ThisVector());
}

float Vector3::DistanceTo2D(const Vector3 position) const
{
	const auto left = Vector3(X, Y, 0.0f);
	const auto right = Vector3(position.X, position.Y, 0.0f);

	return Distance(left, right);
}

float Vector3::DistanceToSquared2D(const Vector3 position) const
{
	const auto left = Vector3(X, Y, 0.0f);
	const auto right = Vector3(position.X, position.Y, 0.0f);

	return DistanceSquared(left, right);
}

float Vector3::ToHeading() const
{
	return MISC::GET_HEADING_FROM_VECTOR_2D(X, Y);
}

float Vector3::Distance(const Vector3 aPos, const Vector3 bPos)
{
	return (aPos - bPos).Length();
}

float Vector3::DistanceSquared(const Vector3 aPos, const Vector3 bPos)
{
	return (aPos - bPos).LengthSquared();
}

float Vector3::Distance2D(const Vector3 aPos, const Vector3 bPos)
{
	const auto a = Vector3(aPos.X, aPos.Y, 0.0f);
	const auto b = Vector3(bPos.X, bPos.Y, 0.0f);

	return (a - b).Length();
}

float Vector3::Distance2DSquared(const Vector3 aPos, const Vector3 bPos)
{
	const auto a = Vector3(aPos.X, aPos.Y, 0.0f);
	const auto b = Vector3(bPos.X, bPos.Y, 0.0f);

	return (a - b).LengthSquared();
}

float Vector3::Angle(Vector3 from, Vector3 to)
{
	// TODO: Implement
	return 0.0f;
}

Vector3 Vector3::operator+(const Vector3 other) const
{
	return {X + other.X, Y + other.Y, Z + other.Z};
}

Vector3 Vector3::operator-(const Vector3 other) const
{
	return {X - other.X, Y - other.Y, Z - other.Z};
}

Vector3 Vector3::operator*(const Vector3 scale) const
{
	return {X * scale.X, Y * scale.Y, Z * scale.Z};
}

Vector3 Vector3::operator*(const float scale) const
{
	return {X * scale, Y * scale, Z * scale};
}

Vector3 Vector3::operator/(const float scale) const
{
	const float invScale = 1.0f / scale;
	return {X * invScale, Y * invScale, Z * invScale};
}
