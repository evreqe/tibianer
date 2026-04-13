#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Resources.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/ResourceLoader.h"

#include "tb/OptionsData.h"
#include "tb/MapData.h"

#include "tb/PatternData.h"
#include "tb/WaterAnimationData.h"
#include "tb/OutfitSpritesData.h"
#include "tb/MessageOfTheDayData.h"
#include "tb/TextureRectData.h"
#include "tb/HotkeysData.h"
#include "tb/TextureData.h"
#include "tb/FontData.h"
#include "tb/BitmapFontData.h"
#include "tb/CursorData.h"
#include "tb/SpriteData.h"
#include "tb/AnimationData.h"
#include "tb/MapGeneratorData.h"
#include "tb/MapGeneratorPixelData.h"

#include "tb/GUI.h"
#include "tb/Thing.h"
#include "tb/Object.h"
#include "tb/Creature.h"
#include "tb/Animation.h"
#include "tb/Tile.h"
#include "tb/TileMap.h"
#include "tb/Sprite.h"
#include "tb/BitmapFont.h"
#include "tb/GameText.h"
#include "tb/Map.h"
#include "tb/MapGenerator.h"
#include "tb/Joystick.h"
#include "tb/JoystickManager.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/RenderWindow.h"

#include "tb/GameWindow.h"
#include "tb/EquipmentWindow.h"
#include "tb/StatusWindow.h"
#include "tb/MiniMapWindow.h"
#include "tb/TabButtonsWindow.h"
#include "tb/SkillsWindow.h"

#include "tb/OverlayWindow.h"
#include "tb/LogWindow.h"
#include "tb/SpriteDataWindow.h"
#include "tb/SpriteEditorWindow.h"
#include "tb/OptionsWindow.h"
#include "tb/HotkeysWindow.h"
#include "tb/EnterGameWindow.h"
#include "tb/MapSelectWindow.h"
#include "tb/SetOutfitWindow.h"
#include "tb/CommentsWindow.h"
#include "tb/MessageOfTheDayWindow.h"
#include "tb/ConnectionWindow.h"
#include "tb/ControlsWindow.h"
#include "tb/TipsAndTricksWindow.h"
#include "tb/AboutTibiaWindow.h"
#include "tb/AboutTibianerWindow.h"
#include "tb/MapGeneratorWindow.h"

namespace tb
{

class Game
{

public:

    Game();
    ~Game();

    static Game& getInstance()
    {
        static Game instance;
        return instance;
    }

private:

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

public:

    struct Properties
    {
        bool IsMouseLeftButtonPressed = false;
        bool IsMouseDragging = false;

        bool IsAnyKeyboardKeyPressed = false;
        bool IsAnyJoystickButtonPressed = false;
    };

    Properties* getProperties();

    bool loadConfig();
    bool loadData();

    bool loadMap(const std::string& fileName);
    void loadMapUsingThread(const std::string& fileName);

    void doGameStateTesting();
    void doGameStateEnterGame();
    void doGameStateLoadingMap();
    void doGameStateMapSelect();
    void doGameStateInGame();

    sf::Vector2i getMousePositionInDesktop();

    tb::AxisZVisibility getPlayerAxisZVisibility();

    bool createPlayer();

    bool spawnAnimationByIndex(const tb::TileCoords& tileCoords, tb::AxisZ axisZ, std::uint32_t index);
    bool spawnAnimationByName(const tb::TileCoords& tileCoords, tb::AxisZ axisZ, const std::string& name);

    void handleEventClosed();
    void handleEventResized(const sf::Event::Resized* eventResized);
    void handleEventFocusLost();
    void handleEventFocusGained();
    void handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled);
    void handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed);
    void handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased);
    void handleEventMouseMoved(const sf::Event::MouseMoved* eventMouseMoved);
    void handleEventKeyPressed(const sf::Event::KeyPressed* eventKeyPressed);
    void handleEventKeyReleased(const sf::Event::KeyReleased* eventKeyReleased);
    void handleEventJoystickConnected(const sf::Event::JoystickConnected* eventJoystickConnected);
    void handleEventJoystickDisconnected(const sf::Event::JoystickDisconnected* eventJoystickDisconnected);
    void handleEventJoystickMoved(const sf::Event::JoystickMoved* eventJoystickMoved);
    void handleEventJoystickButtonPressed(const sf::Event::JoystickButtonPressed* eventJoystickButtonPressed);
    void handleEventJoystickButtonReleased(const sf::Event::JoystickButtonReleased* eventJoystickButtonReleased);

    void initializeFramesPerSecond();
    void calculateFramesPerSecond();
    float getFramesPerSecond();

    void processEvents();

    void handleKeyboardInput();
    void handleJoystickInput();

    void handleCameraMovement();
    void handlePlayerMovement();

    void setMouseCursor(const sf::Cursor& cursor);
    void fixMouseCursorForWindowResize(sf::RenderWindow* renderWindow);

    void createTileFileFromImageFile(const std::string& fileName);

    void updateOverlayWindowText();

    void waitForKeyPress();
    void exit();
    void run();
    void endGame();

    bool isDeveloperModeEnabled();
    void toggleDeveloperMode();

    bool isDebugModeEnabled();
    void toggleDebugMode();

    tb::GameState getGameState();
    void setGameState(tb::GameState gameState);

    tb::Creature::Ptr getPlayer();

    sf::Vector2i getVectorByMovementDirection(tb::MovementDirection movementDirection);
    tb::MovementDirection getMovementDirectionByVector(sf::Vector2i vector);

    tb::Tile::Ptr getTileByThingMovementDirection(tb::Thing::Ptr thing, tb::MovementDirection direction);

    bool doesCeilingExistAbovePlayerAtAxisZ(tb::AxisZ axisZ);

    void handleCreatureMovement(tb::Creature::Ptr creature, tb::MovementDirection movementDirection);

    bool doMoveThingFromTileToTile(tb::Thing::Ptr thing, tb::Tile::Ptr toTile);

private:

    Properties m_properties;

    tb::GameState m_gameState = tb::GameState::EnterGame;

    std::future<bool> m_loadMapThread;
    std::future_status m_loadMapThreadStatus = std::future_status::deferred;

    sf::Clock m_deltaClock;

    sf::Clock m_mouseDragClock;
    const sf::Time m_mouseDragTime = sf::milliseconds(100);
    sf::Vector2i m_mouseDragStartPosition;
    std::int32_t m_mouseDragDistanceThreshold = 4;

    sf::Clock m_framesPerSecondClock;
    sf::Time m_framesPerSecondCurrentTime;
    sf::Time m_framesPerSecondPreviousTime;
    float m_framesPerSecond = 0.0f;

    sf::Clock m_cameraMovementClock;
    const sf::Time m_cameraMovementTime = sf::milliseconds(100);

    tb::Creature::Ptr m_player = nullptr;
    sf::Clock m_playerMovementClock;
     const sf::Time m_playerMovementTime = sf::milliseconds(100);

};

}

namespace
{
    inline tb::Game& g_Game = tb::Game::getInstance();
}
