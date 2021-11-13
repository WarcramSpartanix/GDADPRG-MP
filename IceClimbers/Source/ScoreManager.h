#pragma once

enum class RewardType
{
	TILE_DESTROY,
	ENEMY_DESTROY,
	ITEM_GET,
};

struct LevelScoreData
{
	int LevelID;
	int TilesDestroyed;
	int EnemiesDestroyed;
	int ItemsObtained;
	bool AccomplishedBonusStage;
};

const int TILE_DESTROY_SCORE_BASE = 10;
const int ENEMY_DESTROY_SCORE_BASE = 300;
const int ITEM_GET_SCORE_BASE = 500;

class ScoreManager final
{
public:
	static ScoreManager& GetInstance();
	~ScoreManager();
	
	void TrackScoreForLevel(int levelID);
	void RegisterScore(RewardType rewardType, int count);
	void ProcessCurrentLevelScore();
	
	int GetScoreOfLevel(int levelID);
	int GetUnprocessedScoreOfCurrentLevel() const;
	const LevelScoreData& GetCurrentLevelScoreData() const;
	int GetTotalScore();
	void ResetScores();

private:
	LevelScoreData m_CurrentLevelScoreData;
	HashTable<int, int> m_LevelScoreTable;
	List<int> m_ScoreList;
	
	ScoreManager();
};
