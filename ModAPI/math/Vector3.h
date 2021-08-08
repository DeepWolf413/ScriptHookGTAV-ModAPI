#pragma once

#define ALIGN8 __declspec(align(8))


	struct Vector3 {
	public:
		Vector3();
		Vector3(float x, float y, float z);
	
		static Vector3 Cross(Vector3 left, Vector3 right);
		static float   Distance(Vector3 aPos, Vector3 bPos);
		static float   DistanceSquared(Vector3 aPos, Vector3 bPos);
		static float   Distance2D(Vector3 aPos, Vector3 bPos);
		static float   Distance2DSquared(Vector3 aPos, Vector3 bPos);
		static float   Angle(Vector3 from, Vector3 to);
		static Vector3 Subtract(Vector3 left, Vector3 right);
	
		float Length() const;
		float LengthSquared() const;
		void  Normalize();
		float DistanceTo(Vector3 position) const;
		float DistanceToSquared(Vector3 position) const;
		float DistanceTo2D(Vector3 position) const;
		float DistanceToSquared2D(Vector3 position) const;
		float ToHeading() const;

		Vector3 operator+(Vector3 other) const;
		Vector3 operator-(Vector3 other) const;
		Vector3 operator*(Vector3 scale) const;
		Vector3 operator*(float scale) const;
		Vector3 operator/(float scale) const;
		bool    operator==(Vector3 other) const;
		bool    operator!=(Vector3 other) const;
	
		ALIGN8 float x;
		ALIGN8 float y;
		ALIGN8 float z;

	private:
		Vector3 ThisVector() const;
	};

	static_assert(sizeof(Vector3) == 24, "");