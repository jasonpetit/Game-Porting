#pragma once

#include "SDLHeaders.h"
#include <string>

class Audio
{
public:
	Audio();
	~Audio();

	// See if we loaded up ok
	bool IsOpen() const;

	// Handle music
	bool LoadMusic(const std::string &fileName, const std::string &key);
	void PlayMusic(const std::string &musName, bool loop = true);
	void PauseMusic();
	void UnPauseMusic();
	void RestartMusic();

	// Handle sound
	bool LoadSound(const std::string &fileName, const std::string &key);
	void PlaySound(const std::string &soundName, int channel = -1, int loopcount = 0);
	void StopAllSounds();

private:
	bool isOpen;

	std::map<std::string, Mix_Music *> m_songs;
	std::map<std::string, Mix_Chunk *> m_sounds;
};