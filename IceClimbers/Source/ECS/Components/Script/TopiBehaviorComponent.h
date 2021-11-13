#pragma once
#include "ECS/Components/Script/AScriptComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Script/Collider/TopiColliderComponent.h"

class TopiBehaviorComponent :
    public AScriptComponent
{
public:
    TopiBehaviorComponent(AGameObject& owner, float x, float y, int direction);

    MAKE_COMPONENT(SCRIPT, TopiBehaviorComponent)

    void Update(float deltaTime) override;
    void Kill();
    void Respawn();
    void IceCubeUsed();
private:
    const float m_Speed = 80.0f;
    const float m_Dash = 150.0f;
    const float m_Gravity = 600.0f;
    int m_Direction;
    float m_StartX;
    float m_StartY;
    TransformComponent& m_Transform;
    TransformComponent* m_IceCubeTransform = nullptr;
    TopiColliderComponent& m_TopiCollider;

    bool m_GetIceCube = false;

    bool m_Alive = true;
    float m_ElapsedDeadTime;
    const float m_RespawnTime = 10.0f;
};

