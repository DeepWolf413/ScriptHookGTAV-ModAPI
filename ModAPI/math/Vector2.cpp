#include "Vector2.h"
#include <shsdk/natives.h>

#include "valarray"

Vector2::Vector2()
{
	this->X = 0;
	this->Y = 0;
}

Vector2::Vector2(const float x, const float y)
{
	this->X = x;
	this->Y = y;
}

float Vector2::Cross(const Vector2 left, const Vector2 right)
{ return left.X * right.Y - left.Y * right.X; }

Vector2 Vector2::ThisVector() const
{
	return {this->X, this->Y};
}

float Vector2::Length() const
{
	return std::sqrt((X * X) + (Y * Y));
}

float Vector2::LengthSquared() const
{
	return (X * X) + (Y * Y);
}

void Vector2::Normalize()
{
	const float length = Length();
	if (length <= 0.00000001f)
	{ return; }

	const float num = 1.0f / length;
	X *= num;
	Y *= num;
}

float Vector2::DistanceTo(const Vector2 position) const
{
	return (ThisVector() - position).Length();
}

float Vector2::DistanceToSquared(const Vector2 position) const
{
	return DistanceSquared(position, ThisVector());
}

float Vector2::Distance(const Vector2 aPos, const Vector2 bPos)
{
	return (aPos - bPos).Length();
}

float Vector2::DistanceSquared(const Vector2 aPos, const Vector2 bPos)
{
	return (aPos - bPos).LengthSquared();
}

float Vector2::Angle(Vector2 from, Vector2 to)
{
	// TODO: Implement
	return 0.0f;
}

Vector2 Vector2::operator+(const Vector2 other) const
{
	return {X + other.X, Y + other.Y};
}

Vector2 Vector2::operator-(const Vector2 other) const
{
	return {X - other.X, Y - other.Y};
}

Vector2 Vector2::operator*(const Vector2 scale) const
{
	return {X * scale.X, Y * scale.Y};
}

Vector2 Vector2::operator*(const float scale) const
{
	return {X * scale, Y * scale};
}

Vector2 Vector2::operator/(const float scale) const
{
	const float invScale = 1.0f / scale;
	return {X * invScale, Y * invScale};
}
