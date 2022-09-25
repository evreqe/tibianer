#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

namespace tb
{
    using ZAxis_t = uint8_t;
    using OutfitIndex_t = uint8_t;
    using SpriteID_t = uint16_t;

    using SpriteIDList = std::vector<SpriteID_t>;

    namespace Constants
    {
        const std::string GameTitle = "Tibianer";

        const std::string PlayerNameDefault = "Avatar";

        const float MenuBarHeight = 19.0f;
        const float StatusBarHeight = 19.0f;

        const uint32_t NumSprites = 4096; // 2048x2048

        const uint32_t NumWaterAnimationFrames = 16;

        const uint32_t NumWaterSpritesPerAnimationFrame = 8;

        const sf::Time WaterAnimationFrameTime = sf::seconds(0.5f);

        const uint32_t WaterPatternWidth = 4;
        const uint32_t WaterPatternHeight = 2;

        const uint32_t NumOutfitSpriteIndex = 4; // head, body, legs, feet

        const uint32_t NumOutfitSpriteDirections = 4; // up, right, down, left

        const SpriteID_t SpriteIDNull = 0;
        const SpriteID_t SpriteIDDefault = 1;

        const uint32_t TileSize = 32;
        const uint32_t TileSizeHalf = 16;
        const float TileSizeFloat = 32.0f;
        const float TileSizeHalfFloat = 16.0f;

        const uint32_t NumZAxis = 16;

        const uint32_t GameWindowTileWidth  = 13;    // number of tiles visible on the x-axis
        const uint32_t GameWindowTileHeight = 9;     // number of tiles visible on the y-axis

        const uint32_t GameWindowNumTilesFromCenterX = 6;    // number of tiles visible to the west or east of the player on the x-axis
        const uint32_t GameWindowNumTilesFromCenterY = 4;    // number of tiles visible to the north or south of the player on the y-axis

        const uint32_t GameWindowNumTilesVisible = GameWindowTileWidth * GameWindowTileHeight; // number of tiles visible in the game window

        const uint32_t GameWindowNumTilesToDrawFromOffscreen = 1; // need to draw some tiles that are not visible in order to account for large objects that take up 4 tiles

        const uint32_t GameWindowPixelWidth  = GameWindowTileWidth  * TileSize;    // number of pixels visible on the x-axis
        const uint32_t GameWindowPixelHeight = GameWindowTileHeight * TileSize;    // number of pixels visible on the y-axis

        const uint32_t GameWindowNumPixelsVisible = GameWindowPixelWidth * GameWindowPixelHeight; // number of pixels visible in the game window

        const uint32_t TileHeightMovementDifference = 2; // player cannot move to a tile if it has vertical objects stacked 2 axis higher than the player

        const uint32_t TileHeightMax = 5; // highest you can stack vertical objects on a tile, like chairs or parcels

        const uint32_t TileHeightClimbDifference = 3; // height needed to climb up or down a z-axis level using stacked vertical objects, like going from the ground to the roof of a house

        const uint32_t SkillLevelDefault = 10;
    }

    namespace Variables
    {
        //inline uint32_t MapTileWidth = 128;
        //inline uint32_t MapTileHeight = 128;

        //inline uint32_t MapNumTiles = 16384;

        //inline uint32_t MapPixelWidth = 4096;
        //inline uint32_t MapPixelHeight = 4096;

        //inline uint32_t MapNumPixels = 16777216;
    }

