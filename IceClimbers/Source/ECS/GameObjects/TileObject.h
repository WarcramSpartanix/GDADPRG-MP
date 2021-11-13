#pragma once
#include "ECS/AGameObject.h"
#include "ResourceSystem/Texture/Texture.h"

class TileObject :
    public AGameObject
{
public:
    static float TILE_SIZE;


    TileObject(const String& name, Texture& texture, float x, float y, bool isDestructible, int heightLevel);
    ~TileObject() override;
    void OnInitialize() override;
    void OnDestroy() override;
    void DestroyTile();
    int GetHeightLevel();

    bool m_IsDestructible;

protected:
    int m_HeightLevel;
};

