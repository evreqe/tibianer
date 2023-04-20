#pragma once

#include "common.h"

namespace tb
{
    using ZAxis_t = uint8_t;
    using OutfitIndex_t = uint8_t;
    using SpriteID_t = uint16_t;

    using SpriteIDList = std::vector<SpriteID_t>;

    namespace Constants
    {
        inline const std::string GameTitle = "Tibianer";

        inline const std::string PlayerNameDefault = "Avatar";

        inline const uint32_t NumSprites = 4096; // 2048x2048

        inline const uint32_t NumWaterAnimationFrames = 16;
        inline const uint32_t NumWaterSpritesPerAnimationFrame = 8;

        inline const uint32_t WaterPatternWidth = 4;
        inline const uint32_t WaterPatternHeight = 2;

        inline const uint32_t NumOutfitSpriteIndex = 4; // head, body, legs, feet
        inline const uint32_t NumOutfitSpriteDirections = 4; // up, right, down, left

        inline const uint32_t NumOutfitSpriteIDListHead = 11;
        inline const uint32_t NumOutfitSpriteIDListBody = 11;
        inline const uint32_t NumOutfitSpriteIDListLegs = 9;
        inline const uint32_t NumOutfitSpriteIDListFeet = 9;

        inline const SpriteID_t SpriteIDNull = 0;
        inline const SpriteID_t SpriteIDDefault = 1;

        inline const int TileSize = 32;
        inline const int TileSizeHalf = 16;
        inline const float TileSizeFloat = 32.0f;
        inline const float TileSizeHalfFloat = 16.0f;

        inline const float TileCreatureOffset = 8.0f;

        inline const uint32_t NumZAxis = 16;

        inline const uint32_t TileHeightMovementDifference = 2; // player cannot move to a tile if it has vertical objects stacked 2 axis higher than the player
        inline const uint32_t TileHeightMax = 5; // highest you can stack vertical objects on a tile, like chairs or parcels
        inline const uint32_t TileHeightClimbDifference = 3; // height needed to climb up or down a z-axis level using stacked vertical objects, like going from the ground to the roof of a house

        inline const uint32_t SkillLevelDefault = 10;
    }

    namespace Textures
    {
        inline sf::Texture Introduction;
        inline sf::Texture EnterGame;
        inline sf::Texture NewGameJourneyOnward;
        inline sf::Texture MapSelect;
        inline sf::Texture Loading;
        inline sf::Texture MapEditor;
        inline sf::Texture Sprites;
        inline sf::Texture GUI;
        inline sf::Texture Scroll;
        inline sf::Texture Wood;
        inline sf::Texture WoodHorizontal1;
        inline sf::Texture WoodHorizontal2;
        inline sf::Texture WoodVertical1;
        inline sf::Texture WoodVertical2;

        inline const std::unordered_map<std::string, sf::Texture&> Names =
        {
            {"Introduction",               tb::Textures::Introduction},
            {"Enter Game",                 tb::Textures::EnterGame},
            {"New Game Journey Onward",    tb::Textures::NewGameJourneyOnward},
            {"Map Select",                 tb::Textures::MapSelect},
            {"Loading",                    tb::Textures::Loading},
            {"Map Editor",                 tb::Textures::MapEditor},
            {"Sprites",                    tb::Textures::Sprites},
            {"GUI",                        tb::Textures::GUI},
            {"Scroll",                     tb::Textures::Scroll},
            {"Wood",                       tb::Textures::Wood},
            {"Wood Horizontal 1",          tb::Textures::WoodHorizontal1},
            {"Wood Horizontal 2",          tb::Textures::WoodHorizontal2},
            {"Wood Vertical 1",            tb::Textures::WoodVertical1},
            {"Wood Vertical 2",            tb::Textures::WoodVertical2},
        };
    }

    namespace Cursors
    {
        inline sf::Cursor Arrow;

        inline const std::unordered_map<std::string, sf::Cursor&> Names =
        {
            {"Arrow",               tb::Cursors::Arrow},
        };
    }

    enum class SpriteFlag : uint8_t
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

    inline constexpr auto SpriteFlagEntries = magic_enum::enum_entries<SpriteFlag>();

    using SpriteFlagBitset = std::bitset<magic_enum::enum_count<SpriteFlag>()>;

    namespace ZAxis
    {
        enum : ZAxis_t
        {
            Min     = 0,
            Default = 7,
            Max     = 15,
        };
    }

    namespace OutfitIndex
    {
        enum : OutfitIndex_t
        {
            Head = 0,
            Body = 1,
            Legs = 2,
            Feet = 3,
        };
    }

    enum class GameState : uint8_t
    {
        Loading,
        EnterGame,
        MapSelect,
        InGame,
        Paused,
    };

    enum class TimeOfDay : uint8_t
    {
        Day,
        Night,
    };

    enum class Direction : uint8_t
    {
        Up,
        Right,
        Down,
        Left,
        UpLeft,
        UpRight,
        DownLeft,
        DownRight,
    };

    enum class Vocation : uint8_t
    {
        None,
        Knight,
        Paladin,
        Druid,
        Sorcerer,
    };

    enum class BloodType : uint8_t
    {
        None,
        Red,
        Green,
    };

    enum class ThingType : uint8_t
    {
        Null,
        Creature,
        Object,
        Entity,
    };

    enum class DrawOrderType : uint8_t
    {
        First,
        TileEdge,
        Decal,
        Default,
        Last,
    };

    enum class PatternType : uint8_t
    {
        Tile,
        Object,
    };

    enum class TileMapType : uint8_t
    {
        Tiles,
        TileEdges,
    };

    enum class MapObjectLayerType : uint8_t
    {
        Entities,
        Creatures,
        Objects,
        TileEdgeObjects,
    };

    enum class ObjectType : uint8_t
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

    enum class WeaponType : uint8_t
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

    enum class EquipmentSlot : uint8_t
    {
        Bag, // bag or backpack
        Neck, // amulets
        Head,
        Chest,
        Legs,
        Feet,
        LeftHand,
        RightHand, // shields
        TwoHand,
    };
}
