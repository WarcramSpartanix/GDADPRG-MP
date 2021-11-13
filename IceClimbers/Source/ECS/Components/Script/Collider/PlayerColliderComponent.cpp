#include "pch.h"
#include "PlayerColliderComponent.h"
#include "CollisionManager.h"
#include "ECS/AGameObject.h"
#include "ViewManager.h"
#include "ECS/GameObjects/CloudObject.h"
#include "EventSystem/EventBroadcaster.h"
#include "ECS/Components/Script/PlayerMovementComponent.h"
#include "ScoreManager.h"

#include "SceneSystem/SceneManager.h"
float PlayerColliderComponent::PLAYER_WIDTH = 24;
float PlayerColliderComponent::PLAYER_HEIGHT = 53;

PlayerColliderComponent::PlayerColliderComponent(AGameObject& owner) : 
	BoxColliderComponent(owner, PLAYER_WIDTH, PLAYER_HEIGHT, false, ColliderLayer::Player, 0, 0)
{
	m_MovementComponent = &GetOwner().GetComponent<PlayerMovementComponent>();

	EventBroadcaster::GetInstance().AddEventListener(EventNames::PLAYER_DIED, this);
	EventBroadcaster::GetInstance().AddEventListener(EventNames::PLAYER_RESPAWN, this);
}

void PlayerColliderComponent::Update(float deltaTime)
{
	List<BoxColliderComponent*> colliderList = CollisionManager::GetInstance().GetAllColliders();
	bool collided = false;
	for (int i = 0; i < colliderList.size(); i++)
	{
		if (colliderList[i]->m_Layer != ColliderLayer::Player)
		{
			if (CheckCollision(colliderList[i]))
			{
				if (colliderList[i]->m_Layer == ColliderLayer::Tile && !collided)
				{
					collided = true;
				}
				OnCollision(colliderList[i]);
			}
		}
		
	}
	if (!collided)
		m_IgnoreTiles = false;
	
	CheckPlayerCameraPosition();
}

void PlayerColliderComponent::OnCollision(BoxColliderComponent* collider)
{
	//Debug::Log("Collision with {0}", collider->GetOwner().GetName());
	sf::FloatRect rect1 = GetBounds();
	sf::FloatRect rect2 = collider->GetBounds();
	sf::Vector2f pos = m_Tranform->GetPosition();

	if (collider->m_Layer == ColliderLayer::Tile || collider->m_Layer == ColliderLayer::Cloud && !m_IgnoreTiles)
	{
		
		if (rect1.left < rect2.left || rect1.left + rect1.width > rect2.left + rect2.width)	// rect 1 is colliding from left or right
		{
			// nothing happens
			m_IgnoreTiles = true;
		}
		else if (rect1.top < rect2.top) // rect1 above rect 2
		{
			m_MovementComponent->StopVelocityY();
			m_MovementComponent->m_Falling = false;
			pos.y = rect2.top - rect1.height;
		}
		else
		{
			m_MovementComponent->StopVelocityY();
			pos.y = rect2.top + rect2.height + rect1.height/2;
		}

		m_Tranform->SetPosition(pos.x, pos.y);
	}
	else if (collider->m_Layer == ColliderLayer::Wall)
	{
		if (rect1.left < rect2.left)		// left
		{
			pos.x = rect2.left + rect1.width/2;
		}
		else if (rect1.left + rect1.width > rect2.left + rect2.width)		// right
		{
			pos.x = rect2.left + rect2.width + rect1.width/2;
		}
		else
		{
			m_MovementComponent->StopVelocityY();
			pos.y = rect2.top + rect2.height + rect1.height / 2;
		}

		m_Tranform->SetPosition(pos.x, pos.y);
	}
	else if (collider->m_Layer == ColliderLayer::Enemy || collider->m_Layer == ColliderLayer::IceCube && !m_Invincible)
	{
		// die
		sf::FloatRect viewRect = ViewManager::GetInstance().GetViewBounds(ViewNames::GAME_VIEW);
		EventBroadcaster::GetInstance().BroadcastEvent(EventNames::PLAYER_DIED);
	}
	else if (collider->m_Layer == ColliderLayer::Item)
	{
		//GameObjectManager::GetInstance().DestroyGameObject(collider->GetOwner());
		collider->GetOwner().Disable();
		ScoreManager::GetInstance().RegisterScore(RewardType::ITEM_GET,1);
	}
	else if (collider->m_Layer == ColliderLayer::Bird)
	{
		EventBroadcaster::GetInstance().BroadcastEvent(EventNames::LEVEL_FINISHED);
		SceneManager::GetInstance().LoadScene("ResultScene");
	}

}

