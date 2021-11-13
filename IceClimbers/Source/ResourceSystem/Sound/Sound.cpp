#include "pch.h"
#include "Sound.h"
#include "Core/Debug.h"

Sound::Sound(const String& name,
             const String& filepath) :
	Asset(name, filepath)
{
	m_BufferData = new sf::SoundBuffer();
	m_BufferData->loadFromFile(filepath);
	
	m_SoundData = new sf::Sound(*m_BufferData);
	
	ASSERT(m_BufferData != nullptr,
               "{0} file: {2}({3}) cannot be loaded!",
               GetType(), name, filepath)
	
	Debug::Log("{0}({1}) has been loaded!", m_Name, GetType());
}

Sound::~Sound()
{
	Stop();
	
	if (m_SoundData != nullptr)
	{
		delete m_SoundData;
		m_SoundData = nullptr;
	}
	
	if (m_BufferData != nullptr)
	{
		delete m_BufferData;
		m_BufferData = nullptr;
	}
	
	Debug::Log("{0}({1}) has been unloaded!", m_Name, GetType());
}

void Sound::Play() const
{
	if (m_SoundData->getStatus() != sf::Sound::Playing)
		m_SoundData->play();
}

void Sound::Pause() const
{
	if (m_SoundData->getStatus() == sf::Sound::Playing)
		m_SoundData->pause();
}

void Sound::Stop() const
{
	if (m_SoundData->getStatus() == sf::Sound::Playing || m_SoundData->getStatus() == sf::Sound::Paused)
		m_SoundData->stop();
}

void Sound::SetVolume(const float volume) const
{
	m_SoundData->setVolume(volume);
}
