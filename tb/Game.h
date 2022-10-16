#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteData.h"
#include "tb/BitmapFontData.h"
#include "tb/PatternData.h"
#include "tb/WaterData.h"
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

    bool loadTextures();
    bool loadBitmapFonts();

    void drawDockSpace();

    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);

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
    void processEvents();

    void fixMouseCursorForWindowResize(sf::RenderWindow* renderWindow);

    void createTileFileFromImageFile(const std::string& fileName);

    void doOverlayText();

    void waitForKeyPress();
    void exit();
    void run();

    void toggleDemoWindow();
    void toggleStackToolWindow();

    tb::GameState getGameState();

    tb::Creature::Ptr getPlayer();

private:

    bool m_showDemoWindow = false;
    bool m_showStackToolWindow = false;

    tb::GameState m_gameState = tb::GameState::InGame;

    const unsigned int m_minimumTextureSizeRequiredToRun = 2048;

    sf::Clock m_deltaClock;

    sf::Clock m_animatedWaterClock;

    sf::Cursor m_arrowCursor;

    tb::BitmapFont m_defaultBitmapFont;
    tb::BitmapFont m_tinyBitmapFont;
    tb::BitmapFont m_modernBitmapFont;

    tb::Creature::Ptr m_player;

};

}

namespace
{
    inline tb::Game& g_Game = tb::Game::getInstance();
}
