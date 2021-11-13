#include "pch.h"
#include "Level1.h"
#include "ECS/GameObjectManager.h"
#include "ECS/GameObjects/FloorObject.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Texture/TextureAssets.h"
#include "ECS/GameObjects/CloudObject.h"
#include "Game.h"
#include "ECS/GameObjects/ItemObject.h"
#include "ECS/GameObjectManager.h"

Level1::Level1()
{
}

void Level1::GenerateFloors()
{
	FloorObject* floor;
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level1", 1, Level1_Floors::FLOOR1);//FloorPresets::Level0::floor1);
	floor->AddTopi(-1);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level2", 2, Level1_Floors::FLOOR2);//FloorPresets::Level0::floor1);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level3", 3, Level1_Floors::FLOOR3);//FloorPresets::Level0::floor3);
	floor->AddTopi(1);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level4", 4, Level1_Floors::FLOOR4);//FloorPresets::Level0::floor3);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level5", 5, Level1_Floors::FLOOR5);//FloorPresets::Level0::floor3);
	floor->AddTopi(1);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level6", 6, Level1_Floors::FLOOR6);//FloorPresets::Level0::floor6);
	floor->AddTopi(-1);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level7", 7, Level1_Floors::FLOOR7);//FloorPresets::Level0::floor6);
	floor->AddTopi(-1);
	floor = &GameObjectManager::GetInstance().CreateGameObject<FloorObject>("level8", 8, Level1_Floors::FLOOR8);// FloorPresets::Level0::floor6);

	Texture& cloud3Texture = ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::CLOUD3);
	Texture& cloud6Texture = ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::CLOUD6);

	GameObjectManager::GetInstance().CreateGameObject<CloudObject>("Cloud1", cloud6Texture, 20, -950, 180, 180.0f, 10);
	GameObjectManager::GetInstance().CreateGameObject<CloudObject>("Cloud2", cloud6Texture, Game::SCREEN_WIDTH, -1220, 180, -150.0f, 12);
	GameObjectManager::GetInstance().CreateGameObject<CloudObject>("Cloud3", cloud6Texture, Game::SCREEN_WIDTH, -1430, 180, -120.0f, 14);
	GameObjectManager::GetInstance().CreateGameObject<CloudObject>("Cloud4", cloud6Texture, 20, -1700, 180, -160.0f, 15);
}

void Level1::GenerateBonusStage()
{
	BonusStageWalls();
	BonusStageFixedTiles();

	float TileSize = 30.0f;
	float BottomMost = -680.0f;

	CreateTile("BonusTile1", 165 + TileSize * 5, BottomMost - TileSize * 11, 11);
	CreateTile("BonusTile2", 165 + TileSize * 6, BottomMost - TileSize * 11, 11);
	CreateTile("BonusTile3", 165 + TileSize * 7, BottomMost - TileSize * 11, 11);
	CreateTile("BonusTile4", 165 + TileSize * 8, BottomMost - TileSize * 11, 11);

	CreateTile("BonusTile5", 165 + TileSize * 13, BottomMost - TileSize * 15, 12);
	CreateTile("BonusTile6", 165 + TileSize * 14, BottomMost - TileSize * 15, 12);
	CreateTile("BonusTile7", 165 + TileSize * 15, BottomMost - TileSize * 15, 12);
	CreateTile("BonusTile8", 165 + TileSize * 16, BottomMost - TileSize * 15, 12);

	CreateTile("BonusTile9", 165 + TileSize * 7, BottomMost - TileSize * 21, 13);
	CreateTile("BonusTile10", 165 + TileSize * 8, BottomMost - TileSize * 21, 13);
	CreateTile("BonusTile11", 165 + TileSize * 9, BottomMost - TileSize * 21, 13);
	CreateTile("BonusTile12", 165 + TileSize * 10, BottomMost - TileSize * 21, 13);
	CreateTile("BonusTile13", 165 + TileSize * 11, BottomMost - TileSize * 21, 13);
	CreateTile("BonusTile14", 165 + TileSize * 12, BottomMost - TileSize * 21, 13);

	CreateTile("BonusTile15", 165 + TileSize * 4, BottomMost - TileSize * 30, 14);
	CreateTile("BonusTile16", 165 + TileSize * 5, BottomMost - TileSize * 30, 14);
	CreateTile("BonusTile17", 165 + TileSize * 6, BottomMost - TileSize * 30, 14);
	CreateTile("BonusTile18", 165 + TileSize * 7, BottomMost - TileSize * 30, 14);

	CreateTile("BonusTile19", 165 + TileSize * 10, BottomMost - TileSize * 30, 14);
	CreateTile("BonusTile20", 165 + TileSize * 11, BottomMost - TileSize * 30, 14);
	CreateTile("BonusTile21", 165 + TileSize * 12, BottomMost - TileSize * 30, 14);
	CreateTile("BonusTile22", 165 + TileSize * 13, BottomMost - TileSize * 30, 14);

	CreateTile("BonusTile23", 165 + TileSize * 9, BottomMost - TileSize * 41, 15);
	CreateTile("BonusTile24", 165 + TileSize * 10, BottomMost - TileSize * 41, 15);
	CreateTile("BonusTile25", 165 + TileSize * 11, BottomMost - TileSize * 41, 15);
	CreateTile("BonusTile26", 165 + TileSize * 12, BottomMost - TileSize * 41, 15);
	CreateTile("BonusTile27", 165 + TileSize * 13, BottomMost - TileSize * 41, 15);
	CreateTile("BonusTile28", 165 + TileSize * 14, BottomMost - TileSize * 41, 15);
	CreateTile("BonusTile29", 165 + TileSize * 15, BottomMost - TileSize * 41, 15);
}

void Level1::GenerateItems()
{
	float TileSize = 30.0f;
	float BottomMost = -680.0f;

	GameObjectManager::GetInstance().CreateGameObject<ItemObject>("Item1", 165 + TileSize * 7, BottomMost - TileSize * 12, 1);
	GameObjectManager::GetInstance().CreateGameObject<ItemObject>("Item2", 165 + TileSize * 16, BottomMost - TileSize * 16, 1);
	GameObjectManager::GetInstance().CreateGameObject<ItemObject>("Item3", 165 + TileSize * 9, BottomMost - TileSize * 22, 1);
	GameObjectManager::GetInstance().CreateGameObject<ItemObject>("Item4", 165 + TileSize * 4, BottomMost - TileSize * 31, 1);
	GameObjectManager::GetInstance().CreateGameObject<ItemObject>("Item5", 165 + TileSize * 13, BottomMost - TileSize * 31, 1);
	GameObjectManager::GetInstance().CreateGameObject<ItemObject>("Item6", 165 + TileSize * 12, BottomMost - TileSize * 42, 1);
}