bool PlayerColliderComponent::CheckBelow(float distance)	// return true if a collider is below
{
	if (m_IgnoreTiles || GetOwner().GetComponent<PlayerMovementComponent>().MovingUpwards())
		return false;

	List<BoxColliderComponent*> colliderList = CollisionManager::GetInstance().GetAllColliders();

	sf::FloatRect rect = GetBounds();
	rect.top += distance;

	for (int i = 0; i < colliderList.size(); i++)
	{
		if (colliderList[i]->m_Layer == ColliderLayer::Tile || colliderList[i]->m_Layer == ColliderLayer::Cloud)
		{
			if (rect.intersects(colliderList[i]->GetBounds()))
			{
				if (colliderList[i]->m_Layer == ColliderLayer::Tile)
				{
					m_HeightLevel = ((TileObject&)(colliderList[i]->GetOwner())).GetHeightLevel();
					m_LastTile = &((TileObject&)(colliderList[i]->GetOwner()));
				}
				else
				{
					CloudObject& cloudObj = (CloudObject&)(colliderList[i]->GetOwner());

					m_HeightLevel = (cloudObj).GetHeightLevel();
					m_Tranform->Move(cloudObj.GetLastMoveDistance() , 0.0f);
				}
				if (m_HeightLevel >= ViewManager::GetInstance().GetCameraFloorIndex())
				{
					EventBroadcaster::GetInstance().BroadcastEvent(EventNames::MOVE_NEXT_FLOOR);
				}
				return true;
			}
		}
	}

	return false;
}

void PlayerColliderComponent::CheckPlayerCameraPosition()
{
	sf::Vector2f pos = m_Tranform->GetPosition();
	sf::FloatRect playerRect = GetBounds();
	sf::FloatRect viewRect = ViewManager::GetInstance().GetViewBounds(ViewNames::GAME_VIEW);
	if (playerRect.left < viewRect.left)
		m_Tranform->SetPosition(viewRect.left + viewRect.width - playerRect.width, pos.y);
	else if (playerRect.left + playerRect.width > viewRect.left + viewRect.width)
		m_Tranform->SetPosition(viewRect.left + playerRect.width, pos.y);
	if (m_DeathByCamera)
	{
		if (!playerRect.intersects(viewRect))
		{
			// player dies
			EventBroadcaster::GetInstance().BroadcastEvent(EventNames::PLAYER_DIED);
			Debug::Log("Player Died by Camera");
		}
	}
}

void PlayerColliderComponent::NotInvincible()
{
	m_Invincible = false;
}

void PlayerColliderComponent::Respawn()
{
	sf::Vector2f pos = GetLastTile()->GetComponent<TransformComponent>().GetPosition();
	m_Tranform->SetPosition(pos.x, pos.y - TileObject::TILE_SIZE / 2 - PLAYER_HEIGHT / 2);

	sf::Vector2f tilePos = GetLastTile()->GetComponent<TransformComponent>().GetPosition();
	sf::Vector2f transPos = m_Tranform->GetPosition();
	m_Invincible = true;
}

void PlayerColliderComponent::ReceiveEvent(String eventName)
{
	if (eventName == EventNames::PLAYER_DIED)
	{
		// kill player
		EventBroadcaster::GetInstance().BroadcastEvent(EventNames::PLAYER_RESPAWN);		//temporary
	}
	else if (eventName == EventNames::PLAYER_RESPAWN)
	{
		Respawn();
	}
}

TileObject* PlayerColliderComponent::GetLastTile()
{
	return m_LastTile;
}
