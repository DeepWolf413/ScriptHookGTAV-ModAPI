#pragma once
#include <string>
#include <shsdk/types.h>
#include <shsdk/enums.h>

namespace ModAPI
{
	class Screen
	{
	public:
		static void DrawSprite(const char* category, const char* sprite, const Vector2& position, const Vector2& scale, float rotation, int r, int g, int b, int a);
		static void DisplayText(const char* text, const Vector2& position, int r, int g, int b, int a, bool centered, const Vector2& scale);
		static void DisplayText(const char* text, const Vector2& position, int r, int g, int b, int a, eFont font, bool centered, const Vector2& scale);
		static void DrawRect(const Vector2& position, const Vector2& size, int r, int g, int b, int a);
		static void PrintSubtitle(const char* text);
		static void ShowHelpTextThisFrame(const std::string& helpText);
		static void ShowHelpTextThisFrame(const std::string& helpText, bool beep);
	};
}
