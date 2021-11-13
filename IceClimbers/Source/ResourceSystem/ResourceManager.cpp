#include "pch.h"
#include "ResourceManager.h"
#include "Music/Music.h"

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;
}

ResourceManager::ResourceManager() :
	m_AssetStorage(HashTable<String, AssetTable>())
{
}

ResourceManager::~ResourceManager()
{
}

