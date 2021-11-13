#pragma once
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/GameObjects/TileObject.h"
#include "ECS/GameObjects/TopiObject.h"

class IceCubeColliderComponent :
    public BoxColliderComponent
{
public:
    static float ICE_CUBE_WIDTH;
    static float ICE_CUBE_HEIGHT;

    MAKE_COMPONENT(SCRIPT, IceCubeColliderComponent);

    IceCubeColliderComponent(AGameObject& owner, int direction);
    void Update(float deltaTime) override;
    void OnCollision(BoxColliderComponent* collider) override;
    bool CheckBelow(float distance);
    bool CheckNextTile(sf::FloatRect rect);
    TileObject* CreateTile(float x, float y, Texture* texture);
    void SetTopiParent(TopiObject*);
private:
    TileObject* m_LastTile = nullptr;
    int m_Direction;
    TopiObject* m_TopiParent = nullptr;
};

