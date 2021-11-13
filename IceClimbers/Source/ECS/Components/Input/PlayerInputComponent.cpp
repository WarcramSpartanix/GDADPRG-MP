#include "pch.h"
#include "PlayerInputComponent.h"

#include "ECS/AGameObject.h"
#include "ViewManager.h"
#include "ECS/Components/Script/Collider/PlayerColliderComponent.h"
#include "ECS/Components/Script/SpriteAnimatorComponent.h"

PlayerInputComponent::PlayerInputComponent(AGameObject& owner) :
	AInputComponent(owner)
{
}

void PlayerInputComponent::ProcessInput(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:	
		
		if (event.key.code == sf::Keyboard::A)
		{
			if (m_MoveRight)
			{
				GetOwner().GetComponent<PlayerMovementComponent>().StopVelocityX();
			}
			
			if (!m_MoveLeft &&
				!GetOwner().GetComponent<PlayerMovementComponent>().m_Falling)
			{
				auto& spriteAnim = GetOwner().GetComponent<SpriteAnimatorComponent>();
				spriteAnim.UpdateStartAndEndFrame({1, 0}, {3, 0}, true);
				GetOwner().GetComponent<TransformComponent>().SetScale(1.0f, 1.0f);
			}

			m_MoveLeft = true;
			m_MoveRight = false;
			
			m_Direction = -1;
			GetOwner().GetComponent<PlayerColliderComponent>().NotInvincible();
		}
		if (event.key.code == sf::Keyboard::D)
		{
			if (m_MoveLeft)
			{
				GetOwner().GetComponent<PlayerMovementComponent>().StopVelocityX();
			}
			
			if (!m_MoveRight &&
				!GetOwner().GetComponent<PlayerMovementComponent>().m_Falling)
			{
				auto& spriteAnim = GetOwner().GetComponent<SpriteAnimatorComponent>();
				spriteAnim.UpdateStartAndEndFrame({1, 0}, {3, 0}, true);
				GetOwner().GetComponent<TransformComponent>().SetScale(-1.0f, 1.0f);
			}
			m_MoveLeft = false;
			m_MoveRight = true;

			m_Direction = 1;
			GetOwner().GetComponent<PlayerColliderComponent>().NotInvincible();
		}
		if (event.key.code == sf::Keyboard::W)
		{
			if (!GetOwner().GetComponent<PlayerMovementComponent>().m_Falling)
			{
				GetOwner().GetComponent<PlayerMovementComponent>().m_Jump = true;
				m_JumpTriggered = true;
			}
			GetOwner().GetComponent<PlayerColliderComponent>().NotInvincible();
		}
		if (event.key.code == sf::Keyboard::Space)
		{
			m_AttackTriggered = true;
			m_HammerActive = true;

			auto& spriteAnim = GetOwner().GetComponent<SpriteAnimatorComponent>();
			
			spriteAnim.UpdateStartAndEndFrame({5, 0}, {9, 0}, false);
			
			GetOwner().GetComponent<PlayerColliderComponent>().NotInvincible();
		}
		break;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::A)
		{
			if (m_MoveLeft)
			{
				GetOwner().GetComponent<PlayerMovementComponent>().StopVelocityX();
				m_MoveLeft = false;
				auto& spriteAnim = GetOwner().GetComponent<SpriteAnimatorComponent>();
				spriteAnim.UpdateStartAndEndFrame({0, 0}, {0, 0}, true);
			}
		}
		if (event.key.code == sf::Keyboard::D)
		{
			if (m_MoveRight)
			{
				GetOwner().GetComponent<PlayerMovementComponent>().StopVelocityX();
				m_MoveRight = false;
				auto& spriteAnim = GetOwner().GetComponent<SpriteAnimatorComponent>();
				spriteAnim.UpdateStartAndEndFrame({0, 0}, {0, 0}, true);
			}
		}
		if (event.key.code == sf::Keyboard::Space)
		{
			m_AttackTriggered = false;
			m_HammerActive = false;
		}
		break;
	default:
		break;
	}
}

int* PlayerInputComponent::GetDirectionPointer()
{
	return &m_Direction;
}

bool* PlayerInputComponent::GetHammerActivePointer()
{
	return &m_HammerActive;
}

bool PlayerInputComponent::IsMoveRight() const
{
	return m_MoveRight;
}

bool PlayerInputComponent::IsMoveLeft() const
{
	return m_MoveLeft;
}

bool PlayerInputComponent::IsJumpTriggered() const
{
	return m_JumpTriggered;
}

bool PlayerInputComponent::IsAttackTriggered() const
{
	return m_AttackTriggered;
	
}
