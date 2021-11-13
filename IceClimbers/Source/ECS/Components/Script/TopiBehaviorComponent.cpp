#include "pch.h"
#include "TopiBehaviorComponent.h"
#include "ECS/AGameObject.h"
#include "Game.h"
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/GameObjects/IceCubeObject.h"

TopiBehaviorComponent::TopiBehaviorComponent(AGameObject& owner, float x, float y, int direction) : AScriptComponent(owner),
m_Transform(owner.GetComponent<TransformComponent>()),
m_TopiCollider(owner.GetComponent<TopiColliderComponent>())
{

	m_StartX = x;
	m_StartY = y;
	m_Direction = direction;
}

void TopiBehaviorComponent::Update(float deltaTime)
{
	sf::Vector2f pos = m_Transform.GetPosition();
	if (m_Alive)
	{

		if (!m_GetIceCube)
		{
			GetOwner().GetComponent<TransformComponent>().SetScale(-m_Direction, 1.0f);
			pos.x += m_Speed * deltaTime * m_Direction;
		}
		else
		{
			GetOwner().GetComponent<TransformComponent>().SetScale(m_Direction, 1.0f);
			pos.x -= m_Dash * deltaTime * m_Direction;
		}

		if (pos.x < 0)
		{
			if (m_GetIceCube)
			{
				pos.x = 0;
				m_GetIceCube = false;
				if (m_IceCubeTransform == nullptr)
				{
					auto& obj = GameObjectManager::GetInstance().CreateGameObject<IceCubeObject>(GetOwner().GetName() + "IceCube", m_Direction);
					m_IceCubeTransform = &obj.GetComponent<TransformComponent>();
					obj.SetTopiParent((TopiObject*)&GetOwner());		// commented due to gameobjectmanager deleting errors
				}
				// spawn ice cube
			}
			else
			{
				pos.x = Game::SCREEN_WIDTH;
			}
		}
		else if (pos.x > Game::SCREEN_WIDTH)
		{
			if (m_GetIceCube)
			{
				pos.x = Game::SCREEN_WIDTH;
				m_GetIceCube = false;
				if (m_IceCubeTransform == nullptr)
				{
					auto& obj = GameObjectManager::GetInstance().CreateGameObject<IceCubeObject>(GetOwner().GetName() + "IceCube", m_Direction);
					m_IceCubeTransform = &obj.GetComponent<TransformComponent>();
					obj.SetTopiParent((TopiObject*)&GetOwner());		// commented due to gameobjectmanager deleting errors
				}
				// spawn ice cube
			}
			else
			{
				pos.x = 0;
			}
		}


		m_Transform.SetPosition(pos.x, pos.y);
		if (m_IceCubeTransform != nullptr)
		{
			m_IceCubeTransform->SetPosition(pos.x + 45 * m_Direction, pos.y);
		}

		if (!m_TopiCollider.CheckBelow(deltaTime * m_Gravity))
		{
			if (!m_GetIceCube)
			{
				m_GetIceCube = true;
			}
			else
			{
				Kill();
			}
		}
	}
	else
	{
		m_ElapsedDeadTime += deltaTime;
		if (m_ElapsedDeadTime > m_RespawnTime)
		{
			Respawn();
		}
	}

}

void TopiBehaviorComponent::Kill()
{
	m_Alive = false;
	m_Transform.SetPosition(-10000, -10000);
	GetOwner().GetComponent<TopiColliderComponent>().DisableCollider();
	m_ElapsedDeadTime = 0;
}

void TopiBehaviorComponent::Respawn()
{
	m_Alive = true;
	m_Transform.SetPosition(m_StartX, m_StartY);
	GetOwner().GetComponent<TopiColliderComponent>().EnableCollider();
	m_ElapsedDeadTime = 0;
}

void TopiBehaviorComponent::IceCubeUsed()
{
	m_IceCubeTransform = nullptr;
}
