#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/MapData.h"
#include "tb/TextureData.h"
#include "tb/SpriteData.h"
#include "tb/BitmapFontData.h"
#include "tb/PatternData.h"
#include "tb/WaterAnimationData.h"
#include "tb/OutfitData.h"

#include "tb/Sprite.h"
#include "tb/Creature.h"
#include "tb/BitmapFont.h"
#include "tb/GameText.h"
#include "tb/Map.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/RenderWindow.h"
#include "tb/GameWindow.h"

#include "tb/OverlayWindow.h"
#include "tb/LogWindow.h"
#include "tb/SpriteDataWindow.h"
#include "tb/SpriteEditorWindow.h"
#include "tb/EnterGameWindow.h"
#include "tb/MapSelectWindow.h"

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

    void initImGui();

    bool loadData();

    bool loadTextures();
    bool loadBitmapFonts();

    bool loadMap(const std::string& fileName);

    void drawDockSpace();

    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);

    void doGameStateEnterGame();
    void doGameStateLoading();
    void doGameStateMapSelect();
    void doGameStateInGame();

    bool isMouseInsideImGuiWindow();

    sf::Vector2i getMousePositionInDesktop();

    void doAnimatedWater();

    bool createPlayer();

    void handleClosedEvent(sf::Event event);
    void handleResizedEvent(sf::Event event);
    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);
    void processEvents();

    void fixMouseCursorForWindowResize(sf::RenderWindow* renderWindow);

    void createTileFileFromImageFile(const std::string& fileName);

    void doOverlayText();

    void waitForKeyPress();
    void exit();
    void run();
    void endGame();

    void toggleDemoWindow();
    void toggleStackToolWindow();

    tb::GameState getGameState();
    void setGameState(tb::GameState gameState);

    tb::Creature::Ptr getPlayer();

    void setLoadMapFileName(const std::string& fileName);

private:

    bool m_showDemoWindow = false;
    bool m_showStackToolWindow = false;

    tb::GameState m_gameState = tb::GameState::EnterGame;

    uint32_t m_numLoadingFrames = 0;

    std::string m_loadMapFileName;

    const unsigned int m_minimumTextureSizeRequiredToRun = 2048;

    sf::Clock m_deltaClock;

    sf::Clock m_animatedWaterClock;

    sf::Cursor m_arrowCursor;

    tb::BitmapFont m_defaultBitmapFont;
    tb::BitmapFont m_tinyBitmapFont;
    tb::BitmapFont m_modernBitmapFont;

    const std::unordered_map<std::string, tb::BitmapFont&> m_bitmapFontNames =
    {
        {"Default",    m_defaultBitmapFont},
        {"Tiny",       m_tinyBitmapFont},
        {"Modern",     m_modernBitmapFont},
    };

    tb::Creature::Ptr m_player;

};

}

namespace
{
    inline tb::Game& g_Game = tb::Game::getInstance();
}
