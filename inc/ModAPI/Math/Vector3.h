#pragma once

#define ALIGN8 __declspec(align(8))
#include <types.h>

namespace ModAPI::MMath
{
	struct Vector3
	{
		Vector3();
		Vector3(float x, float y, float z);

		static Vector3 FromSHVector3(const ::Vector3& vector);
		static Vector3 Cross(Vector3 left, Vector3 right);
		static float   Distance(Vector3 aPos, Vector3 bPos);
		static float   DistanceSquared(Vector3 aPos, Vector3 bPos);
		static float   Distance2D(Vector3 aPos, Vector3 bPos);
		static float   Distance2DSquared(Vector3 aPos, Vector3 bPos);
		static float   Angle(Vector3 from, Vector3 to);
		
		[[nodiscard]] ::Vector3 ToSHVector3() const;
		[[nodiscard]] float Length() const;
		[[nodiscard]] float LengthSquared() const;
		void  Normalize();
		[[nodiscard]] float DistanceTo(Vector3 position) const;
		[[nodiscard]] float DistanceToSquared(Vector3 position) const;
		[[nodiscard]] float DistanceTo2D(Vector3 position) const;
		[[nodiscard]] float DistanceToSquared2D(Vector3 position) const;
		[[nodiscard]] float ToHeading() const;

		Vector3 operator+(Vector3 other) const;
		Vector3 operator-(Vector3 other) const;
		Vector3 operator*(Vector3 scale) const;
		Vector3 operator*(float scale) const;
		Vector3 operator/(float scale) const;
	
		ALIGN8 float X;
		ALIGN8 float Y;
		ALIGN8 float Z;

	private:
		[[nodiscard]] Vector3 ThisVector() const;
	};
} // namespace
