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

#include "tb/Sprite.h"
#include "tb/Creature.h"
#include "tb/BitmapFont.h"
#include "tb/GameText.h"
#include "tb/Map.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/RenderWindow.h"
#include "tb/GameWindow.h"
#include "tb/MiniMapWindow.h"

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

    struct GuiState_t
    {
        bool ShowMiniMapWindow = true;
        bool ShowEquipmentWindow = false;
        bool ShowStatusWindow = false;

        bool ShowInventoryWindow = false;
        bool ShowCombatWindow = false;
        bool ShowSkillsWindow = false;
    };

    GuiState_t* getGuiState();

    void initImGui();

    bool loadConfig();
    bool loadData();

    bool loadTextures();
    bool loadFonts();
    bool loadBitmapFonts();
    bool loadCursors();

    bool loadMap(const std::string& fileName);

    void drawDockSpace();

    void drawFramesPerSecond();

    void drawLoadingText();

    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect, bool drawBlackRectangle);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);

    sf::FloatRect getClickRect(const sf::Texture& texture, const std::string& name);

    void drawDebugRect(sf::FloatRect rect);
    void drawDebugRectForWindows();

    void doGameStateEnterGame();
    void doGameStateLoading();
    void doGameStateMapSelect();
    void doGameStateInGame();

    sf::Vector2i getMousePositionInDesktop();

    void doAnimatedWater();

    bool createPlayer();

    void handleClosedEvent(sf::Event event);
    void handleResizedEvent(sf::Event event);
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

    void setLoadMapFileName(const std::string& fileName);

private:

    GuiState_t m_guiState;

    bool m_showDemoWindow = false;
    bool m_showStackToolWindow = false;

    bool m_isAnyKeyPressed = false;

    tb::GameState m_gameState = tb::GameState::EnterGame;

    uint32_t m_numLoadingFrames = 0;
    uint32_t m_numLoadingFramesMax = 2;

    std::string m_loadMapFileName;

    const unsigned int m_minimumTextureSizeRequiredToRun = 2048;

    sf::RectangleShape m_backgroundTextureShape;

    sf::Clock m_deltaClock;

    sf::Clock m_framesPerSecondClock;
    sf::Time m_framesPerSecondCurrentTime;
    sf::Time m_framesPerSecondPreviousTime;
    float m_framesPerSecond;

    sf::Clock m_animatedWaterClock;
    const sf::Time m_animatedWaterTime = sf::seconds(0.5f);

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
