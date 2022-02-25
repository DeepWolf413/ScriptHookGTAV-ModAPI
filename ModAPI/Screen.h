#pragma once
#include <string>
#include <shsdk/types.h>
#include <shsdk/enums.h>

struct Color;

namespace ModAPI
{
	class Screen
	{
	public:
		static void DrawSprite(const char* category, const char* sprite, const Vector2& position, const Vector2& scale, float rotation, const Color& color);
		static void DisplayText(const char* text, const Vector2& position, const Color& color, bool centered, const Vector2& scale);
		static void DisplayText(const char* text, const Vector2& position, const Color& color, eFont font, bool centered, const Vector2& scale);
		static void DrawRect(const Vector2& position, const Vector2& size, const Color& color);
		static void PrintSubtitle(const char* text);
		static void PrintSubtitle(const char* text, float duration);
		static void ShowHelpTextThisFrame(const std::string& helpText);
		static void ShowHelpTextThisFrame(const std::string& helpText, bool beep);
	};
}
