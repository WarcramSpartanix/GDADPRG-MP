#pragma once
#include "ResourceSystem/Music/Music.h"
#include "ResourceSystem/Sound/Sound.h"

class SoundManager
{
public:
	static SoundManager& GetInstance();

	void PlayMusic(String musicName);
	void StopMusic(String musicName);
	void PauseMusic(String musicName);
	
	void PlaySound(String soundName);
	void StopSound(String soundName);
	void PauseSound(String soundName);

private:
	SoundManager();
	~SoundManager();

	HashTable<String, Music*> m_MusicMap;
	HashTable<String, Sound*> m_SoundMap;
};

