#include "pch.h"
#include "Level.h"
#include "ECS/GameObjectManager.h"
#include "ResourceSystem/ResourceManager.h"
#include "ECS/GameObjects/BonusWall.h"
#include "ResourceSystem/Texture/TextureAssets.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/GameObjects/TileObject.h"
#include "ECS/GameObjects/PterodactylObject.h"

float Level::STARTING_HEIGHT = 1030.0f - 190.0f * (9);
float Level::STARTING_LEFT_X = 45.0f;
float Level::STARTING_RIGHT_X = 965.0f;
float Level::DISTANCE = 30.0f;


void Level::BonusStageWalls()
{
	int textureIndex = 0;
	auto& texture1 = ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::BONUS_WALLS_V1);
	auto& texture2 = ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::BONUS_WALLS_V2);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			GameObjectManager::GetInstance().CreateGameObject<BonusWall>
				("BonusStageWallL " + std::to_string(i) + "-" + std::to_string(j),
					STARTING_LEFT_X + i * DISTANCE,
					(-i * 7 - j) * DISTANCE + STARTING_HEIGHT,
					textureIndex % 2 == 0 ? texture1 : texture2);
			textureIndex++;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		GameObjectManager::GetInstance().CreateGameObject<BonusWall>
			("BonusStageWallL 7-" + std::to_string(i),
				STARTING_LEFT_X + 6 * DISTANCE,
				(i + 7 * 6) * -DISTANCE + STARTING_HEIGHT,
				textureIndex % 2 == 0 ? texture1 : texture2);
		textureIndex++;
	}

	textureIndex = 0;

	////Right

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			GameObjectManager::GetInstance().CreateGameObject<BonusWall>
				("BonusStageWallR " + std::to_string(i) + "-" + std::to_string(j),
					STARTING_RIGHT_X - i * DISTANCE,
					(-i * 7 - j) * DISTANCE + STARTING_HEIGHT,
					textureIndex % 2 == 0 ? texture1 : texture2);
			textureIndex++;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		GameObjectManager::GetInstance().CreateGameObject<BonusWall>
			("BonusStageWallR 7-" + std::to_string(i),
				STARTING_RIGHT_X - 6 * DISTANCE,
				(i + 7 * 6) * -DISTANCE + STARTING_HEIGHT,
				textureIndex % 2 == 0 ? texture1 : texture2);
		textureIndex++;
	}
}

void Level::BonusStageFixedTiles()
{


	CreateTile("FixedBonusTile1", 15, -680, 8);
	CreateTile("FixedBonusTile2", 45, -680, 8);
	CreateTile("FixedBonusTile3", 75, -680, 8);
	CreateTile("FixedBonusTile4", 105, -680, 8);
	CreateTile("FixedBonusTile5", 135, -680, 8);
	CreateTile("FixedBonusTile6", 165, -680, 8);
	CreateTile("FixedBonusTile7", 195, -680, 8);

	CreateTile("FixedBonusTile8", 285, -680, 8);
	CreateTile("FixedBonusTile9", 315, -680, 8);
	CreateTile("FixedBonusTile10", 345, -680, 8);
	CreateTile("FixedBonusTile11", 375, -680, 8);
	CreateTile("FixedBonusTile12", 405, -680, 8);
	CreateTile("FixedBonusTile13", 435, -680, 8);

	CreateTile("FixedBonusTile14", 555, -680, 8);
	CreateTile("FixedBonusTile15", 585, -680, 8);
	CreateTile("FixedBonusTile16", 615, -680, 8);
	CreateTile("FixedBonusTile17", 645, -680, 8);
	CreateTile("FixedBonusTile18", 675, -680, 8);
	CreateTile("FixedBonusTile19", 705, -680, 8);

	CreateTile("FixedBonusTile20", 795, -680, 8);
	CreateTile("FixedBonusTile21", 825, -680, 8);
	CreateTile("FixedBonusTile22", 855, -680, 8);
	CreateTile("FixedBonusTile23", 885, -680, 8);
	CreateTile("FixedBonusTile24", 915, -680, 8);
	CreateTile("FixedBonusTile25", 945, -680, 8);
	CreateTile("FixedBonusTile26", 975, -680, 8);

	CreateTile("FixedBonusTile27", 195, -800, 9);
	CreateTile("FixedBonusTile28", 225, -800, 9);
	CreateTile("FixedBonusTile29", 255, -800, 9);
	CreateTile("FixedBonusTile30", 285, -800, 9);

	CreateTile("FixedBonusTile31", 405, -800, 9);
	CreateTile("FixedBonusTile32", 435, -800, 9);
	CreateTile("FixedBonusTile33", 465, -800, 9);
	CreateTile("FixedBonusTile34", 495, -800, 9);
	CreateTile("FixedBonusTile35", 525, -800, 9);
	CreateTile("FixedBonusTile36", 555, -800, 9);
	CreateTile("FixedBonusTile37", 585, -800, 9);

	CreateTile("FixedBonusTile38", 705, -800, 9);
	CreateTile("FixedBonusTile39", 735, -800, 9);
	CreateTile("FixedBonusTile40", 765, -800, 9);
	CreateTile("FixedBonusTile41", 795, -800, 9);


	CreateTile("FixedBonusTile42", 195, -2030, 16);
	CreateTile("FixedBonusTile43", 225, -2030, 16);
	CreateTile("FixedBonusTile44", 255, -2030, 16);
	CreateTile("FixedBonusTile45", 285, -2030, 16);
	CreateTile("FixedBonusTile46", 315, -2030, 16);
	CreateTile("FixedBonusTile47", 345, -2030, 16);
	CreateTile("FixedBonusTile48", 375, -2030, 16);
	CreateTile("FixedBonusTile49", 405, -2030, 16);

	CreateTile("FixedBonusTile50", 675, -2030, 16);
	CreateTile("FixedBonusTile51", 705, -2030, 16);
	CreateTile("FixedBonusTile52", 735, -2030, 16);
	CreateTile("FixedBonusTile53", 765, -2030, 16);
	CreateTile("FixedBonusTile54", 795, -2030, 16);
	CreateTile("FixedBonusTile55", 825, -2030, 16);


	GameObjectManager::GetInstance().CreateGameObject<PterodactylObject>("Pterodactyl");
}

void Level::CreateTile(const String& name, float x, float y, int m_BonusLevel)
{
	auto& texture = ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::UNBREAKABLE_BLUE);

	GameObjectManager::GetInstance().CreateGameObject<TileObject>(name, texture, x, y, false, m_BonusLevel);
}
