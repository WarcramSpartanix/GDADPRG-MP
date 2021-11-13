#pragma once
class LevelManager final
{
public:
	static LevelManager& GetInstance();
	~LevelManager();

	int GetMaxLevelCount() const;
	int GetCurrentLevelID() const;

	void CurrentLevelToNextLevel();
	void CurrentLevelToPrevLevel();

	void LoadCurrentLevel();
private:
	int m_MaxLevelCount;
	int m_CurrentLevelID;

	LevelManager();
};
