#include "tb/Game.h"

namespace tb
{

Game::Game()
{
    //
}

Game::~Game()
{
    //
}

void Game::createRenderWindow()
{
    m_renderWindow.create(sf::VideoMode(m_renderWindowWidth, m_renderWindowHeight), tb::Constants::GameTitle, m_renderWindowStyle);

    if (m_renderWindowIcon.loadFromFile(m_renderWindowIconFileName) == true)
    {
        m_renderWindow.setIcon(m_renderWindowIconWidth, m_renderWindowIconHeight, m_renderWindowIcon.getPixelsPtr());
    }
    else
    {
        g_Log.write("ERROR: Failed to load icon file: {}\n", m_renderWindowIconFileName);
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
        g_Log.write("Your computer supports a maximum texture size of {}\n", maximumTextureSize);
        g_Log.write("This game requires at least {} texture size in order to play\n", m_minimumTextureSizeRequiredToRun);
        return false;
    }

    for (auto& [textureFileName, texture] : tb::KeyValues::Textures)
    {
        if (texture.loadFromFile(textureFileName) == false)
        {
            g_Log.write("ERROR: Failed to load texture file: {}\n", textureFileName);
            return false;
        }
    }

    // tiled textures
    tb::Textures::Scroll.setRepeated(true);

    tb::Textures::Wood.setRepeated(true);
    tb::Textures::WoodHorizontal1.setRepeated(true);
    tb::Textures::WoodHorizontal2.setRepeated(true);
    tb::Textures::WoodVertical1.setRepeated(true);
    tb::Textures::WoodVertical2.setRepeated(true);

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

/*
    sf::Sprite sprInGame2;
    sprInGame2.setTexture(tb::Textures::InGame2);

    m_renderWindow.draw(sprInGame2);

    sf::RenderTexture rt;
    rt.create(416, 288);
    rt.clear(sf::Color::Transparent);

    sf::Sprite sprLight;
    sprLight.setTexture(tb::Textures::Light);
    sprLight.setPosition(128, 128);

    rt.draw(sprLight, sf::BlendAdd);

    sprLight.setPosition(0, 0);

    rt.draw(sprLight, sf::BlendAdd);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(416.0f, 288.0f));
    rect.setFillColor(sf::Color(255, 255, 255, 64));

    rt.draw(rect, sf::BlendAdd);

    rt.display();

    sf::Sprite sprRt;
    sprRt.setTexture(rt.getTexture());

    sf::BlendMode linearBurn = sf::BlendMultiply;
    //linearBurn.colorEquation = sf::BlendMode::Equation::Add;
    //linearBurn.alphaEquation = sf::BlendMode::Equation::Add;
    //linearBurn.colorSrcFactor = sf::BlendMode::Factor::One;
    //linearBurn.colorDstFactor = sf::BlendMode::Factor::SrcColor;
    //linearBurn.alphaSrcFactor = sf::BlendMode::Factor::One;
    //linearBurn.alphaDstFactor = sf::BlendMode::Factor::SrcColor;

    static uint32_t colorEquation = 2; // sf::BlendMode::Equation::Add;
    static uint32_t alphaEquation = 2; // sf::BlendMode::Equation::Add;
    static uint32_t colorSrcFactor = 3; // sf::BlendMode::Factor::One;
    static uint32_t colorDstFactor = 2; // sf::BlendMode::Factor::SrcColor;
    static uint32_t alphaSrcFactor = 8; // sf::BlendMode::Factor::One;
    static uint32_t alphaDstFactor = 8; // sf::BlendMode::Factor::SrcColor;

    bool isVisible = true;
    ImGui::Begin("Blend Mode##BlendModeWindow", &isVisible);

    if (ImGui::Button("Random##BlendModeRandom"))
    {
        colorEquation = tb::Utility::getRandomNumber(0, 2);
        alphaEquation = tb::Utility::getRandomNumber(0, 2);

        colorSrcFactor = tb::Utility::getRandomNumber(0, 9);
        colorDstFactor = tb::Utility::getRandomNumber(0, 9);
        alphaSrcFactor = tb::Utility::getRandomNumber(0, 9);
        alphaDstFactor = tb::Utility::getRandomNumber(0, 9);
    }

    ImGui::Separator();

    ImGui::Text("colorEquation: %d", colorEquation);
    ImGui::Text("alphaEquation: %d", alphaEquation);
    ImGui::Text("colorSrcFactor: %d", colorSrcFactor);
    ImGui::Text("colorDstFactor: %d", colorDstFactor);
    ImGui::Text("alphaSrcFactor: %d", alphaSrcFactor);
    ImGui::Text("alphaDstFactor: %d", alphaDstFactor);

    ImGui::Separator();

    if (ImGui::BeginTable("##BlendModeTable", 2, ImGuiTableFlags_BordersOuter))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("ColorEquationAdd##BlendModeColorEquationAdd")) { colorEquation = sf::BlendMode::Equation::Add; }
        if (ImGui::Button("ColorEquationSubtract##BlendModeColorEquationSubtract")) { colorEquation = sf::BlendMode::Equation::Subtract; }
        if (ImGui::Button("ColorEquationReverseSubtract##BlendModeColorEquationReverseSubtract")) { colorEquation = sf::BlendMode::Equation::ReverseSubtract; }

        ImGui::Separator();

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("AlphaEquationAdd##BlendModeAlphaEquationAdd")) { alphaEquation = sf::BlendMode::Equation::Add; }
        if (ImGui::Button("AlphaEquationSubtract##BlendModeAlphaEquationSubtract")) { alphaEquation = sf::BlendMode::Equation::Subtract; }
        if (ImGui::Button("AlphaEquationReverseSubtract##BlendModeAlphaEquationReverseSubtract")) { alphaEquation = sf::BlendMode::Equation::ReverseSubtract; }

        ImGui::Separator();

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("ColorSrcFactorDstAlpha##BlendModeColorSrcFactorDstAlpha")) { colorSrcFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("ColorSrcFactorDstColor##BlendModeColorSrcFactorDstColor")) { colorSrcFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("ColorSrcFactorOne##BlendModeColorSrcFactorOne")) { colorSrcFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("ColorSrcFactorOneMinusDstAlpha##BlendModeColorSrcFactorOneMinusDstAlpha")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("ColorSrcFactorOneMinusDstColor##BlendModeColorSrcFactorOneMinusDstColor")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("ColorSrcFactorOneMinusSrcAlpha##BlendModeColorSrcFactorOneMinusSrcAlpha")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("ColorSrcFactorOneMinusSrcColor##BlendModeColorSrcFactorOneMinusSrcColor")) { colorSrcFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("ColorSrcFactorSrcAlpha##BlendModeColorSrcFactorSrcAlpha")) { colorSrcFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("ColorSrcFactorSrcColor##BlendModeColorSrcFactorSrcColor")) { colorSrcFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("ColorSrcFactorZero##BlendModeColorSrcFactorZero")) { colorSrcFactor = sf::BlendMode::Factor::Zero; }

        ImGui::Separator();

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("ColorDstFactorDstAlpha##BlendModeColorDstFactorDstAlpha")) { colorDstFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("ColorDstFactorDstColor##BlendModeColorDstFactorDstColor")) { colorDstFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("ColorDstFactorOne##BlendModeColorDstFactorOne")) { colorDstFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("ColorDstFactorOneMinusDstAlpha##BlendModeColorDstFactorOneMinusDstAlpha")) { colorDstFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("ColorDstFactorOneMinusDstColor##BlendModeColorDstFactorOneMinusDstColor")) { colorDstFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("ColorDstFactorOneMinusSrcAlpha##BlendModeColorDstFactorOneMinusSrcAlpha")) { colorDstFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("ColorDstFactorOneMinusSrcColor##BlendModeColorDstFactorOneMinusSrcColor")) { colorDstFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("ColorDstFactorSrcAlpha##BlendModeColorDstFactorSrcAlpha")) { colorDstFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("ColorDstFactorSrcColor##BlendModeColorDstFactorSrcColor")) { colorDstFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("ColorDstFactorZero##BlendModeColorDstFactorZero")) { colorDstFactor = sf::BlendMode::Factor::Zero; }

        ImGui::Separator();

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("AlphaSrcFactorDstAlpha##BlendModeAlphaSrcFactorDstAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("AlphaSrcFactorDstColor##BlendModeAlphaSrcFactorDstColor")) { alphaSrcFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("AlphaSrcFactorOne##BlendModeAlphaSrcFactorOne")) { alphaSrcFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("AlphaSrcFactorOneMinusDstAlpha##BlendModeAlphaSrcFactorOneMinusDstAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("AlphaSrcFactorOneMinusDstColor##BlendModeAlphaSrcFactorOneMinusDstColor")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("AlphaSrcFactorOneMinusSrcAlpha##BlendModeAlphaSrcFactorOneMinusSrcAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("AlphaSrcFactorOneMinusSrcColor##BlendModeAlphaSrcFactorOneMinusSrcColor")) { alphaSrcFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("AlphaSrcFactorSrcAlpha##BlendModeAlphaSrcFactorSrcAlpha")) { alphaSrcFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("AlphaSrcFactorSrcColor##BlendModeAlphaSrcFactorSrcColor")) { alphaSrcFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("AlphaSrcFactorZero##BlendModeAlphaSrcFactorZero")) { alphaSrcFactor = sf::BlendMode::Factor::Zero; }

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("AlphaDstFactorDstAlpha##BlendModeAlphaDstFactorDstAlpha")) { alphaDstFactor = sf::BlendMode::Factor::DstAlpha; }
        if (ImGui::Button("AlphaDstFactorDstColor##BlendModeAlphaDstFactorDstColor")) { alphaDstFactor = sf::BlendMode::Factor::DstColor; }
        if (ImGui::Button("AlphaDstFactorOne##BlendModeAlphaDstFactorOne")) { alphaDstFactor = sf::BlendMode::Factor::One; }
        if (ImGui::Button("AlphaDstFactorOneMinusDstAlpha##BlendModeAlphaDstFactorOneMinusDstAlpha")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusDstAlpha; }
        if (ImGui::Button("AlphaDstFactorOneMinusDstColor##BlendModeAlphaDstFactorOneMinusDstColor")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusDstColor; }
        if (ImGui::Button("AlphaDstFactorOneMinusSrcAlpha##BlendModeAlphaDstFactorOneMinusSrcAlpha")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusSrcAlpha; }
        if (ImGui::Button("AlphaDstFactorOneMinusSrcColor##BlendModeAlphaDstFactorOneMinusSrcColor")) { alphaDstFactor = sf::BlendMode::Factor::OneMinusSrcColor; }
        if (ImGui::Button("AlphaDstFactorSrcAlpha##BlendModeAlphaDstFactorSrcAlpha")) { alphaDstFactor = sf::BlendMode::Factor::SrcAlpha; }
        if (ImGui::Button("AlphaDstFactorSrcColor##BlendModeAlphaDstFactorSrcColor")) { alphaDstFactor = sf::BlendMode::Factor::SrcColor; }
        if (ImGui::Button("AlphaDstFactorZero##BlendModeAlphaDstFactorZero")) { alphaDstFactor = sf::BlendMode::Factor::Zero; }

        ImGui::EndTable();
    }

    ImGui::End();

    linearBurn.colorEquation = (sf::BlendMode::Equation)colorEquation;
    linearBurn.alphaEquation = (sf::BlendMode::Equation)alphaEquation;
    linearBurn.colorSrcFactor = (sf::BlendMode::Factor)colorSrcFactor;
    linearBurn.colorDstFactor = (sf::BlendMode::Factor)colorDstFactor;
    linearBurn.alphaSrcFactor = (sf::BlendMode::Factor)alphaSrcFactor;
    linearBurn.alphaDstFactor = (sf::BlendMode::Factor)alphaDstFactor;

    // light.png
    // 2 2 3 2 8 8
    // 2 0 3 2 8 8

    // light2.png
    // 2 2 8 8 8 8
    // 2 2 5 8 8 8
    // 2 2 2 8 8 8

    m_renderWindow.draw(sprRt, linearBurn);

    return;
*/

    float renderWindowWidth = m_renderWindow.getSize().x;
    float renderWindowHeight = m_renderWindow.getSize().y;

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

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

void Game::drawInGameScreen()
{
    g_Map.getTileMapTiles(tb::ZAxis::Ground)->draw(m_renderWindow);
    g_Map.getTileMapTileEdges(tb::ZAxis::Ground)->draw(m_renderWindow);

    doAnimatedWater();
}

void Game::doAnimatedWater()
{
    // TODO: check if player is above ground

    sf::Time timeElapsed = m_animatedWaterClock.getElapsedTime();
    if (timeElapsed >= tb::Constants::WaterAnimationFrameTime)
    {
        if (g_Map.getTileMapTiles(tb::ZAxis::Ground)->doAnimatedWater() == false)
        {
            g_Log.write("ERROR: animated water failed\n");
        }

        m_animatedWaterClock.restart();
    }
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
    fmt::print("Press any key to continue...\n");

    int waitForKeyPress = std::cin.get();
}

void Game::run()
{
    g_Log.deleteContents();

    g_Log.open();

    g_Log.write("{} (Build: {} {})\n", tb::Constants::GameTitle, __DATE__, __TIME__);

    g_Log.write("Creating render window\n");
    createRenderWindow();

    g_Log.write("Loading sprite data\n");
    if (g_SpriteData.load() == false)
    {
        g_Log.write("ERROR: Failed to load sprite data\n");
        waitForKeyPress();
        return;
    }

    g_Log.write("Loading pattern data\n");
    if (g_PatternData.load() == false)
    {
        g_Log.write("ERROR: Failed to load pattern data\n");
        waitForKeyPress();
        return;
    }

    g_Log.write("Loading water data\n");
    if (g_WaterData.load() == false)
    {
        g_Log.write("ERROR: Failed to load water data\n");
        waitForKeyPress();
        return;
    }

    g_Log.write("Loading textures\n");
    if (loadTextures() == false)
    {
        g_Log.write("ERROR: Failed to load textures\n");
        waitForKeyPress();
        return;
    }

    g_Log.write("Loading bitmap fonts\n");
    if (loadBitmapFonts() == false)
    {
        g_Log.write("ERROR: Failed to load bitmap fonts\n");
        waitForKeyPress();
        return;
    }

    g_Log.write("Loading mouse cursors\n");
    m_cursorArrow.loadFromSystem(sf::Cursor::Arrow);

    g_Log.write("Loading map\n");
    if (g_Map.load("maps/test/test.tmx") == false)
    {
        g_Log.write("ERROR: Failed to load map\n");
        waitForKeyPress();
        return;
    }

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
        else if (m_gameState == tb::GameState::InGame);
        {
            drawInGameScreen();
        }

        g_MenuBar.draw();
        g_StatusBar.draw();

        if (m_showDemoWindow == true)
        {
            ImGui::ShowDemoWindow(&m_showDemoWindow);
        }

        if (m_showStackToolWindow == true)
        {
            ImGui::ShowStackToolWindow(&m_showStackToolWindow);
        }

        if (*g_SpriteEditorWindow.getIsVisible() == true)
        {
            g_SpriteEditorWindow.draw();
        }

        if (*g_SpriteDataWindow.getIsVisible() == true)
        {
            g_SpriteDataWindow.draw();
        }

        if (*g_LogWindow.getIsVisible() == true)
        {
            g_LogWindow.draw();
        }

        ImGui::SFML::Render(m_renderWindow);

        m_renderWindow.display();
    }

    ImGui::SFML::Shutdown();

    g_Log.close();

    //waitForKeyPress();
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

tb::GameState Game::getGameState()
{
    return m_gameState;
}

}
