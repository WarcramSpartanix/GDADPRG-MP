#pragma once
#include "ECS/AGameObject.h"
#include "ResourceSystem/Texture/Texture.h"

class CloudObject :
    public AGameObject
{
public:
    static float TILE_SIZE;

    CloudObject(const String& name, Texture& texture, float x, float y, float width, float speed, int heightLevel);
    ~CloudObject() override;
    void OnInitialize() override;
    void OnDestroy() override;
    int GetHeightLevel();
    float GetLastMoveDistance();

protected:
    int m_HeightLevel;

};

