#include "pch.h"
#include "TopiColliderComponent.h"
#include "CollisionManager.h"

float TopiColliderComponent::TOPI_WIDTH = 25;
float TopiColliderComponent::TOPI_HEIGHT = 45;

TopiColliderComponent::TopiColliderComponent(AGameObject& owner) : BoxColliderComponent(owner, TOPI_WIDTH, TOPI_HEIGHT, false, ColliderLayer::Enemy, 0, 0)
{

}

void TopiColliderComponent::Update(float deltaTime)
{
}

void TopiColliderComponent::OnCollision(BoxColliderComponent* collider)
{
}

bool TopiColliderComponent::CheckBelow(float distance)
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
				return true;
			}
		}
	}
	return false;
}
