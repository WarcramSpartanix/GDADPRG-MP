#include "pch.h"
#include "Music.h"
#include "Core/Debug.h"

Music::Music(const String& name,
             const String& filepath) :
	Asset(name, filepath)
{
	m_Data = new sf::Music();
	m_Data->openFromFile(filepath);
	
	ASSERT(m_Data != nullptr,
               "{0} file: {2}({3}) cannot be loaded!",
               GetType(), name, filepath)
	
    Debug::Log("{0}({1}) has been loaded!", m_Name, GetType());
}

Music::~Music()
{
	Stop();
	if (m_Data != nullptr)
	{
		delete m_Data;
		m_Data = nullptr;
	}
	
	Debug::Log("{0}({1}) has been unloaded!", m_Name, GetType());
}

void Music::Play() const
{
	if (m_Data->getStatus() != sf::Music::Playing)
		m_Data->play();
}

void Music::Pause() const
{
	if (m_Data->getStatus() == sf::Music::Playing)
		m_Data->pause();
}

void Music::Stop() const
{
	if (m_Data->getStatus() == sf::Music::Playing || m_Data->getStatus() == sf::Music::Paused)
		m_Data->stop();
}

void Music::SetVolume(const float volume) const
{
	m_Data->setVolume(volume);
}

void Music::EnableLooping(const bool flag) const
{
	m_Data->setLoop(flag);
}
