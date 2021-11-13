#pragma once
#include "AScriptComponent.h"

#include "ECS/AComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Data/VelocityComponent.h"

class MoveComponent final : public AScriptComponent
{
public:
	explicit MoveComponent(AGameObject& owner);

	MAKE_COMPONENT(SCRIPT, MoveComponent)

	void Update(float deltaTime) override;

private:
	TransformComponent& m_TransformComponent;
	VelocityComponent& m_VelocityComponent;
};
