#include "pch.h"
#include "FloorObject.h"
#include "ResourceSystem/Texture/Texture.h"
#include "ResourceSystem/Texture/TextureAssets.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ResourceSystem/ResourceManager.h"
#include "ECS/GameObjects/TileObject.h"

int FloorObject::TILE_COUNT_PER_ROW = 34;
float FloorObject::HEIGHT_PER_LEVEL = 190.0f;
float FloorObject::HEIGHT_PER_BONUS_LEVEL = 90.0f;
float FloorObject::X_OFFSET = -10.0f;
float FloorObject::Y_OFFSET = 1030.0f;


FloorObject::FloorObject(const String& name, int levelNum, TileMap tileMap) : AGameObject(name)
{
	

	auto& transform = AddComponent<TransformComponent>();
	transform.SetPosition(X_OFFSET + TILE_COUNT_PER_ROW * TileObject::TILE_SIZE / 2.0f, Y_OFFSET - HEIGHT_PER_LEVEL * (levelNum + 0.5));
	switch (levelNum)
	{
	case 1:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS1));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 2:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS2));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 3:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS3));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 4:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS4));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 5:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS5));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 6:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS6));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 7:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS7));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	case 8:
		AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::FLOOR_WALLS8));
		AddComponent<FloorDataComponent>(levelNum, tileMap);
		break;
	default:
		break;
	}
	;

	Debug::Log("Level{0} Location: {1},{2} ", levelNum, transform.GetPosition().x, transform.GetPosition().y);
}

FloorObject::~FloorObject()
{
}

void FloorObject::OnInitialize()
{
}

void FloorObject::OnDestroy()
{
}

void FloorObject::AddTopi(int direction)
{
	GetComponent<FloorDataComponent>().AddTopi(direction);
}
