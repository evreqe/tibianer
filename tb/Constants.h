#pragma once

#include "common.h"

namespace tb
{
    using ZAxis_t = std::uint8_t;
    using LightBrightness_t = std::uint8_t;
    using OutfitIndex_t = std::uint8_t;
    using SpriteID_t = std::uint16_t;

    using SpriteIDList = std::vector<tb::SpriteID_t>;

    struct VisibleZ_t
    {
        tb::ZAxis_t Begin;
        tb::ZAxis_t End;
    };

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

        inline const tb::SpriteID_t SpriteIDNull = 0;
        inline const tb::SpriteID_t SpriteIDDefault = 1;

        inline const float SpriteSizeAsFloat = 32.0f;

        inline const std::uint32_t TileSize = 32;
        inline const std::uint32_t TileSizeHalf = 16;
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

        inline const std::uint32_t TileHeightMovementDifference = 2; // player cannot move to a tile if it has vertical objects stacked 2 axis higher than the player
        inline const std::uint32_t TileHeightMax = 5; // highest you can stack vertical objects on a tile, like chairs or parcels
        inline const std::uint32_t TileHeightClimbDifference = 3; // height needed to climb up or down a z-axis level using stacked vertical objects, like going from the ground to the roof of a house

        inline const std::uint32_t SkillLevelDefault = 10;

        namespace BitmapFonts
        {
            inline const std::uint32_t NumGlyphs = 256; // ASCII codes
        }

        namespace LibImGui
        {
            inline const std::uint8_t InputScalarU8StepOne = 1;
            inline const std::uint16_t InputScalarU16StepOne = 1;
            inline const std::uint32_t InputScalarU32StepOne = 1;
            inline const std::uint64_t InputScalarU64StepOne = 1;

