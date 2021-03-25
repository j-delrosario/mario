#pragma once
#include <string>
#include "utils/Globals.h"
#define WIN_WIDTH 1024
#define WIN_HEIGHT 896
#define CAM_WIDTH 2.56 / 2
#define CAM_HEIGHT 2.24 / 2

#define TILE_TEXTURE_ID 0 // index for tile sprites
#define CHAR_TEXTURE_ID 1 // index for character sprites

#define SPRITE_SIZE_S {0.16 * 2, 0.16 * 2}

#define CHAR_SPRITE 1 / 32.0f

#define FRAME_DURATION 0.25f

static std::string LEVELID_TO_BG_FILEPATH(uint32_t levelID) 
{
	switch (levelID)
	{
	case 0:
		return "assets/textures/bg_ow_1-1.png";
	default:
		break;
	}
}

static std::string LEVELID_TO_WORLDID(uint32_t levelID)
{
	switch (levelID)
	{
	case 0:
		return "1-1";
	default:
		break;
	}
}
