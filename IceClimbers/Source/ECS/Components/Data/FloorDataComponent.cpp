#include "pch.h"
#include <string>
#include "FloorDataComponent.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Texture/Texture.h"
#include "ECS/GameObjectManager.h"
#include "ResourceSystem/Texture/TextureAssets.h"
#include "ECS/GameObjects/FloorObject.h"
#include "ECS/GameObjects/TopiObject.h"
#include "Game.h"

FloorDataComponent::FloorDataComponent(AGameObject& owner, int heightLevel, TileMap tilemap) : AComponent(owner)
{
	m_HeightLevel = heightLevel;

	String unbreakableTextureName;
	String normalTextureName;
	int fixedTileCount = 0;
	
	DetermineValuesForHeightLevel(&fixedTileCount, &normalTextureName, &unbreakableTextureName);

	if (m_HeightLevel < 9)
	{
		NormalFloors(fixedTileCount, normalTextureName, unbreakableTextureName, tilemap);
	}

}

void FloorDataComponent::AddTopi(int direction)
{
	GameObjectManager::GetInstance().CreateGameObject<TopiObject>(
		GetOwner().GetName() + "Topi", 
		direction == 1 ? 0 : Game::SCREEN_WIDTH,
		m_HeightLevel * -FloorObject::HEIGHT_PER_LEVEL + FloorObject::Y_OFFSET - TileObject::TILE_SIZE, 
		direction);
}

void FloorDataComponent::NormalFloors(int fixedTileCount, String normalTextureName, String unbreakableTextureName, TileMap tilemap)
{
	Debug::Log("Execute NormalFloors()");
	auto& unbreakableTile = ResourceManager::GetInstance().Acquire<Texture>(unbreakableTextureName);
	auto& defaultTile = ResourceManager::GetInstance().Acquire<Texture>(normalTextureName);
	int tilemapIndex = 0;

	for (int i = 0; i < FloorObject::TILE_COUNT_PER_ROW; i++)
	{
		if (i < fixedTileCount || i > FloorObject::TILE_COUNT_PER_ROW - fixedTileCount - 1)
		{
			GameObjectManager::GetInstance().CreateGameObject<TileObject>(
				"Level" + std::to_string(m_HeightLevel) + "-Tile" + std::to_string(i),
				unbreakableTile,
				TileObject::TILE_SIZE * i + FloorObject::X_OFFSET + TileObject::TILE_SIZE / 2.0f,
				m_HeightLevel * -FloorObject::HEIGHT_PER_LEVEL + FloorObject::Y_OFFSET, 
				false, m_HeightLevel);
		}
		else if (tilemap.size() > tilemapIndex)
		{
			if (tilemap[tilemapIndex].first == i)
			{
				if (tilemap[tilemapIndex].second)
				{

					CreateTile("Level" + std::to_string(m_HeightLevel) + "-Tile" + std::to_string(i),
						defaultTile,
						TileObject::TILE_SIZE * i + FloorObject::X_OFFSET + TileObject::TILE_SIZE / 2.0f,
						m_HeightLevel * -FloorObject::HEIGHT_PER_LEVEL + FloorObject::Y_OFFSET,
						true, i);
				}
				else
				{

					CreateTile("Level" + std::to_string(m_HeightLevel) + "-Tile" + std::to_string(i),
						unbreakableTile,
						TileObject::TILE_SIZE * i + FloorObject::X_OFFSET + TileObject::TILE_SIZE / 2.0f,
						m_HeightLevel * -FloorObject::HEIGHT_PER_LEVEL + FloorObject::Y_OFFSET,
						false, i);
				}
				tilemapIndex++;
			}
		}
	}
	for (int i = FloorObject::TILE_COUNT_PER_ROW + fixedTileCount -1; i < FloorObject::TILE_COUNT_PER_ROW * 2 - fixedTileCount; i++)
	{
		if (tilemap.size() > tilemapIndex)
		{
			if (tilemap[tilemapIndex].first == i)
			{
				if (tilemap[tilemapIndex].second)
				{

					CreateTile("Level" + std::to_string(m_HeightLevel) + "-Tile" + std::to_string(i),
						defaultTile,
						TileObject::TILE_SIZE * (i % FloorObject::TILE_COUNT_PER_ROW) + FloorObject::X_OFFSET + TileObject::TILE_SIZE / 2.0f,
						m_HeightLevel * -FloorObject::HEIGHT_PER_LEVEL + FloorObject::Y_OFFSET + TileObject::TILE_SIZE,
						true, i);
				}
				else
				{

					CreateTile("Level" + std::to_string(m_HeightLevel) + "-Tile" + std::to_string(i),
						unbreakableTile,
						TileObject::TILE_SIZE * (i % FloorObject::TILE_COUNT_PER_ROW) + FloorObject::X_OFFSET + TileObject::TILE_SIZE / 2.0f,
						m_HeightLevel * -FloorObject::HEIGHT_PER_LEVEL + FloorObject::Y_OFFSET + TileObject::TILE_SIZE,
						false, i);
				}
				tilemapIndex++;
			}
		}
		else
			break;
	}
}

void FloorDataComponent::DetermineValuesForHeightLevel(int* fixedTileCount, String* normalTextureName, String* unbreakableTextureName)
{

	if (m_HeightLevel < 3)
	{
		*fixedTileCount = 4;
		*normalTextureName = TextureNames::Level::GREEN_TILE;
		*unbreakableTextureName = TextureNames::Level::UNBREAKABLE_GREEN;
	}

	else if (m_HeightLevel < 6)
	{
		*fixedTileCount = 5;
		*normalTextureName = TextureNames::Level::BROWN_TILE;
		*unbreakableTextureName = TextureNames::Level::UNBREAKABLE_BROWN;
	}

	else if (m_HeightLevel < 9)
	{
		*fixedTileCount = 6;
		*normalTextureName = TextureNames::Level::BLUE_TILE;
		*unbreakableTextureName = TextureNames::Level::UNBREAKABLE_BLUE;
	}
	else 
	{
		*fixedTileCount = 0;
		*normalTextureName = TextureNames::Level::BLUE_TILE;
		*unbreakableTextureName = TextureNames::Level::UNBREAKABLE_BLUE;
	}

}

void FloorDataComponent::CreateTile(const String& name, Texture& texture, float x, float y, bool isDestructible, int index)
{
	TileObject& obj = GameObjectManager::GetInstance().CreateGameObject<TileObject>(name, texture, x, y, isDestructible, m_HeightLevel);
	m_TileObjectList[index] = &obj;
}
