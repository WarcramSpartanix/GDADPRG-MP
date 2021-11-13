#pragma once
#include "SceneSystem/AScene.h"

class ResultsScene final : public AScene
{
public:
	explicit ResultsScene();
	~ResultsScene() override = default;

	void LoadResources() override;
	void CreateObjects() override;
	void UnloadResources() override;
};
