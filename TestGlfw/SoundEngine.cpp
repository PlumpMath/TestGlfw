#include "SoundEngine.h"
#include <iostream>
#include <cassert>


SoundEngine::SoundEngine()
{
}

SoundEngine::~SoundEngine()
{
	if (m_SoundEngine)
		m_SoundEngine->drop();
}

void SoundEngine::Init()
{
	m_SoundEngine = irrklang::createIrrKlangDevice();
	if(m_SoundEngine == nullptr)
	{
		std::cerr << "Failed to initialize SoundEngine" << std::endl;
		__debugbreak();
	}
}

Sound* SoundEngine::LoadSound(const std::string& path)
{
	assert(m_SoundEngine);

	auto found = m_Sounds.find(path);
	if(found == m_Sounds.end())
	{
		auto sound = std::make_unique<Sound>(path);

		auto source = m_SoundEngine->addSoundSourceFromFile(path.c_str());
		if (!source)
		{
			std::cerr << "Failed to load sound: " << path << std::endl;
			__debugbreak();
		}

		sound->m_Sound = source;
		sound->m_Engine = m_SoundEngine;
		m_Sounds.insert({ path, std::move(sound) });
	}
	
	return m_Sounds[path].get();
}
