#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameObjectStorage.h"
class AGameObject;

#include "Core/TypeAlias.h"
class GameObjectManager final
{
public:
    GameObjectManager(const GameObjectManager& other) = delete;
    GameObjectManager(GameObjectManager&& other) noexcept = delete;
    GameObjectManager& operator=(const GameObjectManager& other) = delete;
    GameObjectManager& operator=(GameObjectManager&& other) noexcept = delete;
    
    static GameObjectManager& GetInstance();
    ~GameObjectManager();

    template <class T, typename ...Args>
    T& CreateGameObject(Args&& ...args);

    void DestroyGameObject(AGameObject& gameObject);
    void DestroyGameObjectByName(const String& gameObjectName);
    void DestroyAllGameObjects();

    AGameObject& FindObjectByName(const String& name);
    
    void InitializeGameObjects();
    void ProcessGameObjectsInput(const sf::Event& event) const;
    void UpdateGameObjects(float deltaTime) const;
    void DrawGameObjects(sf::RenderWindow& window) const;
    void DestroyGameObjects();

private:
    GameObjectManager();

    Queue<AGameObject*> m_InitializationQueue;
    Queue<AGameObject*> m_DestroyQueue;
    
    GameObjectStorage m_GameObjectStorage;
};

template <class T, typename ... Args>
T& GameObjectManager::CreateGameObject(Args&&... args)
{
    T* object = new T(std::forward<Args>(args) ...);
    m_GameObjectStorage.Add(object);
    m_InitializationQueue.push(object);
    return *object;
}