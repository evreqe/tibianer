#pragma once

#include "common.h"

namespace tb
{
    using ZAxis_t = uint8_t;
    using LightBrightness_t = uint8_t;
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

        inline const float PaddingBackgroundTexture = 7.0f;
        inline const float PaddingRenderWindow = 5.0f;
        inline const float PaddingWoodBorder = 3.0f;
        inline const float PaddingBlackRectangle = 1.0f;

        inline const uint32_t NumZAxis = 16;

        inline const uint32_t TileHeightMovementDifference = 2; // player cannot move to a tile if it has vertical objects stacked 2 axis higher than the player
        inline const uint32_t TileHeightMax = 5; // highest you can stack vertical objects on a tile, like chairs or parcels
        inline const uint32_t TileHeightClimbDifference = 3; // height needed to climb up or down a z-axis level using stacked vertical objects, like going from the ground to the roof of a house

        inline const uint32_t SkillLevelDefault = 10;

        namespace MyImGui
        {
            inline const uint8_t InputScalarU8StepOne = 1;
            inline const uint16_t InputScalarU16StepOne = 1;
            inline const uint32_t InputScalarU32StepOne = 1;
            inline const uint64_t InputScalarU64StepOne = 1;

            inline const ImVec2 PopupButtonSize(105.0f, 29.0f);
        }
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
            {"Introduction",            tb::Textures::Introduction},
            {"EnterGame",               tb::Textures::EnterGame},
            {"NewGameJourneyOnward",    tb::Textures::NewGameJourneyOnward},
            {"MapSelect",               tb::Textures::MapSelect},
            {"Loading",                 tb::Textures::Loading},
            {"MapEditor",               tb::Textures::MapEditor},
            {"Sprites",                 tb::Textures::Sprites},
            {"GUI",                     tb::Textures::GUI},
            {"Scroll",                  tb::Textures::Scroll},
            {"Wood",                    tb::Textures::Wood},
            {"WoodHorizontal1",         tb::Textures::WoodHorizontal1},
            {"WoodHorizontal2",         tb::Textures::WoodHorizontal2},
            {"WoodVertical1",           tb::Textures::WoodVertical1},
            {"WoodVertical2",           tb::Textures::WoodVertical2},
        };
    }

    namespace Fonts
    {
        inline sf::Font Arial;
        inline sf::Font CourierNew;
        inline sf::Font Helvetica;
        inline sf::Font MarcoPolo;
        inline sf::Font Martel;
        inline sf::Font Roboto;
        inline sf::Font Supernatural1001;
        inline sf::Font Supernatural1002;
        inline sf::Font System;
        inline sf::Font TimesNewRoman;
        inline sf::Font Verdana;

        inline const std::unordered_map<std::string, sf::Font&> Names =
        {
            {"Arial",               tb::Fonts::Arial},
            {"CourierNew",          tb::Fonts::CourierNew},
            {"Helvetica",           tb::Fonts::Helvetica},
            {"MarcoPolo",           tb::Fonts::MarcoPolo},
            {"Martel",              tb::Fonts::Martel},
            {"Roboto",              tb::Fonts::Roboto},
            {"Supernatural1001",    tb::Fonts::Supernatural1001},
            {"Supernatural1002",    tb::Fonts::Supernatural1002},
            {"System",              tb::Fonts::System},
            {"TimesNewRoman",       tb::Fonts::TimesNewRoman},
            {"Verdana",             tb::Fonts::Verdana},
        };
    }

    namespace Cursors
    {
        // system
        inline sf::Cursor Arrow;
        inline sf::Cursor ArrowWait;
        inline sf::Cursor Wait;
        inline sf::Cursor Text;
        inline sf::Cursor Hand;
        inline sf::Cursor SizeHorizontal;
        inline sf::Cursor SizeVertical;
        inline sf::Cursor SizeTopLeftBottomRight;
        inline sf::Cursor SizeBottomLeftTopRight;
        inline sf::Cursor SizeAll;
        inline sf::Cursor Cross;
        inline sf::Cursor Help;
        inline sf::Cursor NotAllowed;

        // custom
        inline sf::Cursor Crosshair;
        inline sf::Cursor CrosshairModern;
        inline sf::Cursor Drag;
        inline sf::Cursor Inspect;
        inline sf::Cursor Sword;

        inline const std::unordered_map<std::string, sf::Cursor&> SystemCursorNames =
        {
            {"Arrow",                     tb::Cursors::Arrow},
            {"ArrowWait",                 tb::Cursors::ArrowWait},
            {"Wait",                      tb::Cursors::Wait},
            {"Text",                      tb::Cursors::Text},
            {"Hand",                      tb::Cursors::Hand},
            {"SizeHorizontal",            tb::Cursors::SizeHorizontal},
            {"SizeVertical",              tb::Cursors::SizeVertical},
            {"SizeTopLeftBottomRight",    tb::Cursors::SizeTopLeftBottomRight},
            {"SizeBottomLeftTopRight",    tb::Cursors::SizeBottomLeftTopRight},
            {"SizeAll",                   tb::Cursors::SizeAll},
            {"Cross",                     tb::Cursors::Cross},
            {"Help",                      tb::Cursors::Help},
            {"NotAllowed",                tb::Cursors::NotAllowed},
        };

        inline const std::unordered_map<sf::Cursor::Type, sf::Cursor&> SystemCursorTypes =
        {
            {sf::Cursor::Arrow,                     tb::Cursors::Arrow},
            {sf::Cursor::ArrowWait,                 tb::Cursors::ArrowWait},
            {sf::Cursor::Wait,                      tb::Cursors::Wait},
            {sf::Cursor::Text,                      tb::Cursors::Text},
            {sf::Cursor::Hand,                      tb::Cursors::Hand},
            {sf::Cursor::SizeHorizontal,            tb::Cursors::SizeHorizontal},
            {sf::Cursor::SizeVertical,              tb::Cursors::SizeVertical},
            {sf::Cursor::SizeTopLeftBottomRight,    tb::Cursors::SizeTopLeftBottomRight},
            {sf::Cursor::SizeBottomLeftTopRight,    tb::Cursors::SizeBottomLeftTopRight},
            {sf::Cursor::SizeAll,                   tb::Cursors::SizeAll},
            {sf::Cursor::Cross,                     tb::Cursors::Cross},
            {sf::Cursor::Help,                      tb::Cursors::Help},
            {sf::Cursor::NotAllowed,                tb::Cursors::NotAllowed},
        };

        inline const std::unordered_map<std::string, sf::Cursor&> CustomCursorNames =
        {
            {"Crosshair",                 tb::Cursors::Crosshair},
            {"CrosshairModern",           tb::Cursors::CrosshairModern},
            {"Drag",                      tb::Cursors::Drag},
            {"Inspect",                   tb::Cursors::Inspect},
            {"Sword",                     tb::Cursors::Sword},
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

    namespace LightBrightness
    {
        enum : LightBrightness_t
        {
            Min         = 0,
            UnderGround = 32,
            Max         = 255,
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
        EnterGame,
        NewGameJourneyOnward,
        MapSelect,
        LoadingMap,
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
    };

    enum class MovementDirection : uint8_t
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
