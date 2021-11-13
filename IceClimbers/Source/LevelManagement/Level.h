#pragma once
class Level
{
public:
	virtual void GenerateFloors() = 0;
	virtual void GenerateBonusStage() = 0;
	virtual void GenerateItems() = 0;
	void BonusStageWalls();
	void BonusStageFixedTiles();
	void CreateTile(const String& name, float x, float y, int m_BonusLevel);


	static float STARTING_HEIGHT;
	static float STARTING_LEFT_X;
	static float STARTING_RIGHT_X;
	static float DISTANCE;
};

