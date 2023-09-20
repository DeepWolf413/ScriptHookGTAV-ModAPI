#pragma once
#include <string>

#include "../MathAPI.h"

namespace ModAPI::UI
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
		void PushRGBA(const MMath::Color& arg);
		void PushRGB(const MMath::Color& arg);
		void PushVector2(const MMath::Vector2& arg);
		void PushVector3(const MMath::Vector3& arg);
	
		void PopFunction();
		
		void Render2D(MMath::Color color = { 255, 255, 255, 255 }) const;
		void Render2DScreenSpace(const MMath::Vector2& location, const MMath::Vector2& size, MMath::Color color = { 255, 255, 255, 255 }) const;
		void Render3D(const MMath::Vector3& position, const MMath::Vector3& rotation, const MMath::Vector3& unk, const MMath::Vector3& scale) const;
		void Render3DAdditive(const MMath::Vector3& position, const MMath::Vector3& rotation, const MMath::Vector3& unk, const MMath::Vector3& scale) const;

	private:
		int handle;
	};
}
