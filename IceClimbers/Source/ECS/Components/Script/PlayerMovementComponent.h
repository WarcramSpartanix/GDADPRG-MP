#pragma once
#include "AScriptComponent.h"
#include "EventSystem/Event.h"
#include "ECS/Components/Data/TransformComponent.h"

class PlayerInputComponent;
class PlayerMovementComponent final:
    public AScriptComponent
{
public:
    PlayerMovementComponent(AGameObject& owner);

    MAKE_COMPONENT(SCRIPT, PlayerMovementComponent)

    void Update(float deltaTime) override;
    void StopVelocityX();
    void StopVelocityY();
    bool MovingUpwards();
    

public:
    bool m_Jump = false;
    bool m_Falling = true;
    bool m_Attack = false;

private:
    void ApplyBooleans(float deltaTime);
    void ApplyGravity(float deltaTime);
    void ApplyVelocity(float deltaTime);

    const float m_ACCELERATION = 300.0f;
    const float m_ACCELERATION_JUMP = 100.0f;
    const float m_JUMP_VELOCITY = -520.0f;
    const float m_START_X_VELOCITY_FALL = 30.0f;
    const float m_MAX_X_VELOCITY = 300.0f;
    const float m_MAX_X_VELOCITY_JUMP = 150.0f;
    const float m_GRAVITY = 600.0f;

    sf::Vector2f m_Velocity;

    TransformComponent& m_TransformComponent;
    PlayerInputComponent& m_InputComponent;
};

