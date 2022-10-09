#pragma once

#define ALIGN8 __declspec(align(8))

namespace ModAPI::MMath
{
	struct Vector2 {
		Vector2();
		Vector2(float x, float y);
	
		static float Cross(Vector2 left, Vector2 right);
		static float   Distance(Vector2 aPos, Vector2 bPos);
		static float   DistanceSquared(Vector2 aPos, Vector2 bPos);
		static float   Angle(Vector2 from, Vector2 to);

		[[nodiscard]] float Length() const;
		[[nodiscard]] float LengthSquared() const;
		void  Normalize();
		[[nodiscard]] float DistanceTo(Vector2 position) const;
		[[nodiscard]] float DistanceToSquared(Vector2 position) const;

		Vector2 operator+(Vector2 other) const;
		Vector2 operator-(Vector2 other) const;
		Vector2 operator*(Vector2 scale) const;
		Vector2 operator*(float scale) const;
		Vector2 operator/(float scale) const;
	
		ALIGN8 float X;
		ALIGN8 float Y;

	private:
		[[nodiscard]] Vector2 ThisVector() const;
	};
}
