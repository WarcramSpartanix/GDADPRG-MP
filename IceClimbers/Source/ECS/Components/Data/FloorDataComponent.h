#pragma once
#include "ECS/AComponent.h"
#include "ECS/GameObjects/TileObject.h"



class FloorDataComponent: public AComponent
{
public:
	FloorDataComponent(AGameObject& owner, int heightLevel, TileMap tilemap);

	MAKE_COMPONENT(DATA, FloorDataComponent);

	void AddTopi(int direction);

private:
	int m_HeightLevel;
	HashTable<int, TileObject*> m_TileObjectList;

	void NormalFloors(int fixedTileCount, String normalTextureName, String unbreakableTextureName, TileMap tilemap);
	void DetermineValuesForHeightLevel(int* fixedTileCount, String* normalTextureName, String* unbreakableTextureName);

	void CreateTile(const String& name, Texture& texture, float x, float y, bool isDestructible, int i);
	
};

namespace FloorPresets
{
	// selected preset list<int> for the floor generation
	namespace Level0
	{
		const TileMap floor1 = { {4,true}, {5, true}, {6,true}, {7,true}, {8,true}, {9,true}, {10,true}, {11,true}, {12,true},  {13,true}, 
		 {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true}, 
		 {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true} ,  {29,true} ,  {30,true} };

		const TileMap floor3 = { {5, true}, {6,true}, {7,true}, {8,true}, {9,true}, {10,true}, {11,true}, {12,true},  {13,true},
		 {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
		 {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true} ,  {29,true} };

		const TileMap floor6 = { {6,true}, {7,true}, {8,true}, {9,true}, {10,true}, {11,true}, {12,true},  {13,true},
		 {14,true},  {15,true},  {16,true},  {17,true},  {18,true},  {19,true},  {20,true},  {21,true},  {22,true},  {23,true},
		 {24,true},  {25,true},  {26,true},  {27,true} ,  {28,true} };
	}
}