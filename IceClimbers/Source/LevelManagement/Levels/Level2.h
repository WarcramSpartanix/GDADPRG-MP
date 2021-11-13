#pragma once
#include "LevelManagement/Level.h"
class Level2 :
    public Level
{
public:
    Level2();

    void GenerateFloors() override;
    void GenerateBonusStage() override;
    void GenerateItems() override;
};

