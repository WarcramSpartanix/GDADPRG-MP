#include "pch.h"
#include "BoxColliderComponent.h"
#include "ECS/AGameObject.h"
#include "CollisionManager.h"

BoxColliderComponent::BoxColliderComponent(AGameObject& owner, float width, float height, bool isStatic, ColliderLayer layer, float offsetX = 0.0f, float offsetY = 0.0f)
	: AScriptComponent(owner)
{
	m_Tranform = &GetOwner().GetComponent<TransformComponent>();
	m_IsStatic = isStatic;
	m_Width = width;
	m_Height = height;
	m_OffsetX = offsetX;
	m_OffsetY = offsetY;
	m_Layer = layer;

	EnableCollider();
}

BoxColliderComponent::~BoxColliderComponent()
{
	DisableCollider();
}

void BoxColliderComponent::Update(float deltaTime)
{
}

void BoxColliderComponent::OnCollision(BoxColliderComponent* collider)
{
}

sf::FloatRect BoxColliderComponent::GetBounds()
{
	sf::Vector2f pos = m_Tranform->GetPosition();
	sf::FloatRect rect(pos.x - m_Width / 2 + m_OffsetX, pos.y - m_Height / 2 + m_OffsetY, m_Width, m_Height);
	return rect;
}

void BoxColliderComponent::DisableCollider()
{
	CollisionManager::GetInstance().RemoveCollider(this);
}

void BoxColliderComponent::EnableCollider()
{
	CollisionManager::GetInstance().AddCollider(this);
}

bool BoxColliderComponent::CheckCollision(BoxColliderComponent* collider)
{
	sf::FloatRect rect1 = GetBounds();
	sf::FloatRect rect2 = collider->GetBounds();

	return rect1.intersects(rect2);
}
