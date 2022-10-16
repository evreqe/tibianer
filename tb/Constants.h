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

        inline const sf::Time WaterAnimationFrameTime = sf::seconds(0.5f);

        inline const uint32_t WaterPatternWidth = 4;
        inline const uint32_t WaterPatternHeight = 2;

        inline const uint32_t NumOutfitSpriteIndex = 4; // head, body, legs, feet
        inline const uint32_t NumOutfitSpriteDirections = 4; // up, right, down, left

        inline const SpriteID_t SpriteIDNull = 0;
        inline const SpriteID_t SpriteIDDefault = 1;

        inline const int TileSize = 32;
        inline const int TileSizeHalf = 16;
        inline const float TileSizeFloat = 32.0f;
        inline const float TileSizeHalfFloat = 16.0f;

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
        inline sf::Texture Lights;
        inline sf::Texture Scroll;
        inline sf::Texture Wood;
        inline sf::Texture WoodHorizontal1;
        inline sf::Texture WoodHorizontal2;
        inline sf::Texture WoodVertical1;
        inline sf::Texture WoodVertical2;
    }

    namespace KeyValues
    {
        const std::unordered_map<std::string, sf::Texture&> Textures =
        {
            {"images/introduction.png",               tb::Textures::Introduction},
            {"images/enter_game.png",                 tb::Textures::EnterGame},
            {"images/new_game_journey_onward.png",    tb::Textures::NewGameJourneyOnward},
            {"images/map_select.png",                 tb::Textures::MapSelect},
            {"images/loading.png",                    tb::Textures::Loading},
            {"images/sprites.png",                    tb::Textures::Sprites},
            {"images/gui.png",                        tb::Textures::GUI},
            {"images/lights.png",                     tb::Textures::Lights},
            {"images/scroll.png",                     tb::Textures::Scroll},
            {"images/wood.png",                       tb::Textures::Wood},
            {"images/wood_horizontal1.png",           tb::Textures::WoodHorizontal1},
            {"images/wood_horizontal2.png",           tb::Textures::WoodHorizontal2},
            {"images/wood_vertical1.png",             tb::Textures::WoodVertical1},
            {"images/wood_vertical2.png",             tb::Textures::WoodVertical2},
        };
    }

    namespace Fonts
    {
        namespace System
        {
            const std::string FileName = "fonts/System.ttf";

            const uint32_t CharacterSize = 13;
        }
    }

    namespace BitmapFonts
    {
        namespace Default
        {
            const std::string FileName = "images/font.png";

            const sf::Vector2u GlyphSize(32, 32);

            const float TextHeight = 19.0f;

            // 16x6
            const std::vector<unsigned int> GlyphWidthList =
            {
                6,  4,  8,  16, 9,  18, 15, 5,  7,  7,  9,  13, 5,  8,  4,  7,
                10, 8,  10, 10, 10, 9,  10, 10, 9,  10, 4,  5,  12, 14, 12, 9,
                14, 15, 13, 13, 14, 13, 12, 15, 15, 8,  9,  15, 13, 18, 15, 14,
                12, 14, 15, 11, 14, 15, 15, 18, 15, 15, 13, 15, 14, 15, 11, 13,
                4,  9,  11, 9,  11, 9,  10, 11, 11, 6,  7,  11, 6,  16, 11, 10,
                11, 11, 8,  8,  7,  11, 11, 15, 11, 12, 10, 9,  10, 11, 14, 11,
            };
        }

        namespace Tiny
        {
            const std::string FileName = "images/font_tiny.png";

            const sf::Vector2u GlyphSize(16, 16);

            const float TextHeight = 11.0f;

            // 16x6
            const std::vector<unsigned int> GlyphWidthList =
            {
                4, 3, 5, 7, 5, 7, 7, 4, 5, 5, 7, 5, 3, 6, 3, 6,
                6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 5, 6, 5, 6,
                7, 6, 6, 6, 6, 6, 6, 6, 6, 3, 6, 7, 6, 7, 7, 6,
                6, 7, 6, 6, 7, 6, 7, 7, 7, 7, 7, 4, 6, 4, 7, 6,
                9, 6, 6, 6, 6, 6, 6, 6, 6, 3, 6, 7, 6, 7, 7, 6,
                6, 7, 6, 6, 7, 6, 7, 7, 7, 7, 7, 5, 3, 5, 6, 7,
            };
        }

        namespace Modern
        {
            const std::string FileName = "images/font_modern.png";

            const sf::Vector2u GlyphSize(16, 16);

            const float TextHeight = 12.0f;

            // 16x6
            const std::vector<unsigned int> GlyphWidthList =
            {
                3,  4, 7, 9, 8,  10, 10, 4,  6, 6, 9, 9, 4, 9,  4,  8,
                8,  6, 8, 8, 8,  8,  8,  8,  8, 8, 4, 4, 9, 9,  9,  7,
                10, 9, 8, 8, 9,  8,  8,  9,  9, 6, 7, 8, 8, 10, 9,  9,
                8,  9, 9, 8, 10, 9,  8,  10, 8, 8, 8, 6, 8, 6,  10, 10,
                4,  8, 8, 7, 8,  8,  7,  8,  8, 4, 6, 8, 4, 10, 8,  8,
                8,  8, 7, 7, 7,  8,  8,  10, 8, 8, 7, 8, 4, 8,  9,  8,
            };
        }
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
