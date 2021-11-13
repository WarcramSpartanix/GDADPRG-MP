#include "pch.h"
#include "AComponent.h"
#include "AGameObject.h"

AComponent::AComponent(AGameObject& owner) :
    m_Owner(owner)
{
}

AComponent::~AComponent()
{
    // Unbind the component
}

AGameObject& AComponent::GetOwner() const
{
    return m_Owner;
}

bool AComponent::operator==(const AComponent& other) const
{
    return  GetName() == other.GetName() &&
            GetType() == other.GetType() &&
            m_Owner.GetName() == other.m_Owner.GetName();
}

bool AComponent::operator!=(const AComponent& other) const
{
    return  GetName() != other.GetName() ||
            GetType() != other.GetType() ||
            m_Owner.GetName() != other.m_Owner.GetName();
}