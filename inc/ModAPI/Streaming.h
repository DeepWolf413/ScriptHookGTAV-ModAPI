#pragma once
#include <string>

namespace ModAPI::Streaming
{
	/**
	 * \brief Requests the specified texture dictionary. This function only attempts once,
	 * unlike the alternative TryRequestTextureDict.
	 * NOTE: Remember to mark the texture dictionary as no longer needed after you're done with it.
	 * \param category The name of the texture dictionary.
	 */
	void RequestTextureDict(const std::string& category);
	void MarkTextureDictAsNoLongerNeeded(const std::string& category);
	
	/**
	 * \brief Attempts to request the specified texture dictionary.
	 * Will timeout if it isn't able to request it within the specified timeout time.
	 * NOTE: Remember to mark the texture dictionary as no longer needed after you're done with it.
	 * \param category The name of the texture dictionary.
	 * \param timeoutMs How long it should try to request the texture dictionary (in milliseconds).
	 * \return True if the texture dictionary got successfully requested, otherwise it'll be false.
	 */
	[[nodiscard]] bool TryRequestTextureDict(const std::string& category, int timeoutMs = 5000);
	[[nodiscard]] bool HasTextureDictLoaded(const std::string& category);
}
