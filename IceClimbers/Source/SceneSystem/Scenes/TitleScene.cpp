#include "pch.h"
#include "TitleScene.h"

#include "Game.h"
#include "ScoreManager.h"

#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Render/TextRendererComponent.h"

#include "LevelManagement/LevelManager.h"

#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Font/Font.h"
#include "ResourceSystem/Font/FontAssets.h"
#include "ResourceSystem/Music/Music.h"
#include "ResourceSystem/Music/MusicAssets.h"
#include "ResourceSystem/Texture/Texture.h"
#include "ResourceSystem/Texture/TextureAssets.h"

#include "SceneSystem/SceneManager.h"
#include "SceneSystem/SceneNames.h"

#include "UISystem/UIManager.h"
#include "UISystem/Common/BaseWidget.h"
#include "UISystem/Common/TextButtonWidget.h"

TitleScene::TitleScene() :
	AScene(SceneNames::TITLE)
{
}

void TitleScene::LoadResources()
{
	ResourceManager& resourceLoader = ResourceManager::GetInstance();

	resourceLoader.Load<Texture>(TextureNames::TitleScreen::BANNER,
								TextureFilepaths::TitleScreen::BANNER);

	resourceLoader.Load<Font>(FontNames::EMULOGIC,
                             FontFilepaths::EMULOGIC);

	// TODO: Add music
	// resourceLoader.Load<Music>(MusicNames::STAGE_SELECT,
    //                            MusicFilepaths::STAGE_SELECT);
}

void TitleScene::CreateObjects()
{
	ResourceManager& resourceLoader = ResourceManager::GetInstance();
	UIManager& uiManager = UIManager::GetInstance();
	
	Font& font = resourceLoader.Acquire<Font>(FontNames::EMULOGIC);

	BaseWidget& titleBanner = uiManager.CreateWidget<BaseWidget>("TitleBanner");
	{
		Texture& bannerTex = resourceLoader.Acquire<Texture>(TextureNames::TitleScreen::BANNER);
		TransformComponent& transform = titleBanner.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f - 200.0f);
		transform.SetScale(3.5f, 3.5f);
		titleBanner.AddComponent<SpriteRendererComponent>(bannerTex);
	}

	{
		auto onButtonExecute =
            [](AGameObject& buttonObject)->void
            {
            	Debug::Log("Play button input press!");
            	
            	// TODO: Level Manager will create the level based on the below option
                const int currentLevel = LevelManager::GetInstance().GetCurrentLevelID();

            	// Scores will now be reset whenever the player starts playing!
            	ScoreManager::GetInstance().ResetScores();
            	ScoreManager::GetInstance().TrackScoreForLevel(currentLevel);
            	SceneManager::GetInstance().LoadScene(SceneNames::LEVEL);
            };
		
		TextButtonWidget& playButton = uiManager.CreateWidget<TextButtonWidget>("PlayButton",
																			 font,
																				30U,
																				"Play",
																			 onButtonExecute);
		
		TransformComponent& transform = playButton.GetComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f + 50.0f);
	}

	BaseWidget& levelToPlayLabel = uiManager.CreateWidget<BaseWidget>("LevelToPlayLabel");
	{
		TransformComponent& transform = levelToPlayLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f + 150.0f);
		transform.SetScale(1.0f, 1.0f);

		levelToPlayLabel.AddComponent<TextComponent>(font, 30U, "Mountain 0");
		levelToPlayLabel.AddComponent<TextRendererComponent>();
	}

	{
		auto onButtonExecute =
            [&](AGameObject& buttonObject)->void
            {
            	Debug::Log("Prev Level button input press!");
            	LevelManager::GetInstance().CurrentLevelToPrevLevel();
            	
            	const String output = "Mountain " + std::to_string(LevelManager::GetInstance().GetCurrentLevelID());
            	levelToPlayLabel.GetComponent<TextComponent>().SetString(output);
            };
		
		TextButtonWidget& leftLevelSelectionButton = uiManager.CreateWidget<TextButtonWidget>("LeftLevelSelectionButton",
                                                                             font,
                                                                                38U,
                                                                                "<",
                                                                             onButtonExecute);
		
		TransformComponent& transform = leftLevelSelectionButton.GetComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f - 200.0f, Game::SCREEN_HEIGHT / 2.0f + 150.0f);
	}

	{
		auto onButtonExecute =
            [&](AGameObject& buttonObject)->void
            {
            	Debug::Log("Next Level button input press!");
            	LevelManager::GetInstance().CurrentLevelToNextLevel();
            	
            	const String output = "Mountain " + std::to_string(LevelManager::GetInstance().GetCurrentLevelID());
            	levelToPlayLabel.GetComponent<TextComponent>().SetString(output);
            };
		
		TextButtonWidget& leftLevelSelectionButton = uiManager.CreateWidget<TextButtonWidget>("RightLevelSelectionButton",
                                                                             font,
                                                                                38U,
                                                                                ">",
                                                                             onButtonExecute);
		
		TransformComponent& transform = leftLevelSelectionButton.GetComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f + 200.0f, Game::SCREEN_HEIGHT / 2.0f + 150.0f);
	}

	BaseWidget& currentHighScoreLabel = uiManager.CreateWidget<BaseWidget>("HighScoreLabel");
	{
		TransformComponent& transform = currentHighScoreLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f + 250.0f);
		
		const int topScore = ScoreManager::GetInstance().GetTotalScore();
		currentHighScoreLabel.AddComponent<TextComponent>(font, 30U, "Top Score: " + std::to_string(topScore));
		currentHighScoreLabel.AddComponent<TextRendererComponent>();
	}
}

void TitleScene::UnloadResources()
{
	ResourceManager& resourceLoader = ResourceManager::GetInstance();
	
	resourceLoader.Unload<Texture>(TextureNames::TitleScreen::BANNER);

	resourceLoader.Unload<Font>(FontNames::EMULOGIC);
	
	// resourceLoader.Unload<Music>(MusicNames::STAGE_SELECT);
}
