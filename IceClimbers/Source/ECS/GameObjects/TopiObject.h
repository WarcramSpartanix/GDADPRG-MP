#pragma once
#include "ECS/AGameObject.h"
class TopiObject :
    public AGameObject
{
public:
    TopiObject(const String& name, float x, float y, int direction);
    ~TopiObject() override;
    void OnInitialize() override;
    void OnDestroy() override;
    void Respawn();
    void Kill();
};

