#pragma once

#include "common.h"

#include "Types.h"

namespace tb
{
    namespace Resources
    {
        namespace Textures
        {
            inline sf::Texture Introduction("textures/introduction.png");
            inline sf::Texture EnterGame("textures/enter_game.png");
            inline sf::Texture NewGameJourneyOnward("textures/new_game_journey_onward.png");
            inline sf::Texture MapSelect("textures/map_select.png");
            inline sf::Texture Loading("textures/loading.png");
            inline sf::Texture TiledLogo("textures/tiled_logo.png");
            inline sf::Texture SFMLLogo("textures/sfml_logo.png");
            inline sf::Texture SpriteSheet("textures/spritesheet.png");
            inline sf::Texture GUI("textures/gui.png");
            inline sf::Texture Scroll("textures/scroll.png");
            inline sf::Texture Wood("textures/wood.png");
            inline sf::Texture WoodHorizontal("textures/wood_horizontal.png");
            inline sf::Texture WoodHorizontal2("textures/wood_horizontal_2.png");
            inline sf::Texture WoodVertical("textures/wood_vertical.png");
            inline sf::Texture WoodVertical2("textures/wood_vertical_2.png");
            inline sf::Texture Water("textures/water.png");
            inline sf::Texture Null("textures/null.png");

            inline const std::unordered_map<std::string, sf::Texture&> NameTable =
            {
                {"Introduction",            tb::Resources::Textures::Introduction},
                {"EnterGame",               tb::Resources::Textures::EnterGame},
                {"NewGameJourneyOnward",    tb::Resources::Textures::NewGameJourneyOnward},
                {"MapSelect",               tb::Resources::Textures::MapSelect},
                {"Loading",                 tb::Resources::Textures::Loading},
                {"TiledLogo",               tb::Resources::Textures::TiledLogo},
                {"SFMLLogo",                tb::Resources::Textures::SFMLLogo},
                {"SpriteSheet",             tb::Resources::Textures::SpriteSheet},
                {"GUI",                     tb::Resources::Textures::GUI},
                {"Scroll",                  tb::Resources::Textures::Scroll},
                {"Wood",                    tb::Resources::Textures::Wood},
                {"WoodHorizontal",          tb::Resources::Textures::WoodHorizontal},
                {"WoodHorizontal2",         tb::Resources::Textures::WoodHorizontal2},
                {"WoodVertical",            tb::Resources::Textures::WoodVertical},
                {"WoodVertical2",           tb::Resources::Textures::WoodVertical2},
                {"Water",                   tb::Resources::Textures::Water},
                {"Null",                    tb::Resources::Textures::Null},
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

            inline const std::unordered_map<std::string, sf::Font&> NameTable =
            {
                {"MarcoPolo",           tb::Resources::Fonts::MarcoPolo},
                {"Martel",              tb::Resources::Fonts::Martel},
                {"Supernatural1001",    tb::Resources::Fonts::Supernatural1001},
                {"Supernatural1002",    tb::Resources::Fonts::Supernatural1002},
                {"System",              tb::Resources::Fonts::System},
                {"SystemFixed",         tb::Resources::Fonts::SystemFixed},
            };

            namespace CharacterSize
            {
                inline std::uint32_t System = 13;
                inline std::uint32_t SystemFixed = 16;
            }
        }

        namespace Cursors
        {
            namespace System
            {
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

                inline const std::unordered_map<std::string, sf::Cursor&> NameTable =
                {
                    {"Arrow",                     tb::Resources::Cursors::System::Arrow},
                    {"ArrowWait",                 tb::Resources::Cursors::System::ArrowWait},
                    {"Wait",                      tb::Resources::Cursors::System::Wait},
                    {"Text",                      tb::Resources::Cursors::System::Text},
                    {"Hand",                      tb::Resources::Cursors::System::Hand},
                    {"SizeHorizontal",            tb::Resources::Cursors::System::SizeHorizontal},
                    {"SizeVertical",              tb::Resources::Cursors::System::SizeVertical},
                    {"SizeTopLeftBottomRight",    tb::Resources::Cursors::System::SizeTopLeftBottomRight},
                    {"SizeBottomLeftTopRight",    tb::Resources::Cursors::System::SizeBottomLeftTopRight},
                    {"SizeAll",                   tb::Resources::Cursors::System::SizeAll},
                    {"Cross",                     tb::Resources::Cursors::System::Cross},
                    {"Help",                      tb::Resources::Cursors::System::Help},
                    {"NotAllowed",                tb::Resources::Cursors::System::NotAllowed},
                };