            inline const ImVec2 PopupButtonSize(105.0f, 29.0f);
        }
    }

    namespace Textures
    {
        inline sf::Texture Introduction("textures/introduction.png");
        inline sf::Texture EnterGame("textures/enter_game.png");
        inline sf::Texture NewGameJourneyOnward("textures/new_game_journey_onward.png");
        inline sf::Texture MapSelect("textures/map_select.png");
        inline sf::Texture Loading("textures/loading.png");
        inline sf::Texture TiledLogo("textures/tiled_logo.png");
        inline sf::Texture SFMLLogo("textures/sfml_logo.png");
        inline sf::Texture Sprites("textures/sprites.png");
        inline sf::Texture GUI("textures/gui.png");
        inline sf::Texture Scroll("textures/scroll.png");
        inline sf::Texture Wood("textures/wood.png");
        inline sf::Texture WoodHorizontal("textures/wood_horizontal.png");
        inline sf::Texture WoodHorizontal2("textures/wood_horizontal_2.png");
        inline sf::Texture WoodVertical("textures/wood_vertical.png");
        inline sf::Texture WoodVertical2("textures/wood_vertical_2.png");
        inline sf::Texture Water("textures/water.png");
        inline sf::Texture Null("textures/null.png");

        inline const std::unordered_map<std::string, sf::Texture&> Names =
        {
            {"Introduction",            tb::Textures::Introduction},
            {"EnterGame",               tb::Textures::EnterGame},
            {"NewGameJourneyOnward",    tb::Textures::NewGameJourneyOnward},
            {"MapSelect",               tb::Textures::MapSelect},
            {"Loading",                 tb::Textures::Loading},
            {"TiledLogo",               tb::Textures::TiledLogo},
            {"SFMLLogo",                tb::Textures::SFMLLogo},
            {"Sprites",                 tb::Textures::Sprites},
            {"GUI",                     tb::Textures::GUI},
            {"Scroll",                  tb::Textures::Scroll},
            {"Wood",                    tb::Textures::Wood},
            {"WoodHorizontal",          tb::Textures::WoodHorizontal},
            {"WoodHorizontal2",         tb::Textures::WoodHorizontal2},
            {"WoodVertical",            tb::Textures::WoodVertical},
            {"WoodVertical2",           tb::Textures::WoodVertical2},
            {"Water",                   tb::Textures::Water},
            {"Null",                    tb::Textures::Null},
        };
    }

    namespace Fonts
    {
        inline sf::Font MarcoPolo;
        inline sf::Font Martel;
        inline sf::Font Supernatural1001;
        inline sf::Font Supernatural1002;
        inline sf::Font System;
        inline sf::Font SystemFixed;

        inline const std::unordered_map<std::string, sf::Font&> Names =
        {
            {"MarcoPolo",           tb::Fonts::MarcoPolo},
            {"Martel",              tb::Fonts::Martel},
            {"Supernatural1001",    tb::Fonts::Supernatural1001},
            {"Supernatural1002",    tb::Fonts::Supernatural1002},
            {"System",              tb::Fonts::System},
            {"SystemFixed",         tb::Fonts::SystemFixed},
        };

        namespace CharacterSize
        {
            inline std::uint32_t System = 13;
            inline std::uint32_t SystemFixed = 16;
        }
    }

    namespace Cursors
    {
        // system
        inline sf::Cursor Arrow(sf::Cursor::Type::Arrow);
        inline sf::Cursor ArrowWait(sf::Cursor::Type::ArrowWait);
        inline sf::Cursor Wait(sf::Cursor::Type::Wait);
        inline sf::Cursor Text(sf::Cursor::Type::Text);
        inline sf::Cursor Hand(sf::Cursor::Type::Hand);
        inline sf::Cursor SizeHorizontal(sf::Cursor::Type::SizeHorizontal);
        inline sf::Cursor SizeVertical(sf::Cursor::Type::SizeVertical);
        inline sf::Cursor SizeTopLeftBottomRight(sf::Cursor::Type::SizeTopLeftBottomRight);
        inline sf::Cursor SizeBottomLeftTopRight(sf::Cursor::Type::SizeBottomLeftTopRight);
        inline sf::Cursor SizeAll(sf::Cursor::Type::SizeAll);
        inline sf::Cursor Cross(sf::Cursor::Type::Cross);
        inline sf::Cursor Help(sf::Cursor::Type::Help);
        inline sf::Cursor NotAllowed(sf::Cursor::Type::NotAllowed);

        // custom
        inline sf::Cursor Crosshair(sf::Cursor::Type::Cross);
        inline sf::Cursor CrosshairModern(sf::Cursor::Type::Cross);
        inline sf::Cursor Drag(sf::Cursor::Type::Hand);
        inline sf::Cursor Inspect(sf::Cursor::Type::Help);
        inline sf::Cursor Sword(sf::Cursor::Type::Arrow);

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
            {sf::Cursor::Type::Arrow,                     tb::Cursors::Arrow},
            {sf::Cursor::Type::ArrowWait,                 tb::Cursors::ArrowWait},
            {sf::Cursor::Type::Wait,                      tb::Cursors::Wait},
            {sf::Cursor::Type::Text,                      tb::Cursors::Text},
            {sf::Cursor::Type::Hand,                      tb::Cursors::Hand},
            {sf::Cursor::Type::SizeHorizontal,            tb::Cursors::SizeHorizontal},
            {sf::Cursor::Type::SizeVertical,              tb::Cursors::SizeVertical},
            {sf::Cursor::Type::SizeTopLeftBottomRight,    tb::Cursors::SizeTopLeftBottomRight},
            {sf::Cursor::Type::SizeBottomLeftTopRight,    tb::Cursors::SizeBottomLeftTopRight},
            {sf::Cursor::Type::SizeAll,                   tb::Cursors::SizeAll},
            {sf::Cursor::Type::Cross,                     tb::Cursors::Cross},
            {sf::Cursor::Type::Help,                      tb::Cursors::Help},
            {sf::Cursor::Type::NotAllowed,                tb::Cursors::NotAllowed},
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

    namespace Sprites
    {
        inline SpriteID_t TileHighlight;
        inline SpriteID_t TbIconSmall;
        inline SpriteID_t TbIconLarge;
        inline SpriteID_t Evremonde;
        inline SpriteID_t Grass;
        inline SpriteID_t Water;

        inline const std::unordered_map<std::string, SpriteID_t&> Names =
        {
            {"TileHighlight",          tb::Sprites::TileHighlight},
            {"TbIconSmall",            tb::Sprites::TbIconSmall},
            {"TbIconLarge",            tb::Sprites::TbIconLarge},
            {"Evremonde",              tb::Sprites::Evremonde},
            {"Grass",                  tb::Sprites::Grass},
            {"Water",                  tb::Sprites::Water},
        };
    }

    namespace Animations
    {
        inline std::uint32_t BlueOrbSpell;

        inline const std::unordered_map<std::string, std::uint32_t&> Names =
        {
            {"BlueOrbSpell",            tb::Animations::BlueOrbSpell},
        };
    }

    namespace GuiRects
    {
        inline sf::IntRect EquipmentWindow;
        inline sf::IntRect StatusWindow;

        inline sf::IntRect TabButtonsWindowInventoryButtonReleased;
        inline sf::IntRect TabButtonsWindowInventoryButtonPressed;
        inline sf::IntRect TabButtonsWindowStatusButtonReleased;
        inline sf::IntRect TabButtonsWindowStatusButtonPressed;
        inline sf::IntRect TabButtonsWindowBattleButtonReleased;
        inline sf::IntRect TabButtonsWindowBattleButtonPressed;
        inline sf::IntRect TabButtonsWindowMiniMapButtonReleased;
        inline sf::IntRect TabButtonsWindowMiniMapButtonPressed;

        inline sf::IntRect BattleButtonsWindowFullAttackButtonReleased;
        inline sf::IntRect BattleButtonsWindowFullAttackButtonPressed;
        inline sf::IntRect BattleButtonsWindowHalfAttackHalfDefenseButtonReleased;
        inline sf::IntRect BattleButtonsWindowHalfAttackHalfDefenseButtonPressed;
        inline sf::IntRect BattleButtonsWindowFullDefenseButtonReleased;
        inline sf::IntRect BattleButtonsWindowFullDefenseButtonPressed;
        inline sf::IntRect BattleButtonsWindowFollowButtonReleased;
        inline sf::IntRect BattleButtonsWindowFollowButtonPressed;
        inline sf::IntRect BattleButtonsWindowFollowDistanceButtonReleased;
        inline sf::IntRect BattleButtonsWindowFollowDistanceButtonPressed;
        inline sf::IntRect BattleButtonsWindowDoNotFollowButtonReleased;
        inline sf::IntRect BattleButtonsWindowDoNotFollowButtonPressed;

        inline sf::IntRect UpArrowButtonDisabled;
        inline sf::IntRect UpArrowButtonEnabled;
        inline sf::IntRect DownArrowButtonDisabled;
        inline sf::IntRect DownArrowButtonEnabled;
        inline sf::IntRect LeftArrowButtonDisabled;
        inline sf::IntRect LeftArrowButtonEnabled;
        inline sf::IntRect RightArrowButtonEnabled;
        inline sf::IntRect RightArrowButtonDisabled;

        inline sf::IntRect GraySquare;
        inline sf::IntRect RedSquare;

        inline const std::unordered_map<std::string, sf::IntRect&> Names =
        {
            {"EquipmentWindow",                                           tb::GuiRects::EquipmentWindow},
            {"StatusWindow",                                              tb::GuiRects::StatusWindow},

            {"TabButtonsWindowInventoryButtonReleased",                   tb::GuiRects::TabButtonsWindowInventoryButtonReleased},
            {"TabButtonsWindowInventoryButtonPressed",                    tb::GuiRects::TabButtonsWindowInventoryButtonPressed},
            {"TabButtonsWindowStatusButtonReleased",                      tb::GuiRects::TabButtonsWindowStatusButtonReleased},
            {"TabButtonsWindowStatusButtonPressed",                       tb::GuiRects::TabButtonsWindowStatusButtonPressed},
            {"TabButtonsWindowBattleButtonReleased",                      tb::GuiRects::TabButtonsWindowBattleButtonReleased},
            {"TabButtonsWindowBattleButtonPressed",                       tb::GuiRects::TabButtonsWindowBattleButtonPressed},
            {"TabButtonsWindowMiniMapButtonReleased",                     tb::GuiRects::TabButtonsWindowMiniMapButtonReleased},
            {"TabButtonsWindowMiniMapButtonPressed",                      tb::GuiRects::TabButtonsWindowMiniMapButtonPressed},

            {"BattleButtonsWindowFullAttackButtonReleased",               tb::GuiRects::BattleButtonsWindowFullAttackButtonReleased},
            {"BattleButtonsWindowFullAttackButtonPressed",                tb::GuiRects::BattleButtonsWindowFullAttackButtonPressed},
            {"BattleButtonsWindowHalfAttackHalfDefenseButtonReleased",    tb::GuiRects::BattleButtonsWindowHalfAttackHalfDefenseButtonReleased},
            {"BattleButtonsWindowHalfAttackHalfDefenseButtonPressed",     tb::GuiRects::BattleButtonsWindowHalfAttackHalfDefenseButtonPressed},
            {"BattleButtonsWindowFullDefenseButtonReleased",              tb::GuiRects::BattleButtonsWindowFullDefenseButtonReleased},
            {"BattleButtonsWindowFullDefenseButtonPressed",               tb::GuiRects::BattleButtonsWindowFullDefenseButtonPressed},
            {"BattleButtonsWindowFollowButtonReleased",                   tb::GuiRects::BattleButtonsWindowFollowButtonReleased},
            {"BattleButtonsWindowFollowButtonPressed",                    tb::GuiRects::BattleButtonsWindowFollowButtonPressed},
            {"BattleButtonsWindowFollowDistanceButtonReleased",           tb::GuiRects::BattleButtonsWindowFollowDistanceButtonReleased},
            {"BattleButtonsWindowFollowDistanceButtonPressed",            tb::GuiRects::BattleButtonsWindowFollowDistanceButtonPressed},
            {"BattleButtonsWindowDoNotFollowButtonReleased",              tb::GuiRects::BattleButtonsWindowDoNotFollowButtonReleased},
            {"BattleButtonsWindowDoNotFollowButtonPressed",               tb::GuiRects::BattleButtonsWindowDoNotFollowButtonPressed},

            {"UpArrowButtonDisabled",                                     tb::GuiRects::UpArrowButtonDisabled},
            {"UpArrowButtonEnabled",                                      tb::GuiRects::UpArrowButtonEnabled},
            {"DownArrowButtonDisabled",                                   tb::GuiRects::DownArrowButtonDisabled},
            {"DownArrowButtonEnabled",                                    tb::GuiRects::DownArrowButtonEnabled},
            {"LeftArrowButtonDisabled",                                   tb::GuiRects::LeftArrowButtonDisabled},
            {"LeftArrowButtonEnabled",                                    tb::GuiRects::LeftArrowButtonEnabled},
            {"RightArrowButtonEnabled",                                   tb::GuiRects::RightArrowButtonEnabled},
            {"RightArrowButtonDisabled",                                  tb::GuiRects::RightArrowButtonDisabled},

            {"GraySquare",                                                tb::GuiRects::GraySquare},
            {"RedSquare",                                                 tb::GuiRects::RedSquare},

            {"TabButtonsWindowInventoryButtonReleased",                   tb::GuiRects::TabButtonsWindowInventoryButtonReleased},
            {"TabButtonsWindowInventoryButtonPressed",                    tb::GuiRects::TabButtonsWindowInventoryButtonPressed},
            {"TabButtonsWindowStatusButtonReleased",                      tb::GuiRects::TabButtonsWindowStatusButtonReleased},
            {"TabButtonsWindowStatusButtonPressed",                       tb::GuiRects::TabButtonsWindowStatusButtonPressed},
            {"TabButtonsWindowBattleButtonReleased",                      tb::GuiRects::TabButtonsWindowBattleButtonReleased},
            {"TabButtonsWindowBattleButtonPressed",                       tb::GuiRects::TabButtonsWindowBattleButtonPressed},
            {"TabButtonsWindowMiniMapButtonReleased",                     tb::GuiRects::TabButtonsWindowMiniMapButtonReleased},
            {"TabButtonsWindowMiniMapButtonPressed",                      tb::GuiRects::TabButtonsWindowMiniMapButtonPressed},
        };
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

    using SpriteFlagBitset = std::bitset<magic_enum::enum_count<tb::SpriteFlag>()>;

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
