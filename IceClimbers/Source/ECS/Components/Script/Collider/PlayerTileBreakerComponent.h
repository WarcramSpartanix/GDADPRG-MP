#pragma once
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/Components/Script/PlayerMovementComponent.h"
class PlayerTileBreakerComponent :
    public BoxColliderComponent
{
public:
    static float BOX_WIDTH;
    static float BOX_HEIGHT;

    MAKE_COMPONENT(SCRIPT, PlayerTileBreakerComponent);

    PlayerTileBreakerComponent(AGameObject& owner);
    void Update(float deltaTime) override;
    void OnCollision(BoxColliderComponent* collider) override;

private:
    PlayerMovementComponent* m_MovementComponent;
    bool m_HasDestroyed = false; // ensures that only one tile can be destroyed per jump
};

