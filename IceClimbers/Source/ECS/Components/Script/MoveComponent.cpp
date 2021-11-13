#include "pch.h"
#include "MoveComponent.h"

#include "ECS/AGameObject.h"

MoveComponent::MoveComponent(AGameObject& owner) :
	AScriptComponent{owner},
	m_TransformComponent{GetOwner().GetComponent<TransformComponent>()},
	m_VelocityComponent{GetOwner().GetComponent<VelocityComponent>()}
{
}

void MoveComponent::Update(const float deltaTime)
{
	sf::Vector2f velocity = m_VelocityComponent.GetVelocity();
	velocity.x *= deltaTime;
	velocity.y *= deltaTime;
	m_TransformComponent.Move(velocity.x, velocity.y);
}