                inline const std::unordered_map<sf::Cursor::Type, sf::Cursor&> TypeTable =
                {
                    {sf::Cursor::Type::Arrow,                     tb::Resources::Cursors::System::Arrow},
                    {sf::Cursor::Type::ArrowWait,                 tb::Resources::Cursors::System::ArrowWait},
                    {sf::Cursor::Type::Wait,                      tb::Resources::Cursors::System::Wait},
                    {sf::Cursor::Type::Text,                      tb::Resources::Cursors::System::Text},
                    {sf::Cursor::Type::Hand,                      tb::Resources::Cursors::System::Hand},
                    {sf::Cursor::Type::SizeHorizontal,            tb::Resources::Cursors::System::SizeHorizontal},
                    {sf::Cursor::Type::SizeVertical,              tb::Resources::Cursors::System::SizeVertical},
                    {sf::Cursor::Type::SizeTopLeftBottomRight,    tb::Resources::Cursors::System::SizeTopLeftBottomRight},
                    {sf::Cursor::Type::SizeBottomLeftTopRight,    tb::Resources::Cursors::System::SizeBottomLeftTopRight},
                    {sf::Cursor::Type::SizeAll,                   tb::Resources::Cursors::System::SizeAll},
                    {sf::Cursor::Type::Cross,                     tb::Resources::Cursors::System::Cross},
                    {sf::Cursor::Type::Help,                      tb::Resources::Cursors::System::Help},
                    {sf::Cursor::Type::NotAllowed,                tb::Resources::Cursors::System::NotAllowed},
                };
            }

            namespace Custom
            {
                inline sf::Cursor Crosshair(sf::Cursor::Type::Arrow);
                inline sf::Cursor CrosshairModern(sf::Cursor::Type::Arrow);
                inline sf::Cursor Drag(sf::Cursor::Type::Arrow);
                inline sf::Cursor Inspect(sf::Cursor::Type::Arrow);
                inline sf::Cursor Sword(sf::Cursor::Type::Arrow);

                inline const std::unordered_map<std::string, sf::Cursor&> NameTable =
                {
                    {"Crosshair",                 tb::Resources::Cursors::Custom::Crosshair},
                    {"CrosshairModern",           tb::Resources::Cursors::Custom::CrosshairModern},
                    {"Drag",                      tb::Resources::Cursors::Custom::Drag},
                    {"Inspect",                   tb::Resources::Cursors::Custom::Inspect},
                    {"Sword",                     tb::Resources::Cursors::Custom::Sword},
                };
            }
        }

        namespace Sprites
        {
            inline tb::SpriteID TileHighlight = 0;
            inline tb::SpriteID TbIconSmall = 0;
            inline tb::SpriteID TbIconLarge = 0;
            inline tb::SpriteID Evremonde = 0;
            inline tb::SpriteID Grass = 0;
            inline tb::SpriteID Water = 0;

            inline const std::unordered_map<std::string, tb::SpriteID&> NameTable =
            {
                {"TileHighlight",          tb::Resources::Sprites::TileHighlight},
                {"TbIconSmall",            tb::Resources::Sprites::TbIconSmall},
                {"TbIconLarge",            tb::Resources::Sprites::TbIconLarge},
                {"Evremonde",              tb::Resources::Sprites::Evremonde},
                {"Grass",                  tb::Resources::Sprites::Grass},
                {"Water",                  tb::Resources::Sprites::Water},
            };
        }

        namespace Animations
        {
            inline std::uint32_t BlueOrbSpellEffect = 0;

