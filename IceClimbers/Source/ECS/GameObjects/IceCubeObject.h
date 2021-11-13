#pragma once
#include "ECS/AGameObject.h"
#include "ECS/GameObjects/TileObject.h"

class TopiObject;

class IceCubeObject :
    public AGameObject
{
public:
    IceCubeObject(const String& name, int direction);
    ~IceCubeObject() override;
    void OnInitialize() override;
    void OnDestroy() override;

    void SetTopiParent(TopiObject*);
};

