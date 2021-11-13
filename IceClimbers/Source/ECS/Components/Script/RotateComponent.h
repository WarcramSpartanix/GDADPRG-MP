#pragma once
#include "AScriptComponent.h"
#include "ECS/Components/Data/TransformComponent.h"

class RotateComponent final : public AScriptComponent
{
public:
	RotateComponent(AGameObject& owner,
					float initialAngle,
					float initialRotationSpeed);

	MAKE_COMPONENT(SCRIPT, RotateComponent)

	void Update(float deltaTime) override;

private:
	TransformComponent& m_TransformComponent;
	float m_RotationSpeed;
};
