#pragma once

#include "common.h"

namespace tb
{

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