            inline const std::unordered_map<std::string, std::uint32_t&> NameTable =
            {
                {"BlueOrbSpellEffect",        tb::Resources::Animations::BlueOrbSpellEffect},
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

            inline const std::unordered_map<std::string, sf::IntRect&> NameTable =
            {
                {"EquipmentWindow",                                           tb::Resources::GuiRects::EquipmentWindow},
                {"StatusWindow",                                              tb::Resources::GuiRects::StatusWindow},

                {"TabButtonsWindowInventoryButtonReleased",                   tb::Resources::GuiRects::TabButtonsWindowInventoryButtonReleased},
                {"TabButtonsWindowInventoryButtonPressed",                    tb::Resources::GuiRects::TabButtonsWindowInventoryButtonPressed},
                {"TabButtonsWindowStatusButtonReleased",                      tb::Resources::GuiRects::TabButtonsWindowStatusButtonReleased},
                {"TabButtonsWindowStatusButtonPressed",                       tb::Resources::GuiRects::TabButtonsWindowStatusButtonPressed},
                {"TabButtonsWindowBattleButtonReleased",                      tb::Resources::GuiRects::TabButtonsWindowBattleButtonReleased},
                {"TabButtonsWindowBattleButtonPressed",                       tb::Resources::GuiRects::TabButtonsWindowBattleButtonPressed},
                {"TabButtonsWindowMiniMapButtonReleased",                     tb::Resources::GuiRects::TabButtonsWindowMiniMapButtonReleased},
                {"TabButtonsWindowMiniMapButtonPressed",                      tb::Resources::GuiRects::TabButtonsWindowMiniMapButtonPressed},

                {"BattleButtonsWindowFullAttackButtonReleased",               tb::Resources::GuiRects::BattleButtonsWindowFullAttackButtonReleased},
                {"BattleButtonsWindowFullAttackButtonPressed",                tb::Resources::GuiRects::BattleButtonsWindowFullAttackButtonPressed},
                {"BattleButtonsWindowHalfAttackHalfDefenseButtonReleased",    tb::Resources::GuiRects::BattleButtonsWindowHalfAttackHalfDefenseButtonReleased},
                {"BattleButtonsWindowHalfAttackHalfDefenseButtonPressed",     tb::Resources::GuiRects::BattleButtonsWindowHalfAttackHalfDefenseButtonPressed},
                {"BattleButtonsWindowFullDefenseButtonReleased",              tb::Resources::GuiRects::BattleButtonsWindowFullDefenseButtonReleased},
                {"BattleButtonsWindowFullDefenseButtonPressed",               tb::Resources::GuiRects::BattleButtonsWindowFullDefenseButtonPressed},
                {"BattleButtonsWindowFollowButtonReleased",                   tb::Resources::GuiRects::BattleButtonsWindowFollowButtonReleased},
                {"BattleButtonsWindowFollowButtonPressed",                    tb::Resources::GuiRects::BattleButtonsWindowFollowButtonPressed},
                {"BattleButtonsWindowFollowDistanceButtonReleased",           tb::Resources::GuiRects::BattleButtonsWindowFollowDistanceButtonReleased},
                {"BattleButtonsWindowFollowDistanceButtonPressed",            tb::Resources::GuiRects::BattleButtonsWindowFollowDistanceButtonPressed},
                {"BattleButtonsWindowDoNotFollowButtonReleased",              tb::Resources::GuiRects::BattleButtonsWindowDoNotFollowButtonReleased},
                {"BattleButtonsWindowDoNotFollowButtonPressed",               tb::Resources::GuiRects::BattleButtonsWindowDoNotFollowButtonPressed},

                {"UpArrowButtonDisabled",                                     tb::Resources::GuiRects::UpArrowButtonDisabled},
                {"UpArrowButtonEnabled",                                      tb::Resources::GuiRects::UpArrowButtonEnabled},
                {"DownArrowButtonDisabled",                                   tb::Resources::GuiRects::DownArrowButtonDisabled},
                {"DownArrowButtonEnabled",                                    tb::Resources::GuiRects::DownArrowButtonEnabled},
                {"LeftArrowButtonDisabled",                                   tb::Resources::GuiRects::LeftArrowButtonDisabled},
                {"LeftArrowButtonEnabled",                                    tb::Resources::GuiRects::LeftArrowButtonEnabled},
                {"RightArrowButtonEnabled",                                   tb::Resources::GuiRects::RightArrowButtonEnabled},
                {"RightArrowButtonDisabled",                                  tb::Resources::GuiRects::RightArrowButtonDisabled},

                {"GraySquare",                                                tb::Resources::GuiRects::GraySquare},
                {"RedSquare",                                                 tb::Resources::GuiRects::RedSquare},

                {"TabButtonsWindowInventoryButtonReleased",                   tb::Resources::GuiRects::TabButtonsWindowInventoryButtonReleased},
                {"TabButtonsWindowInventoryButtonPressed",                    tb::Resources::GuiRects::TabButtonsWindowInventoryButtonPressed},
                {"TabButtonsWindowStatusButtonReleased",                      tb::Resources::GuiRects::TabButtonsWindowStatusButtonReleased},
                {"TabButtonsWindowStatusButtonPressed",                       tb::Resources::GuiRects::TabButtonsWindowStatusButtonPressed},
                {"TabButtonsWindowBattleButtonReleased",                      tb::Resources::GuiRects::TabButtonsWindowBattleButtonReleased},
                {"TabButtonsWindowBattleButtonPressed",                       tb::Resources::GuiRects::TabButtonsWindowBattleButtonPressed},
                {"TabButtonsWindowMiniMapButtonReleased",                     tb::Resources::GuiRects::TabButtonsWindowMiniMapButtonReleased},
                {"TabButtonsWindowMiniMapButtonPressed",                      tb::Resources::GuiRects::TabButtonsWindowMiniMapButtonPressed},
            };
        }
    }
}