#pragma once
#include <string>
#include "Core/TypeAlias.h"

namespace TextureNames
{
	namespace TitleScreen
	{
		const String BANNER = STRINGIFY(BANNER);
	}

	namespace ResultsScreen
	{
		const String OUTPUT_BORDER = STRINGIFY(OUTPUT_BORDER);
		const String CHARACTER_SPRITE = STRINGIFY(CHARACTER_SPRITE);
	}
	
	namespace Level
	{
		const String GREEN_TILE = "GreenTile";
		const String BROWN_TILE = "BrownTile";
		const String BLUE_TILE = "BlueTile";
		const String UNBREAKABLE_GREEN = "Floor1";
		const String UNBREAKABLE_BROWN = "Floor2";
		const String UNBREAKABLE_BLUE = "Floor3";
		const String FLOOR4 = "Floor4";
		const String FLOOR5 = "Floor5";

		const String FLOOR_WALLS1 = "FLOOR_WALLS1";
		const String FLOOR_WALLS2 = "FLOOR_WALLS2";
		const String FLOOR_WALLS3 = "FLOOR_WALLS3";
		const String FLOOR_WALLS4 = "FLOOR_WALLS4";
		const String FLOOR_WALLS5 = "FLOOR_WALLS5";
		const String FLOOR_WALLS6 = "FLOOR_WALLS6";
		const String FLOOR_WALLS7 = "FLOOR_WALLS7";
		const String FLOOR_WALLS8 = "FLOOR_WALLS8";
		const String BONUS_WALLS_V1 = "BonusWallsV1";
		const String BONUS_WALLS_V2 = "BonusWallsV2";
		const String CLOUD3 = "CLOUD3";
		const String CLOUD6 = "CLOUD6";
		const String ITEM_ICONS = "ITEM_ICONS";
	}
};

namespace TextureFilepaths
{
	namespace TitleScreen
	{
		const String BANNER = "Assets/Textures/TitleScreen/TitleBanner.png";
	}

	namespace ResultsScreen
	{
		const String OUTPUT_BORDER = "Assets/Textures/ResultsScreen/Results_OutputBorder.png";
		const String CHARACTER_SPRITE = "Assets/Textures/ResultsScreen/Results_CharacterSpriteSheet.png";
	}

	namespace Level
	{

		const String FLOOR_WALLS1 = "Assets/Textures/MainGame/FloorWalls1.png";
		const String FLOOR_WALLS2 = "Assets/Textures/MainGame/FloorWalls2.png";
		const String FLOOR_WALLS3 = "Assets/Textures/MainGame/FloorWalls3.png";
		const String FLOOR_WALLS4 = "Assets/Textures/MainGame/FloorWalls4.png";
		const String FLOOR_WALLS5 = "Assets/Textures/MainGame/FloorWalls5.png";
		const String FLOOR_WALLS6 = "Assets/Textures/MainGame/FloorWalls6.png";
		const String FLOOR_WALLS7 = "Assets/Textures/MainGame/FloorWalls7.png";
		const String FLOOR_WALLS8 = "Assets/Textures/MainGame/FloorWalls8.png";
		const String BONUS_WALLS_V1 = "Assets/Textures/MainGame/BonusWallsV1.png";
		const String BONUS_WALLS_V2 = "Assets/Textures/MainGame/BonusWallsV2.png";

		const String GREEN_TILE = "Assets/Textures/MainGame/GreenTile.png";
		const String BROWN_TILE = "Assets/Textures/MainGame/BrownTile.png";
		const String BLUE_TILE = "Assets/Textures/MainGame/BlueTile.png";
		const String UNBREAKABLE_GREEN = "Assets/Textures/MainGame/Floor1-2.png";
		const String UNBREAKABLE_BROWN = "Assets/Textures/MainGame/Floor3-5.png";
		const String UNBREAKABLE_BLUE = "Assets/Textures/MainGame/Floor6-8.png";
		const String FLOOR4 = "Assets/Textures/MainGame/Floor9.png";
		const String FLOOR5 = "Assets/Textures/MainGame/Unbreakable4Tile.png";
		const String CLOUD3 = "Assets/Textures/MainGame/Cloud3.png";
		const String CLOUD6 = "Assets/Textures/MainGame/Cloud6.png";
		const String ITEM_ICONS = "Assets/Textures/ItemIcons.png";
	}
}
