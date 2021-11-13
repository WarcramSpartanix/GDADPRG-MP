#include "pch.h"
#include "AGameObject.h"

#include "Components/Input/AInputComponent.h"
#include "Components/Render/ARenderComponent.h"
#include "Components/Script/AScriptComponent.h"

AGameObject::AGameObject(const String& name) :
    m_Name(name),
    m_IsEnabled(true)
{
}

AGameObject::~AGameObject()
{
}

void AGameObject::Enable()
{
    m_IsEnabled = true;
}

void AGameObject::Disable()
{
    m_IsEnabled = false;
}

bool AGameObject::IsEnabled() const
{
    return m_IsEnabled;
}

const String& AGameObject::GetName() const
{
    return m_Name;
}

void AGameObject::ProcessInput(const sf::Event& event)
{
    if (!m_IsEnabled)
    {
        return;
    }
    
    auto& inputComponentList = m_ComponentStorage.GetListOfType(ComponentType::INPUT);
    for (auto* inputComponent : inputComponentList)
    {
        static_cast<AInputComponent*>(inputComponent)->ProcessInput(event);
    }
}

void AGameObject::Update(const float deltaTime)
{
    if (!m_IsEnabled)
    {
        return;
    }
    
    auto& scriptComponentList = m_ComponentStorage.GetListOfType(ComponentType::SCRIPT);
    for (auto* scriptComponent : scriptComponentList)
    {
        static_cast<AScriptComponent*>(scriptComponent)->Update(deltaTime);
    }
}

void AGameObject::Draw(sf::RenderWindow& window,
                       sf::RenderStates states)
{
    if (!m_IsEnabled)
    {
        return;
    }
    
    auto& renderComponentList = m_ComponentStorage.GetListOfType(ComponentType::RENDER);
    for (auto* renderComponent : renderComponentList)
    {
        static_cast<ARenderComponent*>(renderComponent)->Draw(window, states);
    }
}

void AGameObject::AddChild(AGameObject& child)
{
    m_ChildStorage.Add(&child);
    child.SetParent(this);
}

AGameObject* AGameObject::FindChildByName(const String& childName)
{
    return m_ChildStorage.Get(childName);
}

void AGameObject::RemoveChild(AGameObject* child)
{
    ASSERT(child != nullptr,
                 "Attempting to remove a null GameObject child!");
    
    m_ChildStorage.Remove(child);
}

AGameObject* AGameObject::GetParent() const
{
    return m_Parent;
}

void AGameObject::SetParent(AGameObject* parent)
{
    if (m_Parent == nullptr && parent != nullptr ||
        m_Parent != nullptr && parent == nullptr)
    {
        m_Parent = parent; 
    }
}