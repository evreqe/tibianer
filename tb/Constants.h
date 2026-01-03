#pragma once

#include "common.h"

#include "Types.h"
#include "Resources.h"

namespace tb
{
    namespace Constants
    {
        inline const std::string GameTitle = "Tibianer";

        inline const std::string PlayerNameDefault = "Avatar";

        inline const std::uint32_t NumSprites = 4096; // 2048x2048

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

        inline const float PaddingRenderWindow = 11.0f; // the outer rectangle of the render window
        inline const float PaddingBackgroundTexture = 7.0f;
        inline const float PaddingWoodBorder = 3.0f;
        inline const float PaddingBlackRectangle = 1.0f;
        inline const float PaddingBetweenLeftAndRightLayoutRect = 12.0f;

        inline const float GuiRightLayoutWidthAsFloat = 108.0f;
        inline const int GuiRightLayoutWidthAsInt = 108;

        inline const std::uint32_t NumZAxis = 16;

        inline const tb::ZAxis ZAxisMin = 0;
        inline const tb::ZAxis ZAxisMax = 15;
        inline const tb::ZAxis ZAxisDefault = 7;

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

        namespace BitmapFonts
        {
            inline const std::uint32_t NumGlyphs = 256; // ASCII codes
        }
    }

    enum class SpriteFlag : std::uint8_t
    {
        Null,
        Solid,
        BlockProjectiles, // big sprites, trees
        BlockPathFinding,
        Move,
        PickUp,
        Rotate,
        Hang,
        Use, // food
        UseOnTarget, // fishing rod
        Read, // scrolls, books
        MoveAbove, // going up and down stairs, ladders, holes
        MoveBelow, // going up and down stairs, ladders, holes
        Water,
        Lava,
        Oil,
        Decal, // blood splatters
        TileEdge, // borders
        StepTile, // pressure switch
        Animated,
        Creature,
        Corpse,
        Container,
        LightSource,
        Offset, // has an 8 pixel offset from the bottom right (example: player outfits, mailbox)
        Height, // things on top of it have an offset and it stacks up vertically on the z-axis (example: parcels)
        IgnoreHeight,
        Stack, // stacks together in bundles (example: gold coins)
        NoDraw, // (example: pink tile)
        DrawFirst,
        DrawLast, // drawn on top of everything else
    };

    inline constexpr auto SpriteFlagEntries = magic_enum::enum_entries<tb::SpriteFlag>();

    inline constexpr auto SpriteFlagCount = magic_enum::enum_count<tb::SpriteFlag>();

    using SpriteFlagBitset = std::bitset<SpriteFlagCount>;

    enum class GameState : std::uint8_t
    {
        Testing,
        EnterGame,
        NewGameJourneyOnward,
        MapSelect,
        LoadingMap,
        InGame,
        Paused,
    };

    enum class TimeOfDay : std::uint8_t
    {
        Day,
        Night,
    };

    enum class TextJustifyType : std::uint8_t
    {
        Left,
        Center,
        Right
    };

    enum class Direction : std::uint8_t
    {
        Up,
        Right,
        Down,
        Left,
    };

    enum class MovementDirection : std::uint8_t
    {
        Null,
        Up,
        Right,
        Down,
        Left,
        UpLeft,
        UpRight,
        DownLeft,
        DownRight,
    };

    enum class Vocation : std::uint8_t
    {
        None,
        Knight,
        Paladin,
        Druid,
        Sorcerer,
    };

    enum class BloodType : std::uint8_t
    {
        None,
        Red,
        Green,
    };

    enum class ThingType : std::uint8_t
    {
        Null,
        Object,
        Creature,
        Animation,
        Entity,
    };

    enum class DrawOrderType : std::uint8_t
    {
        First,
        TileEdge,
        Decal,
        Default,
        Last,
    };

    enum class PatternType : std::uint8_t
    {
        Tile,
        Object,
    };

    enum class TileMapType : std::uint8_t
    {
        Tiles,
        TileEdges,
    };

    enum class MapObjectLayerType : std::uint8_t
    {
        Entities,
        Creatures,
        Objects,
        TileEdgeObjects,
    };

    enum class ObjectType : std::uint8_t
    {
        Null,
        ChangeMap,
        Container,
        Sign,
        Book,
        Key,
        Teleporter,
        Door,
        Bed,
        Lever,
        StepTile,
        Creature,
    };

    enum class WeaponType : std::uint8_t
    {
        Null,
        Fist,
        Club,
        Sword,
        Axe,
        Bow,
        Crossbow,
        Spear,
        Knife,
        Shield,
        Wand,
    };

    enum class EquipmentSlot : std::uint8_t
    {
        Neck, // amulets
        Head,
        Bag, // bag or backpack

        LeftHand,
        RightHand, // shields

        Legs,
        Chest,
        Feet,
    };
}
