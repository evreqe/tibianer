#include "tb/Game.h"

namespace tb
{

Game::Game()
{
    m_gameWindow.create(tb::Constants::GameWindowPixelWidth, tb::Constants::GameWindowPixelHeight);
    m_gameWindowLayer.create(tb::Constants::GameWindowPixelWidth, tb::Constants::GameWindowPixelHeight);

    m_gameWindowView.reset(sf::FloatRect(0.0f, 0.0f, tb::Constants::GameWindowPixelWidth, tb::Constants::GameWindowPixelHeight));
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

    imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    imguiIO.ConfigWindowsMoveFromTitleBarOnly = true;
    imguiIO.ConfigDockingWithShift = true;
}

bool Game::loadTextures()
{
    if (auto maximumTextureSize = sf::Texture::getMaximumSize(); maximumTextureSize < m_minimumTextureSizeRequiredToRun)
    {
        g_Log.write("Your computer supports a maximum texture size of {}\n", maximumTextureSize);
        g_Log.write("ERROR: This game requires at least {} texture size in order to play\n", m_minimumTextureSizeRequiredToRun);
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

    if (m_bitmapFontTiny.load(tb::BitmapFonts::Tiny::FileName, tb::BitmapFonts::Tiny::GlyphSize, &tb::BitmapFonts::Tiny::GlyphWidthList) == false)
    {
        return false;
    }

    if (m_bitmapFontModern.load(tb::BitmapFonts::Modern::FileName, tb::BitmapFonts::Modern::GlyphSize, &tb::BitmapFonts::Modern::GlyphWidthList) == false)
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
    drawGameWindow();

    doAnimatedWater();
}

void Game::drawGameWindow()
{
    m_gameWindowView.setCenter
    (
        m_player->getPixelX() + tb::Constants::TileSizeHalf,
        m_player->getPixelY() + tb::Constants::TileSizeHalf
    );

    m_gameWindow.setView(m_gameWindowView);
    m_gameWindow.clear(sf::Color::Red);

    tb::ZAxis_t zBegin = tb::ZAxis::Min;
    tb::ZAxis_t zEnd   = tb::ZAxis::Max;

    // check if the player is underground
    if (m_player->getZ() < tb::ZAxis::Default)
    {
        // draw from the bottom to 1 level below the default
        // this will draw everything that is underground
        zBegin = tb::ZAxis::Min;
        zEnd   = tb::ZAxis::Default - 1;
    }
    else
    {
        // draw from the default level to the top
        // this will draw everything that is aboveground
        zBegin = tb::ZAxis::Default;
        zEnd   = tb::ZAxis::Max;
    }

    //g_Log.write("zBegin,zEnd: {},{}\n", zBegin, zEnd);

    for (tb::ZAxis_t i = zBegin; i < zEnd + 1; i++)
    {
        auto tileMapTiles = g_Map.getTileMapTiles(i);

        if (isTileMapVisible(tileMapTiles) == true)
        {
            //g_Log.write("drawGameLayer: {}\n", i);

            drawGameLayer(i);
        }
    }

/*
    for (tb::ZAxis_t i = zBegin; i < zEnd + 1; i++)
    {
        m_tileMapObjects[i].clear();
        m_tileMapCreatures[i].clear();
        m_tileMapAnimations[i].clear();
        m_tileMapProjectiles[i].clear();
        m_tileMapThings[i].clear();

        //updateTileThings(&m_map.tileMapTiles[i]); // lags too much here, updated elsewhere
    }
*/

    //std::cout << "drawGameLayer START ------------------" << std::endl;

/*
    for (unsigned int i = zBegin; i < zEnd + 1; i++)
    {
        if (isTileMapVisible(&m_map.tileMapTiles[i]) == true)
        {
            drawGameLayer(i);

            //std::cout << "drawGameLayer: " << i << std::endl;
        }

        if (i == tibia::ZAxis::max)
        {
            break;
        }

        if (findTilesAboveThing(m_player, i + 1) == true)
        {
            break;
        }
    }
*/

    //std::cout << "drawGameLayer STOP -------------------" << std::endl;

    //doRayCast(m_player->getTilePosition(), sf::Vector2u(0, 0), m_player->getZ());

    //drawFloatingTextList();
    //drawGameTextList();

    //drawGameWindowText();

    m_gameWindow.display();

    m_gameWindowSprite.setTexture(m_gameWindow.getTexture());
    m_gameWindowSprite.setPosition(32.0f, 32.0f);

    m_renderWindow.draw(m_gameWindowSprite);
}

void Game::drawGameLayer(tb::ZAxis_t z)
{
    m_gameWindowLayer.setView(m_gameWindowView);
    m_gameWindowLayer.clear(sf::Color::Transparent);

    auto tilesToDrawRect = getTilesToDrawRect();

    g_Map.getTileMapTiles(z)->draw(tilesToDrawRect, m_gameWindowLayer);
    g_Map.getTileMapTileEdges(z)->draw(tilesToDrawRect, m_gameWindowLayer);

    m_gameWindowLayer.display();

    m_gameWindowLayerSprite.setTexture(m_gameWindowLayer.getTexture());

    m_gameWindowLayerSprite.setPosition
    (
        (tilesToDrawRect.left + 1) * tb::Constants::TileSize,
        (tilesToDrawRect.top  + 1) * tb::Constants::TileSize
    );

    m_gameWindow.draw(m_gameWindowLayerSprite);
}

sf::IntRect Game::getTilesToDrawRect()
{
    int x1 = m_player->getTileX();
    int y1 = m_player->getTileY();

    x1 = x1 - tb::Constants::GameWindowNumTilesFromCenterX - tb::Constants::GameWindowNumTilesToDrawFromOffscreen;
    y1 = y1 - tb::Constants::GameWindowNumTilesFromCenterY - tb::Constants::GameWindowNumTilesToDrawFromOffscreen;

    int x2 = tb::Constants::GameWindowTileWidth  + (tb::Constants::GameWindowNumTilesToDrawFromOffscreen + 1);
    int y2 = tb::Constants::GameWindowTileHeight + (tb::Constants::GameWindowNumTilesToDrawFromOffscreen + 1);

    return sf::IntRect(x1, y1, x2, y2);
}

bool Game::isTileMapVisible(tb::TileMap* tileMap)
{
    tb::Tile::List* tileList = tileMap->getTileList();

    if (tileList->size() == 0)
    {
        return false;
    }

    auto tilesToDrawRect = getTilesToDrawRect();

    int x1 = tilesToDrawRect.left;
    int y1 = tilesToDrawRect.top;

    int x2 = tilesToDrawRect.width;
    int y2 = tilesToDrawRect.height;

    for (int i = x1; i < x1 + x2; i++)
    {
        for (int j = y1; j < y1 + y2; j++)
        {
            if (i < 0) continue;
            if (j < 0) continue;

            if (i > g_Map.getTileWidth() - 1) continue;
            if (j > g_Map.getTileHeight() - 1) continue;

            uint32_t tileIndex = i + j * g_Map.getTileWidth();

            if (g_Map.isTileIndexOutOfBounds(tileIndex) == true)
            {
                continue;
            }

            tb::Tile::Ptr tile = tileList->at(tileIndex);

            if (tile == nullptr)
            {
                continue;
            }

            tb::SpriteID_t tileSpriteID = tile->getSpriteID();

            if (tileSpriteID != tb::Constants::SpriteIDNull)
            {
                return true;
            }
        }
    }

    return false;
}

tb::Tile::Ptr Game::getTileOfThing(tb::Thing::Ptr thing)
{
    if (thing == nullptr)
    {
        return nullptr;
    }

    auto tileList = g_Map.getTileMapTiles(thing->getZ())->getTileList();

    if (tileList->size() == 0)
    {
        return nullptr;
    }

    uint32_t tileIndex = g_Map.getTileIndexByTileCoords(thing->getTileCoords());

    if (g_Map.isTileIndexOutOfBounds(tileIndex) == true)
    {
        g_Log.write("ERROR: tile index is out of bounds: {}\n", tileIndex);
        return nullptr;
    }

    return tileList->at(tileIndex);
}

void Game::doAnimatedWater()
{
    // TODO: check if player is above ground

    sf::Time timeElapsed = m_animatedWaterClock.getElapsedTime();
    if (timeElapsed >= tb::Constants::WaterAnimationFrameTime)
    {
        if (g_Map.getTileMapTiles(tb::ZAxis::Default)->doAnimatedWater() == false)
        {
            g_Log.write("ERROR: animated water failed\n");
        }

        m_animatedWaterClock.restart();
    }
}

bool Game::createPlayer()
{
    auto mapProperties = g_Map.getProperties();

    auto player = std::make_shared<tb::Creature>
    (
        sf::Vector2u(mapProperties->PlayerStartX, mapProperties->PlayerStartY),
        mapProperties->PlayerStartZ
    );

    auto playerProperties = player->getProperties();
    playerProperties->IsPlayer = true;
    playerProperties->HasOutfit = true;

    player->setName(tb::Constants::PlayerNameDefault);

    m_player = player;

    tb::Tile::Ptr tile = getTileOfThing(m_player);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: nullptr\n");
        return false;
    }

    tile->addCreature(m_player);

    g_Log.write("tile sprite id: {}\n", tile->getSpriteID());
    g_Log.write("tile x: {}\n", tile->getTileX());
    g_Log.write("tile y: {}\n", tile->getTileY());
    g_Log.write("tile z: {}\n", tile->getZ());
    g_Log.write("tile index: {}\n", tile->getTileIndex());

    g_Log.write("Player coords: {},{},{}\n", m_player->getTileX(), m_player->getTileY(), m_player->getZ());

    return true;
}

void Game::handleMouseWheelEvent(sf::Event event)
{
    // scroll up
    if (event.mouseWheel.delta > 0)
    {
        // zoom in

        m_gameWindowZoomLevel -= m_gameWindowZoomFactor;

        if (m_gameWindowZoomLevel < 1.0f) m_gameWindowZoomLevel = 1.0f;

        m_gameWindowView.setSize(sf::Vector2f(tb::Constants::GameWindowPixelWidth * m_gameWindowZoomLevel, tb::Constants::GameWindowPixelHeight * m_gameWindowZoomLevel));
    }

    // scroll down
    else if (event.mouseWheel.delta < 0)
    {
        // zoom out

        m_gameWindowZoomLevel += m_gameWindowZoomFactor;

        m_gameWindowView.setSize(sf::Vector2f(tb::Constants::GameWindowPixelWidth * m_gameWindowZoomLevel, tb::Constants::GameWindowPixelHeight * m_gameWindowZoomLevel));
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_renderWindow.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(m_renderWindow, event);

        if (event.type == sf::Event::Closed)
        {
            m_renderWindow.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            // stretch to fill window
            sf::FloatRect visibleArea(0.0f, 0.0f, event.size.width, event.size.height);
            m_renderWindow.setView(sf::View(visibleArea));
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                auto io = ImGui::GetIO();
                if (io.WantCaptureKeyboard == false && io.WantCaptureMouse == false)
                {
                    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == false)
                    {
                        if (ImGui::IsAnyItemHovered() == false)
                        {
                            ::MessageBoxA(NULL, "right-clicked", "Mouse", MB_ICONINFORMATION);
                        }
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            handleMouseWheelEvent(event);
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
    g_Log.write("Press any key to continue...\n");

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

    g_Log.write("Loading outfit data\n");
    if (g_OutfitData.load() == false)
    {
        g_Log.write("ERROR: Failed to load outfit data\n");
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

    g_Log.write("Creating player\n");
    createPlayer();

    while (m_renderWindow.isOpen() == true)
    {
        g_OverlayWindow.clearTextList();

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

        std::string playerCoordsText = std::format("Player X,Y,Z: {},{},{}\n", m_player->getTileX(), m_player->getTileY(), m_player->getZ());

        g_OverlayWindow.addTextToList(playerCoordsText);

        g_MenuBar.draw();
        g_StatusBar.draw();

        ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_None;
        dockSpaceWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        dockSpaceWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImVec2 windowPosition = viewport->Pos;
        windowPosition.y += tb::Constants::MenuBarHeight;

        ImVec2 windowSize = viewport->Size;
        windowSize.y -= tb::Constants::StatusBarHeight + tb::Constants::MenuBarHeight;

        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::SetNextWindowPos(windowPosition);
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        bool isDockSpaceVisible = true;

        ImGui::Begin("DockSpace", &isDockSpaceVisible, dockSpaceWindowFlags);

        ImGui::PopStyleVar(3);

        ImGuiID dockSpaceID = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);

        ImGui::End();

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

        if (*g_OverlayWindow.getIsVisible() == true)
        {
            g_OverlayWindow.draw();
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
