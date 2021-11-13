#include "pch.h"

#include "Core/PlatformDetection.h"

#include "Game.h"

#include "SceneSystem/SceneManager.h"
#include "SceneSystem/SceneNames.h"
#include "SceneSystem/Scenes/ResultsScene.h"
#include "SceneSystem/Scenes/TitleScene.h"
#include "SceneSystem/Scenes/LevelScene.h"

int main()
{
	const Uint windowWidth  = 1000U;
	const Uint windowHeight = 900U;
	const String gameTitle = "Ice Climbers";
	const String defaultSceneName = SceneNames::TITLE;

	const List<AScene*> gameScenes
	{
		new TitleScene(),
		new ResultsScene(),
		new LevelScene()
	};
	
	auto game = Game(windowWidth,
                     windowHeight,
                     gameTitle,
                     gameScenes,
                     defaultSceneName);
	
	game.Run();
}