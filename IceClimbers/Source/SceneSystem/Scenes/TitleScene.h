#pragma once
#include "SceneSystem/AScene.h"

class TitleScene final : public AScene
{
public:
	explicit TitleScene();
	~TitleScene() override = default;

	void LoadResources() override;
	void CreateObjects() override;
	void UnloadResources() override;
};
