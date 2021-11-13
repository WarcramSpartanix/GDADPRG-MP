#include "pch.h"
#include "PlayerGroundHammerComponent.h"
#include "ECS/Components/Script/Collider/PlayerColliderComponent.h"
#include "ECS/Components/Input/PlayerInputComponent.h"
#include "ECS/AGameObject.h"
#include "CollisionManager.h"
#include "ECS/GameObjects/TopiObject.h"

float PlayerGroundHammerComponent::BOX_HEIGHT = 60;
float PlayerGroundHammerComponent::BOX_WIDTH = 30;

PlayerGroundHammerComponent::PlayerGroundHammerComponent(AGameObject& owner) : 
	BoxColliderComponent(owner, BOX_WIDTH, BOX_HEIGHT, false, ColliderLayer::Player, PlayerColliderComponent::PLAYER_WIDTH/2 + BOX_WIDTH/2, 0.0f)
{
	m_Direction = owner.GetComponent<PlayerInputComponent>().GetDirectionPointer();
	m_Active = owner.GetComponent<PlayerInputComponent>().GetHammerActivePointer();
}

void PlayerGroundHammerComponent::Update(float deltaTime)
{
	List<BoxColliderComponent*> colliderList = CollisionManager::GetInstance().GetAllColliders();

	if (*m_Active)
	{
		for (int i = 0; i < colliderList.size(); i++)
		{
			if (colliderList[i]->m_Layer == ColliderLayer::Enemy)
			{
				if (CheckCollision(colliderList[i]))
				{
					OnCollision(colliderList[i]);
				}
			}
		}
	}
}

void PlayerGroundHammerComponent::OnCollision(BoxColliderComponent* collider)
{
	if (collider->m_Layer == ColliderLayer::Enemy)
	{
		// kill enemy
		Debug::Log("Player Murdered Topi With Hammer");
		((TopiObject&)collider->GetOwner()).Kill();
	}
	// else if (collider->m_Layer == ColliderLayer::IceCube)
	// {
	// 	collider->DisableCollider();
	// 	GameObjectManager::GetInstance().DestroyGameObject(collider->GetOwner());
	// }
}

sf::FloatRect PlayerGroundHammerComponent::GetBounds()
{
	sf::Vector2f pos = m_Tranform->GetPosition();
	sf::FloatRect rect(pos.x - m_Width / 2 + m_OffsetX * (*m_Direction), pos.y - m_Height / 2 + m_OffsetY, m_Width, m_Height);
	return rect;
}
