#include "tb/Game.h"

namespace tb
{

Game::Game()
{
    tb::print("{} (Build: {} {})\n", m_gameTitle, __DATE__, __TIME__);
}

void Game::createRenderWindow()
{
    m_renderWindow.create(sf::VideoMode(m_renderWindowWidth, m_renderWindowHeight), m_gameTitle, m_renderWindowStyle);

    if (m_renderWindowIcon.loadFromFile(m_renderWindowIconFileName) == true)
    {
        m_renderWindow.setIcon(m_renderWindowIconWidth, m_renderWindowIconHeight, m_renderWindowIcon.getPixelsPtr());
    }
    else
    {
        tb::print("ERROR: Failed to load icon file: {}\n", m_renderWindowIconFileName);
    }

    if (m_renderWindowFrameRateLimit != 0)
    {
        m_renderWindow.setFramerateLimit(m_renderWindowFrameRateLimit);
    }

    m_renderWindow.setVerticalSyncEnabled(m_renderWindowVerticalSyncIsEnabled);

    if (m_renderWindowStartMaximized == true)
    {
        //m_renderWindow.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
        //m_renderWindow.setPosition(sf::Vector2i(0, 0));

        // Windows API
        ::ShowWindow(m_renderWindow.getSystemHandle(), SW_MAXIMIZE);
    }

    ImGui::SFML::Init(m_renderWindow);

    ImGui::StyleColorsLight();

    ImGuiIO& imguiIO = ImGui::GetIO();
    imguiIO.ConfigWindowsMoveFromTitleBarOnly = true;
}

bool Game::loadTextures()
{
    if (auto maximumTextureSize = sf::Texture::getMaximumSize(); maximumTextureSize < m_minimumTextureSizeRequiredToRun)
    {
        tb::print("Your computer supports a maximum texture size of {}\n", maximumTextureSize);
        tb::print("This game requires at least {} texture size in order to play\n", m_minimumTextureSizeRequiredToRun);
        return false;
    }

    for (auto& [textureFileName, texture] : tb::KeyValues::Textures)
    {
        if (texture.loadFromFile(textureFileName) == false)
        {
            tb::print("ERROR: Failed to load texture file: {}", textureFileName);
            return false;
        }
    }

    // tiled textures
    tb::Textures::Wood.setRepeated(true);
    tb::Textures::WoodHorizontal1.setRepeated(true);
    tb::Textures::WoodHorizontal2.setRepeated(true);
    tb::Textures::WoodVertical1.setRepeated(true);
    tb::Textures::WoodVertical2.setRepeated(true);

    tb::Textures::Water.setRepeated(true);

    return true;
}

bool Game::loadBitmapFonts()
{
    if (m_bitmapFontDefault.load(tb::BitmapFonts::Default::FileName, tb::BitmapFonts::Default::GlyphSize, &tb::BitmapFonts::Default::GlyphWidthList) == false)
    {
        return false;
    }

    if (m_bitmapFontTiny.load(tb::BitmapFonts::Tiny::FileName, tb::BitmapFonts::Tiny::GlyphSize, &tb::BitmapFonts::Tiny::GlyphWidthList, -1) == false)
    {
        return false;
    }

    if (m_bitmapFontModern.load(tb::BitmapFonts::Modern::FileName, tb::BitmapFonts::Modern::GlyphSize, &tb::BitmapFonts::Modern::GlyphWidthList, -1) == false)
    {
        return false;
    }

    return true;
}

void Game::drawWoodBackground()
{
    sf::Sprite wood;
    wood.setTexture(tb::Textures::Wood);
    wood.setTextureRect(sf::IntRect(0, 0, m_renderWindow.getSize().x, m_renderWindow.getSize().y));

    m_renderWindow.draw(wood);
}

void Game::drawWoodBorder(sf::FloatRect rect)
{
    sf::Sprite woodHorizontal1;
    sf::Sprite woodHorizontal2;
    sf::Sprite woodVertical1;
    sf::Sprite woodVertical2;

    woodHorizontal1.setTexture(tb::Textures::WoodHorizontal1);
    woodHorizontal2.setTexture(tb::Textures::WoodHorizontal2);
    woodVertical1.setTexture(tb::Textures::WoodVertical1);
    woodVertical2.setTexture(tb::Textures::WoodVertical2);

    woodHorizontal1.setPosition(sf::Vector2f(rect.left - 3.0f, rect.top - 3.0f));
    woodHorizontal1.setTextureRect(sf::IntRect(0, 0, (int)(rect.width + 6.0f), 3));

    woodHorizontal2.setPosition(sf::Vector2f(rect.left - 3.0f, rect.top + rect.height));
    woodHorizontal2.setTextureRect(sf::IntRect(0, 0, (int)(rect.width + 6.0f), 3));

    woodVertical1.setPosition(sf::Vector2f(rect.left - 3.0f, rect.top));
    woodVertical1.setTextureRect(sf::IntRect(0, 0, 3, (int)(rect.height)));

    woodVertical2.setPosition(sf::Vector2f(rect.left + rect.width, rect.top));
    woodVertical2.setTextureRect(sf::IntRect(0, 0, 3, (int)(rect.height)));

    m_renderWindow.draw(woodHorizontal1);
    m_renderWindow.draw(woodHorizontal2);
    m_renderWindow.draw(woodVertical1);
    m_renderWindow.draw(woodVertical2);
}

void Game::drawBackgroundTextureWithWoodBorder(const sf::Texture& texture)
{
    /*
            m_img = tb::Textures::InGame.copyToImage();

            float levels = 3.0f;

            float sr, sg, sb;
            sf::Uint8 dr, dg, db;

            for (unsigned int i = 0; i < m_img.getSize().x; ++i)
            {
                for (unsigned int j = 0; j < m_img.getSize().y; ++j)
                {
                    auto pxl = m_img.getPixel(i, j);

                    pxl.r *= 0.75f;
                    pxl.g *= 0.75f;
                    pxl.b *= 0.75f;

                    sr = (float)(pxl.r) / 255.0f;
                    sg = (float)(pxl.g) / 255.0f;
                    sb = (float)(pxl.b) / 255.0f;

                    dr = 255 * std::roundf(sr * levels) / levels;
                    dg = 255 * std::roundf(sg * levels) / levels;
                    db = 255 * std::roundf(sb * levels) / levels;

                    m_img.setPixel(i, j, sf::Color(dr, dg, db));
                }
            }

            m_tex.loadFromImage(m_img);

            sf::Sprite spr;
            spr.setTexture(m_tex);

            m_renderWindow.draw(spr);

            tb::Sprite spr2;
            spr2.setID(4);

            m_renderWindow.draw(spr2);

            return;
    */

    float renderWindowWidth = m_renderWindow.getSize().x;
    float renderWindowHeight = m_renderWindow.getSize().y;

    float menuBarHeight = m_menuBar->getHeight();
    float statusBarHeight = m_statusBar->getHeight();

    sf::RectangleShape blackBorder(sf::Vector2f(renderWindowWidth - 20.0f, renderWindowHeight - 20.0f - menuBarHeight - statusBarHeight));
    blackBorder.setFillColor(sf::Color(0, 0, 0));
    blackBorder.setPosition(sf::Vector2f(10.0f, 10.0f + menuBarHeight));

    sf::RectangleShape backgroundTexture(sf::Vector2f(renderWindowWidth - 20.0f - 2.0f, renderWindowHeight - 20.0f - 2.0f - menuBarHeight - statusBarHeight));
    backgroundTexture.setTexture(&texture);
    backgroundTexture.setPosition(sf::Vector2f(10.0f + 1.0f, 10.0f + 1.0f + menuBarHeight));

    m_renderWindow.draw(blackBorder);
    m_renderWindow.draw(backgroundTexture);

    drawWoodBorder(blackBorder.getGlobalBounds());
}

void Game::drawEnterGameScreen()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::EnterGame);
}

