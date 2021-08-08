#include "Screen.h"

#include <inc/natives.h>

void ModAPI::Screen::DrawSprite(const char* category, const char* sprite, Vector2 position, Vector2 scale, float rotation,
                        int r, int g, int b, int a)
{
	const float fX = position.x + scale.x / 2;
	const float fY = position.y + scale.y / 2;
	if (!TXD::DOES_STREAMED_TEXTURE_DICT_EXIST(category))
	{
		return;
	}

	int ticks = 0;
	while (!TXD::HAS_STREAMED_TEXTURE_DICT_LOADED(category))
	{
		TXD::REQUEST_STREAMED_TEXTURE_DICT(category, 0);
		WAIT(1);
		ticks++;

		if (ticks >= 5000)
		{
			break;
		}
	}

	GRAPHICS::DRAW_SPRITE(category, sprite, fX, fY, scale.x, scale.y, rotation, r, g, b, a, 1);
	TXD::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
}

void ModAPI::Screen::DisplayText(const char* text, Vector2 position, int r, int g, int b, int a, bool centered, Vector2 scale)
{
	HUD::_SET_TEXT_COLOR(r, g, b, a);
	HUD::SET_TEXT_SCALE(scale.x, scale.y);
	HUD::SET_TEXT_CENTRE(centered);
	const char* literalString = MISC::VAR_STRING(10, "LITERAL_STRING", text);
	HUD::_DISPLAY_TEXT(literalString, position.x, position.y);
}

void ModAPI::Screen::DisplayText(const char* text, Vector2 position, int r, int g, int b, int a, eFont font, bool centered,
	Vector2 scale)
{
	HUD::_SET_TEXT_COLOR(r, g, b, a);
	HUD::SET_TEXT_SCALE(scale.x, scale.y);
	HUD::SET_TEXT_CENTRE(centered);
	const char* literalString = MISC::VAR_STRING(10, "LITERAL_STRING", GetFontString(text, font).c_str());
	literalString = MISC::VAR_STRING(42, "COLOR_STRING", nullptr, literalString);
	HUD::_DISPLAY_TEXT(literalString, position.x, position.y);
}

void ModAPI::Screen::DrawRect(Vector2 position, Vector2 size, int r, int g, int b, int a)
{
	const float fX = position.x + size.x / 2;
	const float fY = position.y + size.y / 2;
	GRAPHICS::DRAW_RECT(fX, fY, size.x, size.y, r, g, b, a, true, true);
}

void ModAPI::Screen::PrintSubtitle(const char* text)
{
	const char* literalString = MISC::VAR_STRING(10, "LITERAL_STRING", text);
	UILOG::_UILOG_SET_CACHED_OBJECTIVE(literalString);
	UILOG::_UILOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_UILOG_CLEAR_CACHED_OBJECTIVE();
}

std::string ModAPI::Screen::GetFontString(std::string text, eFont font)
{
    std::string fontName = "";
    switch (font)
    {
    case eFont::FONT_STYLE_BODY:
        fontName = "$body";
        break;
    case eFont::FONT_STYLE_BODY_1:
        fontName = "$body1";
        break;
    case eFont::FONT_STYLE_BODY_2:
        fontName = "$body2";
        break;
    case eFont::FONT_STYLE_BODY_3:
        fontName = "$body3";
        break;
    case eFont::FONT_STYLE_FIXED_WIDTH_NUMBERS:
        fontName = "$FixedWidthNumbers";
        break;
    case eFont::FONT_STYLE_STANDARD:
        fontName = "$Font2";
        break;
    case eFont::FONT_STYLE_STANDARD_NOT_GAMERNAME:
        fontName = "$Font2_cond_NOT_GAMERNAME";
        break;
    case eFont::FONT_STYLE_CURSIVE:
        fontName = "$Font5";
        break;
    case eFont::FONT_STYLE_CONDENSED_NOT_GAMERNAME:
        fontName = "$gamername";
        break;
    case eFont::FONT_STYLE_PRICEDOWN:
        fontName = "$gtaCash";
        break;
    case eFont::FONT_STYLE_HANDWRITTEN:
        fontName = "$handwritten";
        break;
    case eFont::FONT_STYLE_ROCKSTAR_TAG:
        fontName = "$RockstarTAG";
        break;
    case eFont::FONT_STYLE_SOCIAL_CLUB_REG:
        fontName = "$SOCIAL_CLUB_COND_REG";
        break;
    case eFont::FONT_STYLE_SOCIAL_CLUB_BOLD:
        fontName = "$SOCIAL_CLUB_COND_BOLD";
        break;
    case eFont::FONT_STYLE_TITLE:
        fontName = "$title";
        break;
    case eFont::FONT_STYLE_TITLE_1:
        fontName = "$title1";
        break;
    case eFont::FONT_STYLE_TITLE_2:
        fontName = "$title2";
        break;
    case eFont::FONT_STYLE_UTIL:
        fontName = "$util";
        break;
    case eFont::FONT_STYLE_CATALOG_1:
        fontName = "$catalog1";
        break;
    case eFont::FONT_STYLE_CATALOG_2:
        fontName = "$catalog2";
        break;
    case eFont::FONT_STYLE_CATALOG_3:
        fontName = "$catalog3";
        break;
    case eFont::FONT_STYLE_CATALOG_4:
        fontName = "$catalog4";
        break;
    case eFont::FONT_STYLE_CATALOG_5:
        fontName = "$catalog5";
        break;
    case eFont::FONT_STYLE_WANTED:
        fontName = "$wantedPostersGeneric";
        break;
    case eFont::FONT_STYLE_LEDGER:
        fontName = "$ledger";
        break;
    case eFont::FONT_STYLE_CONDENSED:
        fontName = "$Debug_REG";
        break;
    case eFont::FONT_STYLE_CON_BOLD:
        fontName = "$Debug_BOLD";
        break;
    case eFont::FONT_STYLE_CHALK_HAND:
        fontName = "$chalk";
        break;
    case eFont::FONT_STYLE_LIMITED:
        fontName = "$Font5_limited";
        break;
    case eFont::FONT_STYLE_CREDITNAMES:
        fontName = "$creditNames";
        break;
    default:
        // TODO: Log error
        //Game.Console.Print($"Font '{font.ToString()}' is not handled.");
        break;
    }

    return "<font face=\"" + fontName + "\">" + text + "</font>";
}
