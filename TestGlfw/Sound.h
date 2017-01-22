#pragma once

#include <string>
#include <ik_ISoundSource.h>
#include <ik_ISoundEngine.h>

class Sound
{
	friend class SoundEngine;
public:
	Sound(const std::string& path);
	~Sound() = default;
	void Play();
	void Stop();
	bool IsPlaying();

	const std::string Path;
	bool Loop = false;
	bool IsPaused = false;

private:
	irrklang::ISoundSource* m_Sound;
	irrklang::ISound* m_SoundInstance;
	irrklang::ISoundEngine* m_Engine;
};

