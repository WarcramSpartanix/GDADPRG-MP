#pragma once
#include "ECS/AGameObject.h"
#include "ResourceSystem/Texture/Texture.h"
class BonusWall :
    public AGameObject
{
public:
    BonusWall(const String& name, float x, float y, Texture& texture);
    ~BonusWall();

    void OnInitialize() override;
    void OnDestroy() override;

    static float WALL_WIDTH;
    static float WALL_HEIGHT;
};

