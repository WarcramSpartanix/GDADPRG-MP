#include "pch.h"
#include "AGameObject.h"

GameObjectStorage::GameObjectStorage()
{
}

GameObjectStorage::~GameObjectStorage()
{
	Clear();
}

void GameObjectStorage::Add(AGameObject* gameObject)
{
	ASSERT(gameObject != nullptr,
            "Cannot add a null GameObject in storage!")
	
	const bool isObjectInStorage = IsInStorage(gameObject);
	
	ASSERT(!isObjectInStorage,
		"{0} has already been added!",
		gameObject->GetName())

	m_GameObjectList.emplace_back(gameObject);
	m_GameObjectTable[gameObject->GetName()] = gameObject;
}

void GameObjectStorage::Remove(AGameObject* gameObject)
{
	ASSERT(gameObject != nullptr,
            "Cannot remove a null GameObject in storage!")

	const bool isObjectInStorage = IsInStorage(gameObject);
	
	ASSERT(isObjectInStorage,
        "{0} has already been added!",
                 gameObject->GetName())

	AGameObject* foundGameObject = nullptr;
	int index = -1;
	for (size_t i = 0; i < m_GameObjectList.size(); i++)
	{
		if (gameObject->GetName() == m_GameObjectList[i]->GetName())
		{
			foundGameObject = m_GameObjectList[i];
			index = i;
		}
	}

	if (index != -1)
	{
		const auto name = foundGameObject->GetName();
		m_GameObjectList.erase(m_GameObjectList.begin() + index);
		m_GameObjectList.shrink_to_fit();
		m_GameObjectTable.erase(name);
	}
}

AGameObject* GameObjectStorage::Get(const String& name)
{
	auto* foundObject = m_GameObjectTable[name];
	Debug::Warn("Attempting to retrieve a game object {0} that doesn't exist in storage.", name);
	return foundObject;
}

bool GameObjectStorage::IsInStorage(AGameObject* gameObject)
{
	ASSERT(gameObject != nullptr,
			"Cannot find a null GameObject in storage!")
	auto* foundGameObject = m_GameObjectTable[gameObject->GetName()];
	return foundGameObject != nullptr;
}

bool GameObjectStorage::IsInStorageByName(const String& name)
{
    AGameObject* foundGameObject = Get(name);
	return foundGameObject != nullptr;
}

void GameObjectStorage::Clear()
{
	m_GameObjectList.clear();
	m_GameObjectList.shrink_to_fit();
	m_GameObjectTable.clear();
}

const List<AGameObject*>& GameObjectStorage::GetAll() const
{
	return m_GameObjectList;
}
