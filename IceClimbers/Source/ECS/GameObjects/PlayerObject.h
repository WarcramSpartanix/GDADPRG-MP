#pragma once
#include "ECS/AGameObject.h"
#include "ResourceSystem/Texture/Texture.h"
#include "EventSystem/IEventListener.h"

class PlayerObject :
    public AGameObject
{
public:
    PlayerObject(const String& name, Texture& texture);
    ~PlayerObject() override;
    void OnInitialize() override;
    void OnDestroy() override;
};

