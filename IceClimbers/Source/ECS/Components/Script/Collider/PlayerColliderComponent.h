#pragma once
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/Components/Script/PlayerMovementComponent.h"
#include "ECS/GameObjects/TileObject.h"
#include "EventSystem/IEventListener.h"

class PlayerColliderComponent :
    public BoxColliderComponent, IEventListener
{
public:
    static float PLAYER_WIDTH;
    static float PLAYER_HEIGHT;

    MAKE_COMPONENT(SCRIPT, PlayerColliderComponent);

    PlayerColliderComponent(AGameObject& owner);
    void Update(float deltaTime) override;
    void OnCollision(BoxColliderComponent* collider) override;
    bool CheckBelow(float distance);
    void CheckPlayerCameraPosition();
    void NotInvincible();
    void Respawn();

    void ReceiveEvent(String eventName) override;
    TileObject* GetLastTile();
private:
    PlayerMovementComponent* m_MovementComponent;
    bool m_IgnoreTiles = false;
    bool m_DeathByCamera = true;
    bool m_Invincible = false;
    int m_HeightLevel = 1;

    TileObject* m_LastTile;
};

