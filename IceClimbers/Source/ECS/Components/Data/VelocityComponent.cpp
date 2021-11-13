#include "pch.h"
#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(AGameObject& owner,
									 const sf::Vector2f& initialVelocity) :
	AComponent{owner},
	m_VelocityVector{initialVelocity}
{
}

const sf::Vector2f& VelocityComponent::GetVelocity() const
{
	return m_VelocityVector;
}

void VelocityComponent::SetVelocity(const float x,
                                    const float y)
{
	m_VelocityVector.x = x;
	m_VelocityVector.y = y;
}
