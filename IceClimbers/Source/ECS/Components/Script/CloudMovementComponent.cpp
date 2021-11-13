#include "pch.h"
#include "CloudMovementComponent.h"
#include "ECS/AGameObject.h"
#include "Game.h"

CloudMovementComponent::CloudMovementComponent(AGameObject& owner, float speed) : AScriptComponent(owner),
m_Transform(GetOwner().GetComponent<TransformComponent>())
{
	m_Speed = speed;
}

void CloudMovementComponent::Update(float deltaTime)
{
	sf::Vector2f pos = m_Transform.GetPosition();
	m_MoveDistance = m_Speed * deltaTime;
	pos.x += m_MoveDistance;

	if (pos.x < 0)
		pos.x = Game::SCREEN_WIDTH;
	else if (pos.x > Game::SCREEN_WIDTH)
		pos.x = 0;

	m_Transform.SetPosition(pos.x, pos.y);
}

float CloudMovementComponent::GetLastMoveDistance()
{
	return m_MoveDistance;
}
