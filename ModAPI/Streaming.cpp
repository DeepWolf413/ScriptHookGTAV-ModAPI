#include "Streaming.h"

#include <natives.h>

namespace ModAPI
{
	void Streaming::RequestTextureDict(const std::string& category)
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(category.c_str(), 0);
	}

	void Streaming::MarkTextureDictAsNoLongerNeeded(const std::string& category)
	{ GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category.c_str()); }

	bool Streaming::TryRequestTextureDict(const std::string& category, const int timeoutMs)
	{
		int ticks = 0;
		while (!HasTextureDictLoaded(category))
		{
			RequestTextureDict(category);
			WAIT(1);
			ticks++;

			if (ticks >= timeoutMs)
			{ return false; }
		}

		return true;
	}

	bool Streaming::HasTextureDictLoaded(const std::string& category)
	{ return GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(category.c_str()); }
}
