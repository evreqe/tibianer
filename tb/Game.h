#pragma once

#include "tb/Constants.h"
#include "tb/Utility.h"

#include "tb/SpriteData.h"
#include "tb/BitmapFont.h"
#include "tb/GameText.h"
#include "tb/Sprite.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/ErrorWindow.h"
#include "tb/SpriteDataWindow.h"
#include "tb/SpriteEditorWindow.h"

#include <windows.h> // must be included last due to conflicts

namespace tb
{

class MenuBar;
class StatusBar;

class Game
{

public:

    Game();

    void createRenderWindow();

    bool loadTextures();
    bool loadBitmapFonts();

    void drawWoodBackground();
    void drawWoodBorder(sf::FloatRect rect);
    void drawBackgroundTextureWithWoodBorder(const sf::Texture& texture);

    void drawEnterGameScreen();
    void drawLoadingScreen();
    void drawMapSelectScreen();

    void processEvents();

    // this function fixes a bug between imgui, SFML and imgui-SFML
    // where the mouse cursor doesn't work correctly when resizing the window
    void fixMouseCursorForWindowResize(sf::RenderWindow& renderWindow);

    void waitForKeyPress();
    void run();

    void toggleDemoWindow();
    void toggleStackToolWindow();

    sf::RenderWindow* getRenderWindow();

    tb::SpriteDataWindow* getSpriteDataWindow();
    void toggleSpriteDataWindow();

    tb::SpriteEditorWindow* getSpriteEditorWindow();
    void toggleSpriteEditorWindow();

    tb::SpriteData* getSpriteData();

    tb::GameState getGameState();

    void setMenuBar(tb::MenuBar* menuBar);
    void setStatusBar(tb::StatusBar* statusBar);

private:

    bool m_showDemoWindow = false;
    bool m_showStackToolWindow = false;

    const std::string m_gameTitle = "Tibianer";

    tb::GameState m_gameState = tb::GameState::EnterGame;

    unsigned int m_minimumTextureSizeRequiredToRun = 2048;

    sf::Clock m_deltaClock;

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

    tb::MenuBar* m_menuBar = nullptr;
    tb::StatusBar* m_statusBar = nullptr;

    tb::BitmapFont m_bitmapFontDefault;
    tb::BitmapFont m_bitmapFontTiny;
    tb::BitmapFont m_bitmapFontModern;

    tb::SpriteData m_spriteData;

    tb::SpriteDataWindow m_spriteDataWindow;
    tb::SpriteEditorWindow m_spriteEditorWindow;

    sf::Texture m_tex;
    sf::Image m_img;
};

}
