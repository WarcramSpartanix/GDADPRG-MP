#include "pch.h"
#include "PlayerMovementComponent.h"
#include "EventSystem/EventBroadcaster.h"
#include "ECS/AGameObject.h"
#include "Game.h"
#include "ECS/Components/Script/Collider/PlayerColliderComponent.h"
#include "ECS/Components/Input/PlayerInputComponent.h"


PlayerMovementComponent::PlayerMovementComponent(AGameObject& owner) : 
	AScriptComponent(owner),
	m_TransformComponent(GetOwner().GetComponent<TransformComponent>()),
	m_InputComponent{GetOwner().GetComponent<PlayerInputComponent>()}
{
}

void PlayerMovementComponent::Update(float deltaTime)
{
	ApplyBooleans(deltaTime);
	ApplyGravity(deltaTime);
	ApplyVelocity(deltaTime);
}

void PlayerMovementComponent::ApplyBooleans(float deltaTime)
{
	if (m_InputComponent.IsAttackTriggered())
	{
		// attack and cannot move
		StopVelocityX();
	}
	else
	{
		if (m_Jump && !m_Falling)
		{
			m_Velocity.y = m_JUMP_VELOCITY;
			m_Jump = false;
			m_Falling = true;
		}
		
		if (m_InputComponent.IsMoveLeft())
		{
			if (!m_Falling)
				m_Velocity.x -= m_ACCELERATION * deltaTime;
			else
				m_Velocity.x -= m_ACCELERATION_JUMP * deltaTime;
			
			if (abs(m_Velocity.x) > m_MAX_X_VELOCITY)
				m_Velocity.x = -m_MAX_X_VELOCITY;
		}
		else if (m_InputComponent.IsMoveRight())
		{
			if (!m_Falling)
				m_Velocity.x += m_ACCELERATION * deltaTime;
			else
				m_Velocity.x += m_ACCELERATION_JUMP * deltaTime;
			
			if (abs(m_Velocity.x) > m_MAX_X_VELOCITY)
				m_Velocity.x = m_MAX_X_VELOCITY;
		}
		
	}
}

void PlayerMovementComponent::ApplyGravity(float deltaTime)
{
	if (!GetOwner().GetComponent<PlayerColliderComponent>().CheckBelow(m_GRAVITY * deltaTime) || m_Velocity.y < 0.0f)
	{
		if (m_Velocity.y > 0.0f)
			m_Velocity.x = m_START_X_VELOCITY_FALL * m_Velocity.x < 0 ? -1 : 1;
		else if (abs(m_Velocity.x) > m_MAX_X_VELOCITY_JUMP)
			m_Velocity.x = m_MAX_X_VELOCITY_JUMP * m_Velocity.x < 0 ? -1 : 1;
	
		m_Velocity.y += m_GRAVITY * deltaTime;
		m_Falling = true;
	}
	else
	{
		if (m_Velocity.y > 0.0f)
			m_Velocity.y = 0.0f;
		m_Falling = false;
	}
}

void PlayerMovementComponent::ApplyVelocity(float deltaTime)
{
	sf::Vector2f pos = m_TransformComponent.GetPosition();
	m_TransformComponent.Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);
}

void PlayerMovementComponent::StopVelocityX()
{
	m_Velocity.x = 0;
}

void PlayerMovementComponent::StopVelocityY()
{
	m_Velocity.y = 0;
}

bool PlayerMovementComponent::MovingUpwards()
{
	if(m_Velocity.y < 0.0f)
		return true;
	return false;
}
