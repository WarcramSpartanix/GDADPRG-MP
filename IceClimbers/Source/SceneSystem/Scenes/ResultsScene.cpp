#include "pch.h"
#include "ResultsScene.h"

#include "Game.h"
#include "ScoreManager.h"

#include "ECS/Components/Data/TextComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Render/TextRendererComponent.h"
#include "ECS/Components/Script/SpriteAnimatorComponent.h"

#include "LevelManagement/LevelManager.h"

#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Font/Font.h"
#include "ResourceSystem/Font/FontAssets.h"
#include "ResourceSystem/Texture/TextureAssets.h"

#include "SceneSystem/SceneManager.h"
#include "SceneSystem/SceneNames.h"

#include "UISystem/UIManager.h"
#include "UISystem/Common/BaseWidget.h"
#include "UISystem/Common/TextButtonWidget.h"

ResultsScene::ResultsScene() :
	AScene{SceneNames::RESULT}
{

}

void ResultsScene::LoadResources()
{
	ResourceManager& resourceLoader = ResourceManager::GetInstance();

	resourceLoader.Load<Texture>(TextureNames::ResultsScreen::OUTPUT_BORDER,
                                TextureFilepaths::ResultsScreen::OUTPUT_BORDER);

	resourceLoader.Load<Texture>(TextureNames::ResultsScreen::CHARACTER_SPRITE,
                                TextureFilepaths::ResultsScreen::CHARACTER_SPRITE);

	resourceLoader.Load<Texture>("ItemScoreIcon",
                                "Assets/Textures/TileIcon.png");

	resourceLoader.Load<Font>(FontNames::EMULOGIC,
                             FontFilepaths::EMULOGIC);
}

