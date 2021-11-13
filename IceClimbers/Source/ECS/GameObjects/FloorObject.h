#pragma once
#include "ECS/AGameObject.h"
#include "ECS/Components/Data/FloorDataComponent.h"

class FloorObject :
    public AGameObject
{
public:
    static int TILE_COUNT_PER_ROW;
    static float HEIGHT_PER_LEVEL;
    static float HEIGHT_PER_BONUS_LEVEL;
    static float X_OFFSET;
    static float Y_OFFSET;


    FloorObject(const String& name, int levelNum, TileMap tileMap);
    ~FloorObject() override;
    void OnInitialize() override;
    void OnDestroy() override;
    void AddTopi(int direction);
};

