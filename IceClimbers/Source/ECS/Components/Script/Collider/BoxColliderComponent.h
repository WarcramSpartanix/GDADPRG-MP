#pragma once
#include "ECS/Components/Script/AScriptComponent.h"
#include "ECS/Components/Data/TransformComponent.h"

enum ColliderLayer
{
    Tile, Player, Enemy, Wall, Cloud, Item, Bird, IceCube
};

class BoxColliderComponent :
    public AScriptComponent
{

    

public:
    BoxColliderComponent(AGameObject& owner, float width, float height, bool isStatic, ColliderLayer layer, float offsetX, float offsetY);
    ~BoxColliderComponent();

    MAKE_COMPONENT(SCRIPT, BoxColliderComponent)

    virtual void Update(float deltaTime) override;
    virtual void OnCollision(BoxColliderComponent* collider);
    virtual sf::FloatRect GetBounds();
    void DisableCollider();
    void EnableCollider();

    bool m_IsStatic;
    ColliderLayer m_Layer;
protected:
    bool CheckCollision(BoxColliderComponent* collider);

    TransformComponent* m_Tranform;
    float m_Width;
    float m_Height;
    float m_OffsetX;
    float m_OffsetY;
};

