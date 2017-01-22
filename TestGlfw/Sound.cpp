#include "Sound.h"
#include <cassert>


Sound::Sound(const std::string& path)
	:Path(path)
{
}

void Sound::Play()
{
	assert(m_Engine);
	m_SoundInstance = m_Engine->play2D(m_Sound, Loop, false, true);
}

void Sound::Stop()
{
	assert(m_Engine);
	
	if (!m_SoundInstance)
		return;

	m_SoundInstance->stop();
	m_SoundInstance->drop();
}

bool Sound::IsPlaying()
{
	if (!m_SoundInstance)
		return false;

	return !m_SoundInstance->isFinished();
}
