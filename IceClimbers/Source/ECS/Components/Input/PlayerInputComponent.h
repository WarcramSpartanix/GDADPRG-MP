#pragma once
#include "AInputComponent.h"
#include "ECS/Components/Script/PlayerMovementComponent.h"

class PlayerInputComponent final:
    public AInputComponent
{
public:
    PlayerInputComponent(AGameObject& owner);

    MAKE_COMPONENT(INPUT, PlayerInputComponent)

    void ProcessInput(const sf::Event& event);
    int* GetDirectionPointer();
    bool* GetHammerActivePointer();

    bool IsMoveRight() const;
    bool IsMoveLeft() const;
    bool IsJumpTriggered() const;
    bool IsAttackTriggered() const;
private:
    int m_Direction = 1;
    bool m_HammerActive = false;
    bool m_MoveLeft = false;
    bool m_MoveRight = false;
    bool m_JumpTriggered = false;
    bool m_AttackTriggered = false;
    
};

