#include "pch.h"
#include "GameObjectManager.h"
#include "GameObjectStorage.h"
#include "AGameObject.h"

GameObjectManager& GameObjectManager::GetInstance()
{
    static GameObjectManager instance;
    return instance;
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::DestroyGameObject(AGameObject& gameObject)
{
    AGameObject* toDestroy = m_GameObjectStorage.Get(gameObject.GetName());
    if (toDestroy == nullptr)
    {
        return;
    }
    m_DestroyQueue.push(toDestroy);
    m_GameObjectStorage.Remove(toDestroy);
}

void GameObjectManager::DestroyGameObjectByName(const String& gameObjectName)
{
    AGameObject* toDestroy = m_GameObjectStorage.Get(gameObjectName);
    if (toDestroy == nullptr)
    {
        return;
    }
    m_DestroyQueue.push(toDestroy);
    m_GameObjectStorage.Remove(toDestroy);
}

void GameObjectManager::DestroyAllGameObjects()
{
    auto& gameObjectList = m_GameObjectStorage.GetAll();

    for (int i = 0; i < gameObjectList.size(); i++)
    {
        m_DestroyQueue.push(gameObjectList[i]);
    }

    m_GameObjectStorage.Clear();
}

AGameObject& GameObjectManager::FindObjectByName(const String& name)
{
    AGameObject* gameObject = m_GameObjectStorage.Get(name);

    ASSERT(gameObject != nullptr,
            "Cannot find GameObject {0}!", name);
    
    return *gameObject;
}

void GameObjectManager::InitializeGameObjects()
{
    while (!m_InitializationQueue.empty())
    {
        m_InitializationQueue.front()->OnInitialize();
        m_InitializationQueue.pop();
    }
}

void GameObjectManager::ProcessGameObjectsInput(const sf::Event& event) const
{
    auto& gameObjectList = m_GameObjectStorage.GetAll();

    for (int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->ProcessInput(event);
    }
}

void GameObjectManager::UpdateGameObjects(const float deltaTime) const
{
    auto& gameObjectList = m_GameObjectStorage.GetAll();

    for (int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->Update(deltaTime);
    }
}

void GameObjectManager::DrawGameObjects(sf::RenderWindow& window) const
{
    auto& gameObjectList = m_GameObjectStorage.GetAll();

    for (int i = 0; i < gameObjectList.size(); i++)
    {
        gameObjectList[i]->Draw(window, sf::RenderStates::Default);
    }
}

void GameObjectManager::DestroyGameObjects()
{
    while (!m_DestroyQueue.empty())
    {
        auto* gameObject = m_DestroyQueue.front();
        gameObject->OnDestroy();
        delete gameObject;
        m_DestroyQueue.pop();
    }
}

GameObjectManager::GameObjectManager()
{
}