void ResultsScene::CreateObjects()
{
	ResourceManager& resourceLoader = ResourceManager::GetInstance();
	UIManager& uiManager = UIManager::GetInstance();
	
	Font& font = resourceLoader.Acquire<Font>(FontNames::EMULOGIC);

	BaseWidget& levelLabel = uiManager.CreateWidget<BaseWidget>("LevelLabel");
	{
		// TODO: Get Level ID from Level Manager
		TransformComponent& transform = levelLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f - 375.0f);
		
		const int levelID = LevelManager::GetInstance().GetCurrentLevelID();
		
		levelLabel.AddComponent<TextComponent>(font, 38U, "Mountain " + std::to_string(levelID));
		levelLabel.AddComponent<TextRendererComponent>();
	}
	
	BaseWidget& playerLabel = uiManager.CreateWidget<BaseWidget>("PlayerLabel");
	{
		TransformComponent& transform = playerLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f - 250.0f);
		
		playerLabel.AddComponent<TextComponent>(font, 24U, "Player");
		playerLabel.AddComponent<TextRendererComponent>();
	}

	BaseWidget& outputPanel = uiManager.CreateWidget<BaseWidget>("OutputLabel");
	{
		Texture& texture = resourceLoader.Acquire<Texture>(TextureNames::ResultsScreen::OUTPUT_BORDER);
		TransformComponent& transform = outputPanel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f + 2.0f, Game::SCREEN_HEIGHT / 2.0f + 30.0f);
		transform.SetScale(3.5f, 3.5f);
		outputPanel.AddComponent<SpriteRendererComponent>(texture);
	}

	BaseWidget& characterSprite = uiManager.CreateWidget<BaseWidget>("CharacterSprite");
	{
		Texture& texture = resourceLoader.Acquire<Texture>(TextureNames::ResultsScreen::CHARACTER_SPRITE);
		
		TransformComponent& transform = characterSprite.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f - 90.0f, Game::SCREEN_HEIGHT / 2.0f - 150.0f);
		transform.SetScale(5.0f, 5.0f);
		
		characterSprite.AddComponent<SpriteRendererComponent>(texture);
		characterSprite.AddComponent<SpriteAnimatorComponent>(sf::Vector2i(2, 0),
															  sf::Vector2i(3, 0),
															  sf::Vector2i(32, 32),
															  0.5f,
															  0.5f,
															  false);
	}

	BaseWidget& resultsInfo = uiManager.CreateWidget<BaseWidget>("ResultsInfo");
	{
		TransformComponent& transform = resultsInfo.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f + 60.0f, Game::SCREEN_HEIGHT / 2.0f - 180.0f);

		const bool accomplishedBonus = ScoreManager::GetInstance().GetCurrentLevelScoreData().AccomplishedBonusStage;
		
		// TODO: Score Manager
		// When killed or time lost, no bonus.
		
		// Achieved Bonus, No Bonus, Lose
		// How does bonus work again?

		String firstLine = accomplishedBonus ? "" : "";
		String secondLine = "\n";
		
		resultsInfo.AddComponent<TextComponent>(font, 20U, firstLine + secondLine);
		resultsInfo.AddComponent<TextRendererComponent>();
	}

	// BaseWidget& itemScoreIcon = uiManager.CreateWidget<BaseWidget>("ItemScoreIcon");
	// {
	// 	auto& texture = resourceLoader.Acquire<Texture>("ItemScoreIcon");
	// 	
	// 	TransformComponent& transform = itemScoreIcon.AddComponent<TransformComponent>();
	// 	transform.SetPosition(Game::SCREEN_WIDTH / 2.0f - 70.0f, Game::SCREEN_HEIGHT / 2.0f - 55.0f);
	// 	transform.SetScale(4.0f, 4.0f);
	//
	// 	itemScoreIcon.AddComponent<SpriteRendererComponent>(texture);
	// }
	
	BaseWidget& itemScoreLabel = uiManager.CreateWidget<BaseWidget>("ItemScoreLabel");
	{
		TransformComponent& transform = itemScoreLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f + 60.0f, Game::SCREEN_HEIGHT / 2.0f - 55.0f);
		
		const int itemBaseScore = ITEM_GET_SCORE_BASE;
		const int itemsObtained = ScoreManager::GetInstance().GetCurrentLevelScoreData().ItemsObtained;
		String label            = std::to_string(itemBaseScore) + "x" + std::to_string(itemsObtained);
		
		itemScoreLabel.AddComponent<TextComponent>(font, 24U, label);
		itemScoreLabel.AddComponent<TextRendererComponent>();
	}

	// BaseWidget& enemyDestroyedIcon = uiManager.CreateWidget<BaseWidget>("EnemyDestroyedIcon");
	// {
	// 	auto& texture = resourceLoader.Acquire<Texture>("ItemScoreIcon");
	// 	
	// 	TransformComponent& transform = enemyDestroyedIcon.AddComponent<TransformComponent>();
	// 	transform.SetPosition(Game::SCREEN_WIDTH / 2.0f - 70.0f, Game::SCREEN_HEIGHT / 2.0f + 20.0f);
	// 	transform.SetScale(4.0f, 4.0f);
	//
	// 	enemyDestroyedIcon.AddComponent<SpriteRendererComponent>(texture);
	// }
	
	
	BaseWidget& enemyDestroyedScoreLabel = uiManager.CreateWidget<BaseWidget>("EnemyDestroyedScoreLabel");
	{
		TransformComponent& transform = enemyDestroyedScoreLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f + 60.0f, Game::SCREEN_HEIGHT / 2.0f + 20.0f);

		const int enemyDestroyBase = ENEMY_DESTROY_SCORE_BASE;
		const int enemyDestoryed = ScoreManager::GetInstance().GetCurrentLevelScoreData().EnemiesDestroyed;
		String label            = std::to_string(enemyDestroyBase) + "x" + std::to_string(enemyDestoryed);

		enemyDestroyedScoreLabel.AddComponent<TextComponent>(font, 24U, label);
		enemyDestroyedScoreLabel.AddComponent<TextRendererComponent>();
	}

	// BaseWidget& tileDestroyedIcon = uiManager.CreateWidget<BaseWidget>("TileDestroyedIcon");
	// {
	// 	auto& texture = resourceLoader.Acquire<Texture>("ItemScoreIcon");
	// 	
	// 	TransformComponent& transform = tileDestroyedIcon.AddComponent<TransformComponent>();
	// 	transform.SetPosition(Game::SCREEN_WIDTH / 2.0f - 70.0f, Game::SCREEN_HEIGHT / 2.0f + 95.0f);
	// 	transform.SetScale(4.0f, 4.0f);
	//
	// 	tileDestroyedIcon.AddComponent<SpriteRendererComponent>(texture);
	// }

	BaseWidget& tileDestroyedScoreLabel = uiManager.CreateWidget<BaseWidget>("TileDestroyedScoreLabel");
	{
		TransformComponent& transform = tileDestroyedScoreLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f + 60.0f, Game::SCREEN_HEIGHT / 2.0f + 95.0f);

		const int tilesDestroyedBase = TILE_DESTROY_SCORE_BASE;
		const int tilesDestroyed = ScoreManager::GetInstance().GetCurrentLevelScoreData().TilesDestroyed;
		String label            = std::to_string(tilesDestroyedBase) + "x" + std::to_string(tilesDestroyed);

		tileDestroyedScoreLabel.AddComponent<TextComponent>(font, 24U, label);
		tileDestroyedScoreLabel.AddComponent<TextRendererComponent>();
	}

	BaseWidget& totalLabel = uiManager.CreateWidget<BaseWidget>("TotalLabel");
	{
		TransformComponent& transform = totalLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f + 205.0f);

		totalLabel.AddComponent<TextComponent>(font, 28U, "Total");
		totalLabel.AddComponent<TextRendererComponent>();
	}

	BaseWidget& totalScoreLabel = uiManager.CreateWidget<BaseWidget>("TotalScoreLabel");
	{
		TransformComponent& transform = totalScoreLabel.AddComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, Game::SCREEN_HEIGHT / 2.0f + 265.0f);
		
		const int totalScore = ScoreManager::GetInstance().GetUnprocessedScoreOfCurrentLevel();
		String label            = std::to_string(totalScore);
		
		totalScoreLabel.AddComponent<TextComponent>(font, 24U, label);
		totalScoreLabel.AddComponent<TextRendererComponent>();
	}

	{
		auto onButtonExecute =
            [](AGameObject& buttonObject)->void
            {
            	Debug::Log("Proceed button input press!");
            	SceneManager::GetInstance().LoadScene(SceneNames::TITLE);
            	ScoreManager::GetInstance().ProcessCurrentLevelScore();
            };
		
		TextButtonWidget& proceedButton = uiManager.CreateWidget<TextButtonWidget>("ProceedButton",
                                                                                    font,
                                                                                    30U,
                                                                                    "Proceed",
                                                                                    onButtonExecute);

		TransformComponent& transform = proceedButton.GetComponent<TransformComponent>();
		transform.SetPosition(Game::SCREEN_WIDTH - 150.0f, Game::SCREEN_HEIGHT - 50.0f);
	}

}

void ResultsScene::UnloadResources()
{
	ResourceManager& resourceLoader = ResourceManager::GetInstance();

	resourceLoader.Unload<Texture>(TextureNames::ResultsScreen::OUTPUT_BORDER);

	resourceLoader.Unload<Texture>(TextureNames::ResultsScreen::CHARACTER_SPRITE);

	resourceLoader.Unload<Texture>("ItemScoreIcon");

	resourceLoader.Unload<Font>(FontNames::EMULOGIC);
}
