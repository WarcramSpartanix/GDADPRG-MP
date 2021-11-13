#pragma once
#include "ECS/AGameObject.h"
class PterodactylObject :
    public AGameObject
{
public:
    PterodactylObject(const String& name);
    ~PterodactylObject() override;
    void OnInitialize() override;
    void OnDestroy() override;
};

