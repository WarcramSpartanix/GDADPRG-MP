#include "pch.h"
#include "AScene.h"

#include "ECS/GameObjectManager.h"

#include "UISystem/UIManager.h"

AScene::AScene(const String& name) :
    m_Name(name)
{
}

void AScene::DestroyObjects()
{
	UIManager::GetInstance().DestroyAllWidgets();
	GameObjectManager::GetInstance().DestroyAllGameObjects();
}