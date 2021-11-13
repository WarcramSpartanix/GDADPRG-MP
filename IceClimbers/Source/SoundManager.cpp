#include "pch.h"
#include "SoundManager.h"
#include "ResourceSystem/ResourceManager.h"

SoundManager& SoundManager::GetInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::PlayMusic(String musicName)
{
    if (m_MusicMap.find(musicName) != m_MusicMap.end())
    {
        m_MusicMap[musicName]->Play();
    }   
}

void SoundManager::StopMusic(String musicName)
{
    if (m_MusicMap.find(musicName) != m_MusicMap.end())
    {
        m_MusicMap[musicName]->Stop();
    }
}

void SoundManager::PauseMusic(String musicName)
{
    if (m_MusicMap.find(musicName) != m_MusicMap.end())
    {
        m_MusicMap[musicName]->Pause();
    }
}

void SoundManager::PlaySound(String soundName)
{
    if (m_SoundMap.find(soundName) != m_SoundMap.end())
    {
        m_SoundMap[soundName]->Play();
    }
}

void SoundManager::StopSound(String soundName)
{
    if (m_SoundMap.find(soundName) != m_SoundMap.end())
    {
        m_SoundMap[soundName]->Stop();
    }
}

void SoundManager::PauseSound(String soundName)
{
    if (m_SoundMap.find(soundName) != m_SoundMap.end())
    {
        m_SoundMap[soundName]->Pause();
    }
}

SoundManager::SoundManager()
{
    //TODO:: load all music and sounds files
    /*m_MusicMap.insert({ "bgm", new Music("bgm", "assets/BGM/bgm.ogg") });
    m_SoundMap.insert({ "AGura", new Sound("AGura", "assets/SFX/AGura.wav") });
    m_SoundMap.insert({ "Charge", new Sound("Charge", "assets/SFX/Charge.wav") });*/


    //Testing Purposes
    ResourceManager::GetInstance().Load<Music>("bgm", "assets/BGM/bgm.ogg");



    m_MusicMap["bgm"] = &ResourceManager::GetInstance().Acquire<Music>("bgm");
    /*m_SoundMap["AGura"] = &ResourceManager::GetInstance().Acquire<Sound>("AGura");
    m_SoundMap["Charge"] = &ResourceManager::GetInstance().Acquire<Sound>("Charge");*/
}

SoundManager::~SoundManager()
{
}
