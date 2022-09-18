#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteData.h"
#include "tb/PatternData.h"
#include "tb/WaterData.h"

#include "tb/Sprite.h"

#include "tb/BitmapFont.h"
#include "tb/GameText.h"

#include "tb/Map.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

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
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    static Game& getInstance()
    {
        static Game game;
        return game;
    }

    void createRenderWindow();

    bool loadTextures();
    bool loadBitmapFonts();

    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);

    void drawEnterGameScreen();
    void drawLoadingScreen();
    void drawMapSelectScreen();
    void drawInGameScreen();

    void doAnimatedWater();

    void processEvents();

    // this function fixes a bug between imgui, SFML and imgui-SFML
    // where the mouse cursor doesn't work correctly when resizing the window
    void fixMouseCursorForWindowResize(sf::RenderWindow& renderWindow);

    void waitForKeyPress();
    void run();

    void toggleDemoWindow();
    void toggleStackToolWindow();

    sf::RenderWindow* getRenderWindow();

    tb::GameState getGameState();

private:

    bool m_showDemoWindow = false;
    bool m_showStackToolWindow = false;

    tb::GameState m_gameState = tb::GameState::InGame;

    unsigned int m_minimumTextureSizeRequiredToRun = 2048;

    sf::Clock m_deltaClock;

    sf::Clock m_animatedWaterClock;

    sf::Cursor m_cursorArrow;

    sf::RenderWindow m_renderWindow;

    unsigned int m_renderWindowWidth = 1280;
    unsigned int m_renderWindowHeight = 720;

    sf::Uint32 m_renderWindowStyle = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;

    unsigned int m_renderWindowFrameRateLimit = 60;

    bool m_renderWindowVerticalSyncIsEnabled = false;

    bool m_renderWindowStartMaximized = true;

    sf::Image m_renderWindowIcon;

    const std::string m_renderWindowIconFileName = "images/icon.png";

    unsigned int m_renderWindowIconWidth = 32;
    unsigned int m_renderWindowIconHeight = 32;

    tb::BitmapFont m_bitmapFontDefault;
    tb::BitmapFont m_bitmapFontTiny;
    tb::BitmapFont m_bitmapFontModern;
};

}

namespace
{
    tb::Game& g_Game = tb::Game::getInstance();
}
