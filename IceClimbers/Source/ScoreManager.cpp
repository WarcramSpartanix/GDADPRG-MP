#include "pch.h"
#include "ScoreManager.h"

ScoreManager& ScoreManager::GetInstance()
{
	static ScoreManager instance;
	return instance;
}

ScoreManager::~ScoreManager()
{
}

int ScoreManager::GetScoreOfLevel(const int levelID) 
{
	return m_LevelScoreTable[levelID];
}

int ScoreManager::GetUnprocessedScoreOfCurrentLevel() const
{
	int score = 0;
	score += ENEMY_DESTROY_SCORE_BASE * m_CurrentLevelScoreData.EnemiesDestroyed;
	score += TILE_DESTROY_SCORE_BASE * m_CurrentLevelScoreData.TilesDestroyed;
	score += ITEM_GET_SCORE_BASE * m_CurrentLevelScoreData.ItemsObtained;
	return score;
}

const LevelScoreData& ScoreManager::GetCurrentLevelScoreData() const
{
	return m_CurrentLevelScoreData;
}

int ScoreManager::GetTotalScore()
{
	int score = 0;
	for (auto levelScore : m_ScoreList)
	{
		score += levelScore;
	}
	return score;
}

void ScoreManager::TrackScoreForLevel(const int levelID)
{
	m_CurrentLevelScoreData.LevelID = levelID;
}

void ScoreManager::RegisterScore(const RewardType rewardType,
                                 const int count)
{
	switch (rewardType)
	{
		case RewardType::TILE_DESTROY:
			m_CurrentLevelScoreData.TilesDestroyed += count;
			break;
		case RewardType::ENEMY_DESTROY:
			m_CurrentLevelScoreData.EnemiesDestroyed += count;
			break;
		case RewardType::ITEM_GET:
			m_CurrentLevelScoreData.ItemsObtained += count;
			break;
		default:
			break;
	}
}

void ScoreManager::ProcessCurrentLevelScore()
{
	int score = 0;
	score += ENEMY_DESTROY_SCORE_BASE * m_CurrentLevelScoreData.EnemiesDestroyed;
	score += TILE_DESTROY_SCORE_BASE * m_CurrentLevelScoreData.TilesDestroyed;
	score += ITEM_GET_SCORE_BASE * m_CurrentLevelScoreData.ItemsObtained;
	m_ScoreList.push_back(score);
	m_LevelScoreTable[m_CurrentLevelScoreData.LevelID] = score;
}

void ScoreManager::ResetScores()
{
	m_ScoreList.clear();
	m_CurrentLevelScoreData = LevelScoreData();
}

ScoreManager::ScoreManager() :
	m_CurrentLevelScoreData{}
{
}
