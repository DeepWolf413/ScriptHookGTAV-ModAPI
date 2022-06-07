#pragma once
#include <string>

#include "math/Color.h"

struct Vector3;
struct Vector2;

namespace ModAPI
{
	class Scaleform final
	{
	public:
		Scaleform();
		Scaleform(const Scaleform& obj);
		Scaleform(int handle);

		int& Handle();
		[[nodiscard]] int GetHandle() const;
		[[nodiscard]] bool HasLoaded() const;
		bool Load(const std::string& scaleformID);
	
		void Unload();

		void PushFunction(const std::string& function) const;
		void PushInteger(int arg);
		void PushBoolean(bool arg);
		void PushFloat(float arg);
		void PushString(const std::string& arg);
		void PushString2(const std::string& arg);
		void PushTextComponent(const std::string& arg);
		void PushRGBA(const Color& arg);
		void PushRGB(const Color& arg);
		void PushVector2(const Vector2& arg);
		void PushVector3(const Vector3& arg);
	
		void PopFunction();
		
		void Render2D(Color color = { 255, 255, 255, 255 }) const;
		void Render2DScreenSpace(const Vector2& location, const Vector2& size, Color color = { 255, 255, 255, 255 }) const;
		void Render3D(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale) const;
		void Render3DAdditive(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale) const;

	private:
		int mHandle;
	};
}
