#include "pch.h"
#include "IceCubeColliderComponent.h"
#include "CollisionManager.h"
#include "ECS/GameObjects/TileObject.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Texture/TextureAssets.h"
#include "ECS/Components/Script/TopiBehaviorComponent.h"

float IceCubeColliderComponent::ICE_CUBE_WIDTH = 25;
float IceCubeColliderComponent::ICE_CUBE_HEIGHT = 30;

IceCubeColliderComponent::IceCubeColliderComponent(AGameObject& owner, int direction) :
    BoxColliderComponent(owner, ICE_CUBE_WIDTH, ICE_CUBE_HEIGHT, false, ColliderLayer::Enemy, 0, 0)
{
	m_Direction = direction;
}

void IceCubeColliderComponent::Update(float deltaTime)
{
	if (!CheckBelow(deltaTime * 600.0f))
	{
		int heightLevel = m_LastTile->GetHeightLevel();
		Texture* texture;
		if (heightLevel < 3)
			texture = &ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::GREEN_TILE);
		else if(heightLevel < 6)
			texture = &ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::BROWN_TILE);
		else
			texture = &ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::BLUE_TILE);

		sf::FloatRect rect = GetBounds();
		rect.top += deltaTime * 600.0f;

		sf::Vector2f tilePos = m_LastTile->GetComponent<TransformComponent>().GetPosition();

		if (!CheckNextTile(rect));
		{
			TileObject* tile2 = CreateTile(tilePos.x + m_Direction * 30.0f * 2, tilePos.y, texture);
			Debug::Log("Create 2nd Tile at {0}, {1}", tilePos.x + m_Direction * 30.0f * 2, tilePos.y);
		}

		TileObject* tile1 = CreateTile(tilePos.x + m_Direction * 30.0f, tilePos.y, texture);
		Debug::Log("Create 1st Tile at {0}, {1}", tilePos.x + m_Direction * 30.0f, tilePos.y);

		m_TopiParent->GetComponent<TopiBehaviorComponent>().IceCubeUsed();

		DisableCollider();
		GameObjectManager::GetInstance().DestroyGameObject(GetOwner());
	}
}

void IceCubeColliderComponent::OnCollision(BoxColliderComponent* collider)
{
}

bool IceCubeColliderComponent::CheckBelow(float distance)
{
	List<BoxColliderComponent*> colliderList = CollisionManager::GetInstance().GetAllColliders();

	sf::FloatRect rect = GetBounds();
	rect.top += distance;

	for (int i = 0; i < colliderList.size(); i++)
	{
		if (colliderList[i]->m_Layer == ColliderLayer::Tile)
		{
			if (rect.intersects(colliderList[i]->GetBounds()))
			{
				m_LastTile = (TileObject*)&colliderList[i]->GetOwner();
				return true;
			}
		}
	}
	return false;
}

bool IceCubeColliderComponent::CheckNextTile(sf::FloatRect rect)
{
	List<BoxColliderComponent*> colliderList = CollisionManager::GetInstance().GetAllColliders();

	rect.left += 30.0f * m_Direction;

	for (int i = 0; i < colliderList.size(); i++)
	{
		if (colliderList[i]->m_Layer == ColliderLayer::Tile)
		{
			if (rect.intersects(colliderList[i]->GetBounds()))
			{
				return true;
			}
		}
	}
	return false;
}

TileObject* IceCubeColliderComponent::CreateTile(float x, float y, Texture* texture)
{
	static int id = 0;

	TileObject* tileObj = &GameObjectManager::GetInstance().CreateGameObject<TileObject>
		("IceGenerateTile" + std::to_string(id), *texture, x, y, true, m_LastTile->GetHeightLevel());

	id++;
	return tileObj;
}

void IceCubeColliderComponent::SetTopiParent(TopiObject* topiParent)
{
	m_TopiParent = topiParent;
}
