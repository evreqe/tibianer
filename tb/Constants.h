#pragma once

#include "common.h"

#include "tb/Types.h"
#include "tb/Enums.h"

namespace tb::Constants
{

inline const std::string GameTitle = "Tibianer";

inline const std::string PlayerNameDefault = "Avatar";

inline const std::filesystem::path SystemFontFilePath = "fonts/system.ttf";

inline const std::uint32_t NumSprites = 4096; // 2048x2048 spritesheet

inline const std::uint32_t NumWaterAnimationFrames = 16;
inline const std::uint32_t NumWaterSpritesPerAnimationFrame = 8;

inline const std::uint32_t WaterPatternWidth = 4;
inline const std::uint32_t WaterPatternHeight = 2;

inline const std::uint32_t NumOutfitSpriteIndex = 4; // head, body, legs, feet
inline const std::uint32_t NumOutfitSpriteDirections = 4; // up, right, down, left

inline const std::uint32_t NumOutfitSpriteIDListHead = 11;
inline const std::uint32_t NumOutfitSpriteIDListBody = 11;
inline const std::uint32_t NumOutfitSpriteIDListLegs = 9;
inline const std::uint32_t NumOutfitSpriteIDListFeet = 9;

inline const tb::SpriteID SpriteIDNull = 0;
inline const tb::SpriteID SpriteIDDefault = 1;

inline const float SpriteSizeAsFloat = 32.0f;

inline const std::int32_t TileSize = 32;
inline const std::int32_t TileSizeHalf = 16;
inline const float TileSizeAsFloat = 32.0f;
inline const float TileSizeHalfAsFloat = 16.0f;

inline const float TileCreatureOffset = 8.0f;

inline const std::uint32_t NumAxisZ = 16;

inline const tb::AxisZ AxisZMin = 0;
inline const tb::AxisZ AxisZMax = 15;
inline const tb::AxisZ AxisZDefault = 7;

inline const tb::LightBrightness LightBrightnessMin = 0;
inline const tb::LightBrightness LightBrightnessMax = 255;
inline const tb::LightBrightness LightBrightnessUnderGround = 32;

inline const tb::OutfitIndex OutfitIndexHead = 0;
inline const tb::OutfitIndex OutfitIndexBody = 1;
inline const tb::OutfitIndex OutfitIndexLegs = 2;
inline const tb::OutfitIndex OutfitIndexFeet = 3;

inline const std::uint32_t TileHeightMovementDifference = 2; // player cannot move to a tile if it has vertical objects stacked 2 axis higher than the player
inline const std::uint32_t TileHeightMax = 5; // highest you can stack vertical objects on a tile, like chairs or parcels
inline const std::uint32_t TileHeightClimbDifference = 3; // height needed to climb up or down a z-axis level using stacked vertical objects, like going from the ground to the roof of a house

inline const std::uint32_t SkillLevelDefault = 10;

inline const std::uint32_t NumGlyphsForBitmapFont = 256; // ASCII codes

inline const float GUIRightLayoutWidthAsFloat = 108.0f;
inline const int GUIRightLayoutWidthAsInt = 108;

inline const float GUIPaddingRenderWindow = 11.0f; // the outer rectangle of the render window
inline const float GUIPaddingBackgroundTexture = 7.0f;
inline const float GUIPaddingWoodBorder = 3.0f;
inline const float GUIPaddingBlackRectangle = 1.0f;
inline const float GUIPaddingBetweenLeftAndRightLayoutRect = 12.0f;

}
