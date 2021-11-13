#include "pch.h"
#include "RotateComponent.h"

#include "ECS/AGameObject.h"

RotateComponent::RotateComponent(AGameObject& owner,
                                 const float initialAngle,
                                 const float initialRotationSpeed) :
	AScriptComponent{owner},
	m_TransformComponent{GetOwner().GetComponent<TransformComponent>()},
	m_RotationSpeed{initialRotationSpeed}
{
	m_TransformComponent.SetRotation(initialAngle);
}

void RotateComponent::Update(const float deltaTime)
{
	m_TransformComponent.Rotate(m_RotationSpeed * deltaTime);
}
