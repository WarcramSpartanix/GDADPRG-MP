#pragma once
#include "BoxColliderComponent.h"

class PlayerGroundHammerComponent :
    public BoxColliderComponent
{
public:
    static float BOX_WIDTH;
    static float BOX_HEIGHT;

    MAKE_COMPONENT(SCRIPT, PlayerGroundHammerComponent);

    PlayerGroundHammerComponent(AGameObject& owner);
    void Update(float deltaTime) override;
    void OnCollision(BoxColliderComponent* collider) override;
    sf::FloatRect GetBounds() override;

private:
    PlayerGroundHammerComponent* m_MovementComponent;
    int* m_Direction;
    bool* m_Active;
};

