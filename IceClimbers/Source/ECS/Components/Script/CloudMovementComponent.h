#pragma once
#include "ECS/Components/Script/AScriptComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
class CloudMovementComponent :
    public AScriptComponent
{
public:
    CloudMovementComponent(AGameObject& owner, float speed);

    MAKE_COMPONENT(SCRIPT, CloudMovementComponent)

    void Update(float deltaTime) override;
    float GetLastMoveDistance();
private:
    float m_Speed;
    TransformComponent& m_Transform;
    float m_MoveDistance;
};

