#include "pch.h"
#include <SceneSystem/SceneNames.h>
#include "LevelScene.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Texture/Texture.h"
#include "ECS/GameObjects/PlayerObject.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/GameObjects/FloorObject.h"
#include "ECS/GameObjects/TimerObject.h"

#include "ResourceSystem/Texture/TextureAssets.h"
#include "LevelManagement/LevelManager.h"

#include "ResourceSystem/Font/FontAssets.h"

LevelScene::LevelScene() : AScene(SceneNames::LEVEL)
{
	
}

void LevelScene::LoadResources()
{
	ResourceManager::GetInstance().Load<Texture>("Player", "Assets/Textures/MainGame/Player.png");
	ResourceManager::GetInstance().Load<Texture>("Topi", "assets/textures/MainGame/Topi.png");
	ResourceManager::GetInstance().Load<Texture>("Bird", "assets/textures/Bird.png");
	ResourceManager::GetInstance().Load<Texture>("IceCube", "assets/textures/IceCube.png");
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::GREEN_TILE, TextureFilepaths::Level::GREEN_TILE);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::BROWN_TILE, TextureFilepaths::Level::BROWN_TILE);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::BLUE_TILE, TextureFilepaths::Level::BLUE_TILE);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::UNBREAKABLE_GREEN, TextureFilepaths::Level::UNBREAKABLE_GREEN);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::UNBREAKABLE_BROWN, TextureFilepaths::Level::UNBREAKABLE_BROWN);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::UNBREAKABLE_BLUE, TextureFilepaths::Level::UNBREAKABLE_BLUE);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR4, TextureFilepaths::Level::FLOOR4);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR5, TextureFilepaths::Level::FLOOR5);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS1, TextureFilepaths::Level::FLOOR_WALLS1);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS2, TextureFilepaths::Level::FLOOR_WALLS2);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS3, TextureFilepaths::Level::FLOOR_WALLS3);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS4, TextureFilepaths::Level::FLOOR_WALLS4);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS5, TextureFilepaths::Level::FLOOR_WALLS5);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS6, TextureFilepaths::Level::FLOOR_WALLS6);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS7, TextureFilepaths::Level::FLOOR_WALLS7);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::FLOOR_WALLS8, TextureFilepaths::Level::FLOOR_WALLS8);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::BONUS_WALLS_V1, TextureFilepaths::Level::BONUS_WALLS_V1);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::BONUS_WALLS_V2, TextureFilepaths::Level::BONUS_WALLS_V2);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::CLOUD3, TextureFilepaths::Level::CLOUD3);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::CLOUD6, TextureFilepaths::Level::CLOUD6);
	ResourceManager::GetInstance().Load<Texture>(TextureNames::Level::ITEM_ICONS, TextureFilepaths::Level::ITEM_ICONS);

	ResourceManager::GetInstance().Load<Font>(FontNames::EMULOGIC, FontFilepaths::EMULOGIC);
}

void LevelScene::CreateObjects()
{
	auto& gameObjectManager = GameObjectManager::GetInstance();
	auto& resourceManager = ResourceManager::GetInstance();

	LevelManager::GetInstance().LoadCurrentLevel();

	auto& texture = resourceManager.Acquire<Texture>("Player");
	auto& obj1 = gameObjectManager.CreateGameObject<PlayerObject>("Player", texture);

	gameObjectManager.CreateGameObject<TimerObject>("TimerObject", 40);
}

void LevelScene::UnloadResources()
{
	ResourceManager::GetInstance().Unload<Texture>("Player");
	ResourceManager::GetInstance().Unload<Texture>("Topi");
	ResourceManager::GetInstance().Unload<Texture>("Bird");
	ResourceManager::GetInstance().Unload<Texture>("IceCube");
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::GREEN_TILE);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::BROWN_TILE);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::BLUE_TILE);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::UNBREAKABLE_GREEN);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::UNBREAKABLE_BROWN);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::UNBREAKABLE_BLUE);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR4);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR5);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS1);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS2);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS3);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS4);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS5);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS6);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS7);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::FLOOR_WALLS8);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::BONUS_WALLS_V1);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::BONUS_WALLS_V2);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::CLOUD3);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::CLOUD6);
	ResourceManager::GetInstance().Unload<Texture>(TextureNames::Level::ITEM_ICONS);

	ResourceManager::GetInstance().Unload<Font>(FontNames::EMULOGIC);
}
