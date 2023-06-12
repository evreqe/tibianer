#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/OptionsData.h"
#include "tb/MapData.h"
#include "tb/TextureData.h"
#include "tb/SpriteData.h"
#include "tb/BitmapFontData.h"
#include "tb/PatternData.h"
#include "tb/WaterAnimationData.h"
#include "tb/OutfitData.h"
#include "tb/MessageOfTheDayData.h"
#include "tb/ClickRectData.h"
#include "tb/GuiData.h"
#include "tb/CursorData.h"
#include "tb/FontData.h"
#include "tb/HotkeysData.h"
#include "tb/AnimationData.h"

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

#include <windows.h> // must be included last due to conflicts

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

    struct Properties_t
    {
        bool ShowMenuBar = true;
        bool ShowStatusBar = true;

        bool ShowDemoWindow = false;
        bool ShowStackToolWindow = false;

        bool ShowErrorLoadingMapPopup = false;
        bool ShowEndGamePopup = false;

        bool IsAnyKeyPressed = false;
    };

    struct GuiProperties_t
    {
        float Scale = 1.0f;

        bool ShowEquipmentWindow = false;
        bool ShowStatusWindow = false;
        bool ShowMiniMapWindow = true;

        bool TabButtonsWindowInventoryButtonIsPressed = true;
        bool TabButtonsWindowStatusButtonIsPressed = false;
        bool TabButtonsWindowBattleButtonIsPressed = false;
        bool TabButtonsWindowMiniMapButtonIsPressed = false;

        bool ShowInventoryWindow = true;
        bool ShowSkillsWindow = false;
        bool ShowBattleWindow = false;

        bool BattleButtonsWindowFullAttackButtonIsPressed = true;
        bool BattleButtonsWindowHalfAttackHalfDefenseButtonIsPressed = false;
        bool BattleButtonsWindowFullDefenseButtonIsPressed = false;

        bool BattleButtonsWindowFollowButtonIsPressed = false;
        bool BattleButtonsWindowFollowDistanceButtonIsPressed = false;
        bool BattleButtonsWindowDoNotFollowButtonIsPressed = true;
    };

    Properties_t* getProperties();
    GuiProperties_t* getGuiProperties();

    void initImGui();

    bool loadConfig();
    bool loadData();

    bool loadGlobalsFromData();
    bool loadTextures();
    bool loadFonts();
    bool loadBitmapFonts();
    bool loadCursors();
    bool loadSprites();
    bool loadAnimations();
    bool loadGuiRects();

    bool loadMap(const std::string& fileName);
    void loadMapUsingThread(const std::string& fileName);

    void drawDockSpace();

    void drawFramesPerSecond();

    void drawLoadingText();

    sf::FloatRect getGuiFullLayoutRect();
    sf::FloatRect getGuiLeftLayoutRect();
    sf::FloatRect getGuiRightLayoutRect();

    void drawToolTip(const std::string& text);

    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect, bool drawBlackRectangle);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);

    sf::FloatRect getClickRect(const sf::Texture& texture, const std::string& name);

    void drawDebugRect(sf::FloatRect rect);

    void drawSfmlWindows();
    void drawDebugRectForSfmlWindows();
    void drawWoodBorderForSfmlWindows();

    void setSizeInLayoutForSfmlWindows();
    void setPositionInLayoutForSfmlWindows();
    void setSizeScaleForSfmlWindows(float scale);
    void updateLayoutForSfmlWindows();

    void drawImGuiWindows();

    void doEndGamePopup();
    void doErrorLoadingMapPopup();

    void doGameStateEnterGame();
    void doGameStateLoadingMap();
    void doGameStateMapSelect();
    void doGameStateInGame();

    sf::Vector2i getMousePositionInDesktop();

    tb::VisibleZ_t getVisibleZOfPlayer();

    bool createPlayer();

    bool spawnAnimationByIndex(const sf::Vector2i& tileCoords, tb::ZAxis_t z, uint32_t index);
    bool spawnAnimationByName(const sf::Vector2i& tileCoords, tb::ZAxis_t z, const std::string& name);

    void handleClosedEvent(sf::Event event);
    void handleResizedEvent(sf::Event event);
    void handleLostFocusEvent(sf::Event event);
    void handleGainedFocusEvent(sf::Event event);
    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);
    void handleKeyPressedEvent(sf::Event event);
    void handleKeyReleasedEvent(sf::Event event);
    void handleKeyboardInput();
    void processEvents();

    void setMouseCursor(const sf::Cursor& cursor);
    void fixMouseCursorForWindowResize(sf::RenderWindow* renderWindow);

    void createTileFileFromImageFile(const std::string& fileName);

    void doOverlayText();

    void waitForKeyPress();
    void exit();
    void run();
    void endGame();

    bool isDeveloperModeEnabled();
    void toggleDeveloperMode();

    bool isDebugModeEnabled();
    void toggleDebugMode();

    void toggleDemoWindow();
    void toggleStackToolWindow();

    tb::GameState getGameState();
    void setGameState(tb::GameState gameState);

    tb::Creature::Ptr getPlayer();

    sf::Vector2i getVectorByMovementDirection(tb::MovementDirection movementDirection);
    tb::MovementDirection getMovementDirectionByVector(sf::Vector2i vector);

    tb::Tile::Ptr getTileByThingMovementDirection(tb::Thing::Ptr thing, tb::MovementDirection direction);

    bool findCeilingAbovePlayerAtZ(tb::ZAxis_t z);

    void handleCreatureMovement(tb::Creature::Ptr creature, tb::MovementDirection movementDirection);

    bool doMoveThingFromTileToTile(tb::Thing::Ptr thing, tb::Tile::Ptr toTile);

    tb::BitmapFont* getDefaultBitmapFont();
    tb::BitmapFont* getTinyBitmapFont();
    tb::BitmapFont* getModernBitmapFont();

private:

    Properties_t m_properties;
    GuiProperties_t m_guiProperties;

    tb::GameState m_gameState = tb::GameState::EnterGame;

    std::future<bool> m_loadMapThread;
    std::future_status m_loadMapThreadStatus;

    const unsigned int m_minimumTextureSizeRequiredToRun = 2048;

    sf::RectangleShape m_backgroundTextureShape;

    sf::Clock m_deltaClock;

    sf::Clock m_framesPerSecondClock;
    sf::Time m_framesPerSecondCurrentTime;
    sf::Time m_framesPerSecondPreviousTime;
    float m_framesPerSecond;

    sf::Clock m_cameraKeyPressedClock;
    const sf::Time m_cameraKeyPressedTime = sf::milliseconds(100);

    tb::BitmapFont m_defaultBitmapFont;
    tb::BitmapFont m_tinyBitmapFont;
    tb::BitmapFont m_modernBitmapFont;

    const std::unordered_map<std::string, tb::BitmapFont&> m_bitmapFontNames =
    {
        {"Default",    m_defaultBitmapFont},
        {"Tiny",       m_tinyBitmapFont},
        {"Modern",     m_modernBitmapFont},
    };

    tb::Creature::Ptr m_player = nullptr;

};

}

namespace
{
    inline tb::Game& g_Game = tb::Game::getInstance();
}
