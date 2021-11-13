#pragma once
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
class TopiColliderComponent :
    public BoxColliderComponent
{
public:
    static float TOPI_WIDTH;
    static float TOPI_HEIGHT;

    MAKE_COMPONENT(SCRIPT, PlayerColliderComponent);

    TopiColliderComponent(AGameObject& owner);
    void Update(float deltaTime) override;
    void OnCollision(BoxColliderComponent* collider) override;
    bool CheckBelow(float distance);

};

