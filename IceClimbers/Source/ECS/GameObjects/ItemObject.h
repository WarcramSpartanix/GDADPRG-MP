#pragma once
#include "ECS/AGameObject.h"
#include "ResourceSystem/Texture/Texture.h"

class ItemObject :
    public AGameObject
{
public:
    ItemObject(const String& name, float x, float y, int index);
    ~ItemObject() override;
    void OnInitialize() override;
    void OnDestroy() override;

    static float ITEM_WIDTH;
    static float ITEM_HEIGHT;
};

