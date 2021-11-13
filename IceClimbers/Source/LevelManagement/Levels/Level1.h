#pragma once
#include "LevelManagement/Level.h"

class Level1 :
    public Level
{
public:
    Level1();

    void GenerateFloors() override;
    void GenerateBonusStage() override;
    void GenerateItems() override;
};

namespace Level1_Floors
{
    /*
    {4,true},   {5, true},  {6,true},   {7,true},   {8,true},   {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
        {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true} ,  {29,true}
    {38, true},  {39,true},   {40,true},   {41,true},   {42,true},   {43,true},  {44,true}, {45,true},  {46,true}, {47,true},  
    {48,true},  {49,true},  {50,true},  {51,true},  {52,true},  {53,true},  {54,true},  {55,true},  {56,true},
        {57,true},  {58,true},  {59,true},  {60,true} ,  {61,true} ,  {62,true}, {63, true}
    */

    const TileMap FLOOR1 = {
        {4,true},   {5, true},  {6,true},   {7,true},   {8,true},   {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
        {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true} ,  {29,true} 
    };

    const TileMap FLOOR2 = { 
        {4, true}, {5, true}, {6, true}, {7, true}, {8, true}, {9, true}, {24,true},  {25,true},  {26,true},  
        {27,true} ,  {28,true} ,  {29,true}, {39,true}, {40,true}, {41,true}, {42, true}, {43, true}, {58,true}, {59,true}, 
        {60,true}, {61,true} 
    };

    const TileMap FLOOR3 = {
        {5, true},  {6,true},   {7,true},   {8,true},   {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
        {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true}, 
        {39,true},   {40,true},   {41,true},   {42,true},   {43,true},
        {48,true},  {49,true},  {50,true},  {51,true},  {52,true},  {53,true},  {54,true},
        {59,true},  {60,true} ,  {61,true} ,  {62,true}
    };

    const TileMap FLOOR4 = { {5, true},  {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true}, {23,true},
        {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true} };

    const TileMap FLOOR5 = { 
        {8,true},   {9,true},   {10,true},  {11,true}, {16,true},  {17,true},  {18,true},  {19,true},
        {24,true},  {25,true},  {26,true},  {27,true}, {42,true},   {43,true},  {44,true}, {45,true},
        {50,true},  {51,true},  {52,true},  {53,true}, {58,true},  {59,true},  {60,true} ,  {61,true}
        };

    const TileMap FLOOR6 = {  
        {6,true},   {7,true},   {8,true},   {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
        {24,true},  {25,true},  {26,true},  {27,true},
        {40,true},   {41,true},   {42,true},   {43,true}, 
        {47,true}, {48,true},  {49,true},  {50,true},  {51,true},  {52,true}, {57,true},  {58,true},  {59,true},  {60,true} ,  {61,true}
    };
    const TileMap FLOOR7 = {  
        {6,true},   {7,true},   {8,true},   {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
        {24,true},  {25,true},  {26,true},  {27,true}, {40,true},   {41,true}, {47,true},
        {48,true},  {49,true},  {50,true},  {51,true},{55,true},  {56,true},
        {57,true},  {58,true},  {59,true},  {60,true} ,  {61,true}
    };

    const TileMap FLOOR8 = { {6,true},   {7,true},   {8,true},   {9,true},   {10,true},  {11,true}, {12,true},  {13,true},
        {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
        {24,true},  {25,true},  {26,true},  {27,true},  {40,true},   {41,true}, {45,true},  {46,true}, {47,true},
        {48,true},  {49,true},  {50,true},  {51,true},  {52,true},  {53,true},  {54,true}, {58,true},  {59,true},  {60,true}
    };
}