#include "pch.h"
#include "TransformComponent.h"

#include "ECS/AGameObject.h"

TransformComponent::TransformComponent(AGameObject& owner) :
	AComponent{owner}
{
	
}

const sf::Vector2f& TransformComponent::GetPosition() const
{
	return m_Transform.getPosition();
}

void TransformComponent::SetPosition(float x,
                                     float y)
{
	m_Transform.setPosition(x, y);
	UpdateWorldTransform();
}

void TransformComponent::Move(const float x,
                              const float y)
{
	m_Transform.move(x, y);
	UpdateWorldTransform();
}

float TransformComponent::GetRotation() const
{
	return m_Transform.getRotation();
}

void TransformComponent::SetRotation(const float angle)
{
	m_Transform.setRotation(angle);
	UpdateWorldTransform();
}

void TransformComponent::Rotate(const float angleAdded)
{
	m_Transform.rotate(angleAdded);
	UpdateWorldTransform();
}

const sf::Vector2f& TransformComponent::GetScale() const
{
	return m_Transform.getScale();
}

void TransformComponent::SetScale(float scaleX, float scaleY)
{
	m_Transform.setScale(scaleX, scaleY);
	UpdateWorldTransform();
}

void TransformComponent::Scale(const float scaleVectorX,
                               const float scaleVectorY)
{
	m_Transform.scale(scaleVectorX, scaleVectorY);
	UpdateWorldTransform();
}

void TransformComponent::SetOrigin(float x,
                                   float y)
{
	m_Transform.setOrigin(x, y);
	UpdateWorldTransform();
}

const sf::Vector2f& TransformComponent::GetOrigin() const
{
	return m_Transform.getOrigin();
}

const sf::Transform& TransformComponent::GetLocalTransform() const
{
	return m_Transform.getTransform();
}

const sf::Transform& TransformComponent::GetWorldTransform() const
{
	return m_WorldTransform;
}

void TransformComponent::UpdateWorldTransform()
{
	m_WorldTransform = sf::Transform::Identity;
	AGameObject* parent = &GetOwner();
	while (parent != nullptr)
	{
		TransformComponent& parentTransform = parent->GetComponent<TransformComponent>();
		m_WorldTransform =  parentTransform.GetLocalTransform() * m_WorldTransform;
		parent = parent->GetParent();
	}
}