void Game::drawLoadingScreen()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::Loading);
}

void Game::drawMapSelectScreen()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::MapSelect);
}

void Game::processEvents()
{
    sf::Event event;
    while (m_renderWindow.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(m_renderWindow, event);

        if (event.type == sf::Event::Resized)
        {
            // stretch to fill window
            sf::FloatRect visibleArea(0.0f, 0.0f, event.size.width, event.size.height);
            m_renderWindow.setView(sf::View(visibleArea));
        }

        if (event.type == sf::Event::Closed)
        {
            m_renderWindow.close();
        }
    }
}

// this function fixes a bug between imgui, SFML and imgui-SFML
// where the mouse cursor doesn't work correctly when resizing the window
void Game::fixMouseCursorForWindowResize(sf::RenderWindow& renderWindow)
{
    static ImGuiIO& imguiIO = ImGui::GetIO();

    static bool imguiHasCursorPrev = true;

    if (bool imguiHasCursor = imguiIO.WantCaptureMouse || imguiIO.WantCaptureKeyboard; imguiHasCursor != imguiHasCursorPrev)
    {
        if (imguiHasCursor)
        {
            imguiIO.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
        }
        else
        {
            imguiIO.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

            renderWindow.setMouseCursor(m_cursorArrow);
        }
        imguiHasCursorPrev = imguiHasCursor;
    }
}

