#pragma once

#include <map>

#include <irrKlang.h>
#include <string>

#include "Sound.h"
#include <memory>

class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();
	void Init();
	Sound* LoadSound(const std::string& path);

	irrklang::ISoundEngine* m_SoundEngine;

private:
	std::map<std::string, std::unique_ptr<Sound>> m_Sounds;
};

