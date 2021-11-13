#pragma once
#include "ComponentStorage.h"
#include "GameObjectManager.h"

#include "Core/TypeAlias.h"
#include "SFML/Graphics.hpp"

// TODO:
// Implement finding child and children

// Implement finding components

// Implement input, update, and render functions
// Case 2: Move the white rectangle using WASD
// Case 3: Change the color of the rectangle using space key
// Case 4: Create Parent -> Child -> Child's Child with an offset position and have different behavior:
//		Parent : No change
//		Child : Rotates
//		Child's Child: Changes color every 1 second

// Flow:
// Start Loop
// -> Initialize all uninitialized game objects and components
// -> process input
// -> update
// -> render
// -> Deactivate all destroyed / disabled game objects and components

class AGameObject
{
public:
    explicit AGameObject(const String& name);
    virtual ~AGameObject();

    virtual void OnInitialize() = 0;
    virtual void OnDestroy() = 0;

    void Enable();
    void Disable();
    bool IsEnabled() const;

    const String& GetName() const;

    void ProcessInput(const sf::Event& event);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window,
              sf::RenderStates states = sf::RenderStates::Default);

    template <class T, typename ...Args>
    T& AddComponent(Args&& ... args);
    
    template <class T>
    void RemoveComponent();

    template <class T>
    T& GetComponent();

    void AddChild(AGameObject& child);
    AGameObject* FindChildByName(const String& childName);  
    void RemoveChild(AGameObject* child);

    AGameObject* GetParent() const;
    void SetParent(AGameObject* parent);
    
private:
    String m_Name;
    bool m_IsEnabled;
    AGameObject* m_Parent = nullptr;
    GameObjectStorage m_ChildStorage;
    ComponentStorage m_ComponentStorage;
};

template <class T, typename ... Args>
T& AGameObject::AddComponent(Args&&... args)
{
    T* component = new T(*this, std::forward<Args>(args)...);
    m_ComponentStorage.Add(component);
    return *component;
}

template <class T>
void AGameObject::RemoveComponent()
{
    AComponent* component = m_ComponentStorage.Get(T::GetStaticType(), T::GetStaticName());
    if (component == nullptr)
    {
        Debug::Warn("{0} attempting to remove a non-existent {1}",
                    m_Name, T::GetStaticName());
        return;
    }
    m_ComponentStorage.Remove(T::GetStaticType(), T::GetStaticName());
    delete component;
}

template <class T>
T& AGameObject::GetComponent()
{
    AComponent* component = m_ComponentStorage.Get(T::GetStaticName());

    ASSERT(component != nullptr,
        "{0} does not have {1}!",
                m_Name, T::GetStaticName())
    
    return *static_cast<T*>(component);
}