void Game::waitForKeyPress()
{
    tb::print("Press any key to continue...\n");

    int waitForKeyPress = std::cin.get();
}

void Game::run()
{
    tb::print("Creating render window\n");
    createRenderWindow();

    tb::print("Loading sprite data\n");
    if (m_spriteData.load() == false)
    {
        tb::print("ERROR: Failed to load sprite data\n");
        waitForKeyPress();
        return;
    }

    tb::print("Loading textures\n");
    if (loadTextures() == false)
    {
        tb::print("ERROR: Failed to load textures\n");
        waitForKeyPress();
        return;
    }

    tb::print("Loading bitmap fonts\n");
    if (loadBitmapFonts() == false)
    {
        tb::print("ERROR: Failed to load bitmap fonts\n");
        waitForKeyPress();
        return;
    }

    tb::print("Loading mouse cursors\n");
    m_cursorArrow.loadFromSystem(sf::Cursor::Arrow);

    m_spriteDataWindow.setSpriteData(m_spriteData);
    m_spriteEditorWindow.setSpriteData(m_spriteData);

    while (m_renderWindow.isOpen() == true)
    {
        processEvents();

        fixMouseCursorForWindowResize(m_renderWindow);

        ImGui::SFML::Update(m_renderWindow, m_deltaClock.restart());

        m_renderWindow.clear(sf::Color::Black);

        drawWoodBackground();

        if (m_gameState == tb::GameState::EnterGame)
        {
            drawEnterGameScreen();
        }
        else if (m_gameState == tb::GameState::Loading)
        {
            drawLoadingScreen();
        }
        else if (m_gameState == tb::GameState::MapSelect)
        {
            drawMapSelectScreen();
        }

        m_menuBar->draw(this);
        m_statusBar->draw(this);

        if (m_showDemoWindow == true)
        {
            ImGui::ShowDemoWindow(&m_showDemoWindow);
        }

        if (m_showStackToolWindow == true)
        {
            ImGui::ShowStackToolWindow(&m_showStackToolWindow);
        }

        if (m_spriteEditorWindow.getIsVisible() == true)
        {
            m_spriteEditorWindow.draw();
        }

        if (m_spriteDataWindow.getIsVisible() == true)
        {
            m_spriteDataWindow.draw();
        }

        ImGui::SFML::Render(m_renderWindow);

        m_renderWindow.display();
    }

    ImGui::SFML::Shutdown();

    waitForKeyPress();
}

void Game::toggleDemoWindow()
{
    tb::Utility::toggleBool(m_showDemoWindow);
}

void Game::toggleStackToolWindow()
{
    tb::Utility::toggleBool(m_showStackToolWindow);
}

sf::RenderWindow* Game::getRenderWindow()
{
    return &m_renderWindow;
}

tb::SpriteDataWindow* Game::getSpriteDataWindow()
{
    return &m_spriteDataWindow;
}

void Game::toggleSpriteDataWindow()
{
    m_spriteDataWindow.toggleIsVisible();
}

tb::SpriteEditorWindow* Game::getSpriteEditorWindow()
{
    return &m_spriteEditorWindow;
}

void Game::toggleSpriteEditorWindow()
{
    m_spriteEditorWindow.toggleIsVisible();
}

tb::SpriteData* Game::getSpriteData()
{
    return &m_spriteData;
}

tb::GameState Game::getGameState()
{
    return m_gameState;
}

void Game::setMenuBar(tb::MenuBar* menuBar)
{
    m_menuBar = menuBar;
}

void Game::setStatusBar(tb::StatusBar* statusBar)
{
    m_statusBar = statusBar;
}

}