    namespace Textures
    {
        inline sf::Texture Loading;
        inline sf::Texture EnterGame;
        inline sf::Texture JourneyOnward;
        inline sf::Texture MapSelect;
        inline sf::Texture Sprites;
        inline sf::Texture GUI;
        inline sf::Texture Lights;
        inline sf::Texture Light;
        inline sf::Texture InGame;
        inline sf::Texture InGame2;
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
            {"images/loading.png",             tb::Textures::Loading},
            {"images/enter_game.png",          tb::Textures::EnterGame},
            {"images/journey_onward.png",      tb::Textures::JourneyOnward},
            {"images/map_select.png",          tb::Textures::MapSelect},
            {"images/sprites.png",             tb::Textures::Sprites},
            {"images/gui.png",                 tb::Textures::GUI},
            {"images/lights.png",              tb::Textures::Lights},
            {"images/light.png",               tb::Textures::Light},
            {"images/in_game.png",             tb::Textures::InGame},
            {"images/in_game2.png",            tb::Textures::InGame2},
            {"images/scroll.png",              tb::Textures::Scroll},
            {"images/wood.png",                tb::Textures::Wood},
            {"images/wood_horizontal1.png",    tb::Textures::WoodHorizontal1},
            {"images/wood_horizontal2.png",    tb::Textures::WoodHorizontal2},
            {"images/wood_vertical1.png",      tb::Textures::WoodVertical1},
            {"images/wood_vertical2.png",      tb::Textures::WoodVertical2},
        };
    }

    namespace Fonts
    {
        namespace Default
        {
            const std::string FileName = "fonts/OpenSans.ttf";
        }

        namespace Console
        {
            const std::string FileName = "fonts/Inconsolata.ttf";
        }

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

            const sf::Vector2u GlyphSize(18, 19);

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

            const sf::Vector2u GlyphSize(7, 10);

            // 16x6
            const std::vector<unsigned int> GlyphWidthList =
            {
                4, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 6, 3, 7,
                6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 7, 7, 7, 7,
                7, 6, 6, 6, 6, 6, 6, 6, 6, 3, 6, 7, 6, 7, 7, 6,
                6, 7, 6, 6, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                7, 6, 6, 6, 6, 6, 6, 6, 6, 3, 6, 7, 6, 7, 7, 6,
                6, 7, 6, 6, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            };
        }

        namespace Modern
        {
            const std::string FileName = "images/font_modern.png";

            const sf::Vector2u GlyphSize(16, 12);

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

    namespace SpriteFlags
    {
        enum : uint8_t
        {
            Null,
            Solid,
            BlockProjectiles,
            BlockPathFinding,
            Move,
            PickUp,
            Rotate,
            Hang,
            Use,
            UseOnTarget,
            Read,
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

            NumFlags,
        };
    }

    using SpriteFlags_t = std::bitset<tb::SpriteFlags::NumFlags>;

    namespace KeyValues
    {
        const std::map<std::string, uint32_t> SpriteFlags =
        {
            {"Null",                tb::SpriteFlags::Null},
            {"Solid",               tb::SpriteFlags::Solid},
            {"BlockProjectiles",    tb::SpriteFlags::BlockProjectiles},
            {"BlockPathFinding",    tb::SpriteFlags::BlockPathFinding},
            {"Move",                tb::SpriteFlags::Move},
            {"PickUp",              tb::SpriteFlags::PickUp},
            {"Rotate",              tb::SpriteFlags::Rotate},
            {"Hang",                tb::SpriteFlags::Hang},
            {"Use",                 tb::SpriteFlags::Use},
            {"UseOnTarget",         tb::SpriteFlags::UseOnTarget},
            {"Read",                tb::SpriteFlags::Read},
            {"MoveAbove",           tb::SpriteFlags::MoveAbove},
            {"MoveBelow",           tb::SpriteFlags::MoveBelow},
            {"Water",               tb::SpriteFlags::Water},
            {"Lava",                tb::SpriteFlags::Lava},
            {"Oil",                 tb::SpriteFlags::Oil},
            {"Decal",               tb::SpriteFlags::Decal},
            {"TileEdge",            tb::SpriteFlags::TileEdge},
            {"StepTile",            tb::SpriteFlags::StepTile},
            {"Animated",            tb::SpriteFlags::Animated},
            {"Creature",            tb::SpriteFlags::Creature},
            {"Corpse",              tb::SpriteFlags::Corpse},
            {"Container",           tb::SpriteFlags::Container},
            {"LightSource",         tb::SpriteFlags::LightSource},
            {"Offset",              tb::SpriteFlags::Offset},
            {"Height",              tb::SpriteFlags::Height},
            {"IgnoreHeight",        tb::SpriteFlags::IgnoreHeight},
            {"Stack",               tb::SpriteFlags::Stack},
            {"NoDraw",              tb::SpriteFlags::NoDraw},
            {"DrawFirst",           tb::SpriteFlags::DrawFirst},
            {"DrawLast",            tb::SpriteFlags::DrawLast},
        };
    }

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
        JourneyOnward,
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

    namespace KeyValues
    {
        const std::map<std::string, tb::ObjectType> ObjectType =
        {
            {"Null",               tb::ObjectType::Null},
            {"ChangeMap",          tb::ObjectType::ChangeMap},
            {"Container",          tb::ObjectType::Container},
            {"Sign",               tb::ObjectType::Sign},
            {"Book",               tb::ObjectType::Book},
            {"Key",                tb::ObjectType::Key},
            {"Teleporter",         tb::ObjectType::Teleporter},
            {"Door",               tb::ObjectType::Door},
            {"Bed",                tb::ObjectType::Bed},
            {"Lever",              tb::ObjectType::Lever},
            {"StepTile",           tb::ObjectType::StepTile},
            {"Creature",           tb::ObjectType::Creature},
        };
    }

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

    namespace KeyValues
    {
        const std::map<std::string, tb::EquipmentSlot> EquipmentSlot =
        {
            {"Bag",          tb::EquipmentSlot::Bag},
            {"Neck",         tb::EquipmentSlot::Neck},
            {"Head",         tb::EquipmentSlot::Head},
            {"Chest",        tb::EquipmentSlot::Chest},
            {"Legs",         tb::EquipmentSlot::Legs},
            {"Feet",         tb::EquipmentSlot::Feet},
            {"LeftHand",     tb::EquipmentSlot::LeftHand},
            {"RightHand",    tb::EquipmentSlot::RightHand},
        };
    }
}
