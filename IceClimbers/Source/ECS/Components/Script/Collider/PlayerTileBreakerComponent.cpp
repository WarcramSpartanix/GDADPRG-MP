#include "pch.h"
#include "PlayerTileBreakerComponent.h"
#include "ECS/AGameObject.h"
#include "CollisionManager.h"
#include "ECS/GameObjects/TileObject.h"
#include "ECS/Components/Script/Collider/PlayerColliderComponent.h"

float PlayerTileBreakerComponent::BOX_WIDTH = 4;
float PlayerTileBreakerComponent::BOX_HEIGHT = 5;

PlayerTileBreakerComponent::PlayerTileBreakerComponent(AGameObject& owner) :
	BoxColliderComponent(owner, BOX_WIDTH, BOX_HEIGHT, false, ColliderLayer::Player, 
		0.0f, -BOX_HEIGHT - PlayerColliderComponent::PLAYER_HEIGHT / 2)
{
	m_MovementComponent = &GetOwner().GetComponent<PlayerMovementComponent>();
}

void PlayerTileBreakerComponent::Update(float deltaTime)
{
	if (m_MovementComponent->MovingUpwards())
	{
		List<BoxColliderComponent*> colliderList = CollisionManager::GetInstance().GetAllColliders();

		for (int i = 0; i < colliderList.size(); i++)
		{
			if (colliderList[i]->m_Layer != ColliderLayer::Player)
			{
				if (CheckCollision(colliderList[i]))
				{
					OnCollision(colliderList[i]);
					if (m_HasDestroyed)
						break;
				}
			}
		}
	}
	m_HasDestroyed = false;
}

void PlayerTileBreakerComponent::OnCollision(BoxColliderComponent* collider)
{
	sf::FloatRect rect1 = GetBounds();
	sf::FloatRect rect2 = collider->GetBounds();
	sf::Vector2f pos = m_Tranform->GetPosition();
	//Debug::Log("Collision with {0}", collider->GetOwner().GetName());
	//if (rect1.left < rect2.width /2 || rect1.left + rect1.width /2> rect2.left + rect2.width)	// rect 1 is colliding from left or right
	//{
	//	// nothing happens
	//}
	if (collider->m_Layer == ColliderLayer::Tile)
	{
		TileObject& tileobj = (TileObject&)collider->GetOwner();
		if (tileobj.m_IsDestructible)
		{
			GameObjectManager::GetInstance().DestroyGameObject(collider->GetOwner());
			collider->DisableCollider();
			m_HasDestroyed = true;
		}
		m_MovementComponent->StopVelocityY();
		pos.y = rect2.top + rect2.height + PlayerColliderComponent::PLAYER_HEIGHT / 2;
	}

	m_Tranform->SetPosition(pos.x, pos.y);
}
