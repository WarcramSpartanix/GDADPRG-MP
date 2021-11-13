#include "pch.h"
#include "Font.h"
#include "Core/Debug.h"

Font::Font(const String& name,
           const String& filepath) :
	Asset(name, filepath)
{
	m_Data = new sf::Font();
	m_Data->loadFromFile(filepath);

	ASSERT(m_Data != nullptr,
               "{0} file: {2}({3}) cannot be loaded!",
               GetType(), name, filepath)

	Debug::Log("{0}({1}) has been loaded!", m_Name, GetType());
}

Font::~Font()
{
	if (m_Data != nullptr)
	{
		delete m_Data;
		m_Data = nullptr;
	}

	Debug::Log("{0}({1}) has been unloaded!", m_Name, GetType());
}

sf::Font& Font::GetData() const
{
	return *m_Data;
}
