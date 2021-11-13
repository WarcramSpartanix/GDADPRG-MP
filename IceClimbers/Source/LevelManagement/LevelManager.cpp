#include "pch.h"
#include "LevelManager.h"
#include "ScoreManager.h"
#include "Levels/Level0.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"

LevelManager& LevelManager::GetInstance()
{
	static LevelManager instance;
	return instance;
}

LevelManager::~LevelManager()
{
}

int LevelManager::GetMaxLevelCount() const
{
	return m_MaxLevelCount;
}

int LevelManager::GetCurrentLevelID() const
{
	return m_CurrentLevelID;
}

void LevelManager::CurrentLevelToNextLevel()
{
	m_CurrentLevelID++;
	m_CurrentLevelID = std::min(m_CurrentLevelID, m_MaxLevelCount - 1);
	
	ScoreManager::GetInstance().ResetScores();
	ScoreManager::GetInstance().TrackScoreForLevel(m_CurrentLevelID);
}

void LevelManager::CurrentLevelToPrevLevel()
{
	m_CurrentLevelID--;
	m_CurrentLevelID = std::max(m_CurrentLevelID, 0);
}

void LevelManager::LoadCurrentLevel()
{
	switch (m_CurrentLevelID)
	{
	case 0:
	{
		Level0* newLevel = new Level0();
		newLevel->GenerateFloors();
		newLevel->GenerateBonusStage();
		newLevel->GenerateItems();
		break;
	}
	case 1:
	{
		Level1* newLevel = new Level1();
		newLevel->GenerateFloors();
		newLevel->GenerateBonusStage();
		newLevel->GenerateItems();
		break;
	}
	case 2:
	{
		Level2* newLevel = new Level2();
		newLevel->GenerateFloors();
		newLevel->GenerateBonusStage();
		newLevel->GenerateItems();
		break;
	}
	default:
		Debug::Warn("Loading Invalid Level ID");
		break;
	}
}

LevelManager::LevelManager() :
	m_MaxLevelCount{3},
	m_CurrentLevelID{0}	// pls change back to 0
{
}
