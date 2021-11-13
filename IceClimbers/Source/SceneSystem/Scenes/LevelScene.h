#pragma once
#include "SceneSystem/AScene.h"

class LevelScene :
    public AScene
{
public:
	LevelScene();
	~LevelScene() override = default;

	void LoadResources() override;
	void CreateObjects() override;
	void UnloadResources() override;
};

