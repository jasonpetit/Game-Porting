#include "Audio.h"
#include "SDLHeaders.h"

Audio::Audio()
{
	isOpen = (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 8, 4096) != -1);
}

Audio::~Audio()
{
	if(isOpen) Mix_CloseAudio();
}

bool Audio::IsOpen() const
{
	return isOpen;
}

bool Audio::LoadMusic(const std::string &fileName, const std::string &key)
{
	Mix_Music *mus = Mix_LoadMUS(fileName.c_str());

	if(mus == NULL)
		return false;

	m_songs[key] = mus;
	return true;
}

void Audio::PlayMusic(const std::string &musName, bool loop /*= true*/)
{
	if(Mix_PlayingMusic())
		Mix_HaltMusic();

	if(m_songs.find(musName) != m_songs.end())
		Mix_PlayMusic(m_songs[musName], (loop ? -1 : 0));
}

void Audio::PauseMusic()
{
	if(Mix_PlayingMusic())
		Mix_PauseMusic();
}

void Audio::UnPauseMusic()
{
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
}

void Audio::RestartMusic()
{
	if(Mix_PlayingMusic() || Mix_PausedMusic())
	{
		Mix_RewindMusic();
		Mix_ResumeMusic();
	}
}

bool Audio::LoadSound(const std::string &fileName, const std::string &key)
{
	Mix_Chunk *chunk = Mix_LoadWAV(fileName.c_str());

	if(chunk == NULL)
		return false;

	m_sounds[key] = chunk;
	return true;
}

void Audio::PlaySound(const std::string &soundName, int channel /*= -1*/, int loopcount /*= 0*/)
{
	if(m_sounds.find(soundName) != m_sounds.end())
	{
		Mix_PlayChannel(channel, m_sounds[soundName], loopcount);
	}
}

void Audio::StopAllSounds()
{
	//Mix_HaltChannel(-1);
	Mix_HaltGroup(-1);
}

