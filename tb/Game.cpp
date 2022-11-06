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

void Game::initImGui()
{
    ImGui::SFML::Init(*g_RenderWindow.getWindow());

    // TODO: light mode vs dark mode
    ImGui::StyleColorsLight();

    ImGuiIO& imguiIO = ImGui::GetIO();

    imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    imguiIO.ConfigWindowsMoveFromTitleBarOnly = true;
    imguiIO.ConfigDockingWithShift = true;
}

bool Game::loadData()
{
    g_Log.write("Loading map data\n");
    if (g_MapData.load() == false)
    {
        g_Log.write("ERROR: Failed to load map data\n");
        return false;
    }

    g_Log.write("Loading texture data\n");
    if (g_TextureData.load() == false)
    {
        g_Log.write("ERROR: Failed to load texture data\n");
        return false;
    }

    g_Log.write("Loading sprite data\n");
    if (g_SpriteData.load() == false)
    {
        g_Log.write("ERROR: Failed to load sprite data\n");
        return false;
    }

    g_Log.write("Loading bitmap font data\n");
    if (g_BitmapFontData.load() == false)
    {
        g_Log.write("ERROR: Failed to load bitmap font data\n");
        return false;
    }

    g_Log.write("Loading pattern data\n");
    if (g_PatternData.load() == false)
    {
        g_Log.write("ERROR: Failed to load pattern data\n");
        return false;
    }

    g_Log.write("Loading water animation data\n");
    if (g_WaterAnimationData.load() == false)
    {
        g_Log.write("ERROR: Failed to load water animation data\n");
        return false;
    }

    g_Log.write("Loading outfit data\n");
    if (g_OutfitData.load() == false)
    {
        g_Log.write("ERROR: Failed to load outfit data\n");
        return false;
    }

    return true;
}

bool Game::loadTextures()
{
    unsigned int maximumTextureSize = sf::Texture::getMaximumSize();

    if (maximumTextureSize < m_minimumTextureSizeRequiredToRun)
    {
        g_Log.write("ERROR: Your computer supports a maximum texture size of {}\n", maximumTextureSize);
        g_Log.write("----> This game requires at least {} texture size in order to run\n", m_minimumTextureSizeRequiredToRun);
        return false;
    }

    if (g_TextureData.isLoaded() == false)
    {
        g_Log.write("ERROR: Texture data is not loaded\n");
        return false;
    }

    tb::TextureData::DataList* textureDataList = g_TextureData.getDataList();

    for (auto& textureData : *textureDataList)
    {
        bool isFound = false;

        for (auto& [textureName, textureObject] : tb::Textures::Names)
        {
            if (textureData.Name == textureName)
            {
                if (textureObject.loadFromFile(textureData.FileName, sf::IntRect(0, 0, textureData.Width, textureData.Height)) == true)
                {
                    // tiled textures
                    if (textureData.Repeated == true)
                    {
                        textureObject.setRepeated(true);
                    }

                    isFound = true;

                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded texture '{}' from file: {}\n", textureData.Name, textureData.FileName);
        }
        else
        {
            g_Log.write("ERROR: Failed to load texture '{}' from file: {}\n", textureData.Name, textureData.FileName);
            return false;
        }
    }

    return true;
}

bool Game::loadBitmapFonts()
{
    if (g_BitmapFontData.isLoaded() == false)
    {
        g_Log.write("ERROR: Bitmap font data is not loaded\n");
        return false;
    }

    tb::BitmapFontData::DataList* bitmapFontDataList = g_BitmapFontData.getDataList();

    for (auto& bitmapFont : *bitmapFontDataList)
    {
        bool isFound = false;

        for (auto& [bitmapFontName, bitmapFontObject] : m_bitmapFontNames)
        {
            if (bitmapFont.Name == bitmapFontName)
            {
                if (bitmapFontObject.load(bitmapFont.FileName, sf::Vector2u(bitmapFont.GlyphWidth, bitmapFont.GlyphHeight), bitmapFont.TextHeight, &bitmapFont.GlyphWidthList) == true)
                {
                    isFound = true;

                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded bitmap font '{}' from file: {}\n", bitmapFont.Name, bitmapFont.FileName);
        }
        else
        {
            g_Log.write("ERROR: Failed to load bitmap font '{}' from file: {}\n", bitmapFont.Name, bitmapFont.FileName);
            return false;
        }
    }

    return true;
}

bool Game::loadMap(const std::string& fileName)
{
    g_Log.write("Loading map\n");
    if (g_Map.load(fileName) == false)
    {
        g_Log.write("ERROR: Failed to load map\n");
        return false;
    }

    g_Log.write("Creating player\n");
    if (createPlayer() == false)
    {
        g_Log.write("ERROR: Failed to create player\n");
        return false;
    }

    return true;
}

void Game::drawDockSpace()
{
    ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_None;
    dockSpaceWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    dockSpaceWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float menuBarHeight = g_MenuBar.getHeight();
    const float statusBarHeight = g_StatusBar.getHeight();

    ImVec2 windowPosition = viewport->Pos;
    windowPosition.y += menuBarHeight;

    ImVec2 windowSize = viewport->Size;
    windowSize.y = windowSize.y - statusBarHeight + menuBarHeight;

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
}

void Game::drawWoodBackground()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2u renderWindowSize = g_RenderWindow.getWindow()->getSize();

    sf::Sprite wood;
    wood.setTexture(tb::Textures::Wood);
    wood.setTextureRect(sf::IntRect(0, 0, renderWindowSize.x, renderWindowSize.y));

    renderWindow->draw(wood);
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

    unsigned int woodHorizontal1Height = tb::Textures::WoodHorizontal1.getSize().y;
    unsigned int woodHorizontal2Height = tb::Textures::WoodHorizontal2.getSize().y;

    unsigned int woodVertical1Width = tb::Textures::WoodVertical1.getSize().x;
    unsigned int woodVertical2Width = tb::Textures::WoodVertical2.getSize().x;

    woodHorizontal1.setPosition(sf::Vector2f(rect.left - 3.0f, rect.top - 3.0f));
    woodHorizontal1.setTextureRect(sf::IntRect(0, 0, static_cast<int>(rect.width + 6.0f), woodHorizontal1Height));

    woodHorizontal2.setPosition(sf::Vector2f(rect.left - 3.0f, rect.top + rect.height));
    woodHorizontal2.setTextureRect(sf::IntRect(0, 0, static_cast<int>(rect.width + 6.0f), woodHorizontal2Height));

    woodVertical1.setPosition(sf::Vector2f(rect.left - 3.0f, rect.top));
    woodVertical1.setTextureRect(sf::IntRect(0, 0, woodVertical1Width, static_cast<int>(rect.height)));

    woodVertical2.setPosition(sf::Vector2f(rect.left + rect.width, rect.top));
    woodVertical2.setTextureRect(sf::IntRect(0, 0, woodVertical2Width, static_cast<int>(rect.height)));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(woodHorizontal1);
    renderWindow->draw(woodHorizontal2);
    renderWindow->draw(woodVertical1);
    renderWindow->draw(woodVertical2);
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

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    float renderWindowWidth = static_cast<float>(renderWindow->getSize().x);
    float renderWindowHeight = static_cast<float>(renderWindow->getSize().y);

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    sf::RectangleShape blackBorder(sf::Vector2f(renderWindowWidth - 20.0f, renderWindowHeight - 20.0f - menuBarHeight - statusBarHeight));
    blackBorder.setFillColor(sf::Color(0, 0, 0));
    blackBorder.setPosition(sf::Vector2f(10.0f, 10.0f + menuBarHeight));

    sf::RectangleShape backgroundTexture(sf::Vector2f(renderWindowWidth - 20.0f - 2.0f, renderWindowHeight - 20.0f - 2.0f - menuBarHeight - statusBarHeight));
    backgroundTexture.setTexture(&texture);
    backgroundTexture.setPosition(sf::Vector2f(10.0f + 1.0f, 10.0f + 1.0f + menuBarHeight));

    renderWindow->draw(blackBorder);
    renderWindow->draw(backgroundTexture);

    drawWoodBorder(blackBorder.getGlobalBounds());
}

void Game::doGameStateEnterGame()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::EnterGame);

    if (*g_EnterGameWindow.getIsVisible() == true)
    {
        g_EnterGameWindow.draw();
    }
}

void Game::doGameStateLoading()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::Loading);

    if (m_numLoadingFrames > 1)
    {
        if (m_loadMapFileName.size() != 0)
        {
            if (loadMap(m_loadMapFileName) == true)
            {
                setGameState(tb::GameState::InGame);
            }
            else
            {
                setGameState(tb::GameState::MapSelect);

                g_MapSelectWindow.setIsVisible(true);
            }

            m_loadMapFileName = "";

            m_loadMapFileName.clear();
        }

        m_numLoadingFrames = 0;
    }

    m_numLoadingFrames++;
}

void Game::doGameStateMapSelect()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::MapSelect);

    if (*g_MapSelectWindow.getIsVisible() == true)
    {
        g_MapSelectWindow.draw();
    }
    else
    {
        setGameState(tb::GameState::EnterGame);
    }
}

void Game::doGameStateInGame()
{
    g_GameWindow.draw();

    doAnimatedWater();
}

void Game::doAnimatedWater()
{
    // do not animate water while underground
    if (m_player->getZ() < tb::ZAxis::Default)
    {
        return;
    }

    sf::Time timeElapsed = m_animatedWaterClock.getElapsedTime();
    if (timeElapsed >= tb::Constants::WaterAnimationFrameTime)
    {
        sf::IntRect gameWindowTileRect = g_GameWindow.getTileRect();

        if (g_Map.getTileMapTiles(tb::ZAxis::Default)->doAnimatedWater(gameWindowTileRect) == false)
        {
            g_Log.write("ERROR: animated water failed\n");
        }

        m_animatedWaterClock.restart();
    }
}

bool Game::isMouseInsideImGuiWindow()
{
    auto io = ImGui::GetIO();

    if (io.WantCaptureKeyboard == true || io.WantCaptureMouse == true)
    {
        return true;
    }

    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == true)
    {
        return true;
    }

    if (ImGui::IsAnyItemHovered() == true)
    {
        return true;
    }

    return false;
}

sf::Vector2i Game::getMousePositionInDesktop()
{
    // get mouse position in operating system desktop
    return sf::Mouse::getPosition();
}

bool Game::createPlayer()
{
    tb::Map::Properties_t* mapProperties = g_Map.getProperties();

    tb::Creature::Ptr player = std::make_shared<tb::Creature>
    (
        sf::Vector2i(mapProperties->PlayerStartX, mapProperties->PlayerStartY),
        mapProperties->PlayerStartZ
    );

    tb::Creature::Properties_t* playerProperties = player->getProperties();
    playerProperties->IsPlayer = true;
    playerProperties->HasOutfit = true;

    std::string playerName = g_EnterGameWindow.getCharacterName();
    if (playerName.size() == 0)
    {
        playerName = tb::Constants::PlayerNameDefault;
    }

    player->setName(playerName);

    m_player = player;

    tb::Tile::Ptr tile = g_Map.getTileOfThing(m_player);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addCreature(m_player);

    g_Log.write("tile index: {}\n", tile->getTileIndex());
    g_Log.write("tile x: {}\n", tile->getTileX());
    g_Log.write("tile y: {}\n", tile->getTileY());
    g_Log.write("tile z: {}\n", tile->getZ());
    g_Log.write("tile sprite id: {}\n", tile->getSpriteID());

    g_Log.write("player coords: {},{},{}\n", m_player->getTileX(), m_player->getTileY(), m_player->getZ());

    return true;
}

void Game::handleClosedEvent(sf::Event event)
{
    g_RenderWindow.handleClosedEvent(event);
}

void Game::handleResizedEvent(sf::Event event)
{
    g_RenderWindow.handleResizedEvent(event);
}

void Game::handleMouseWheelMovedEvent(sf::Event event)
{
    g_GameWindow.handleMouseWheelMovedEvent(event);
}

void Game::handleMouseButtonPressedEvent(sf::Event event)
{
    g_GameWindow.handleMouseButtonPressedEvent(event);

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        //
    }
}

void Game::handleMouseButtonReleasedEvent(sf::Event event)
{
    g_GameWindow.handleMouseButtonReleasedEvent(event);

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if (m_gameState == tb::GameState::EnterGame)
        {
            g_EnterGameWindow.setIsVisible(true);
        }
    }
}

void Game::processEvents()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Event event;
    while (renderWindow->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(*renderWindow, event);

        if (event.type == sf::Event::Closed)
        {
            handleClosedEvent(event);
        }
        else if (event.type == sf::Event::Resized)
        {
            handleResizedEvent(event);
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (isMouseInsideImGuiWindow() == false)
            {
                handleMouseButtonPressedEvent(event);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (isMouseInsideImGuiWindow() == false)
            {
                handleMouseButtonReleasedEvent(event);
            }
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            if (isMouseInsideImGuiWindow() == false)
            {
                handleMouseWheelMovedEvent(event);
            }
        }
    }
}

void Game::fixMouseCursorForWindowResize(sf::RenderWindow* renderWindow)
{
    // this function fixes a bug between imgui, SFML and imgui-SFML
    // where the mouse cursor doesn't work correctly when resizing the window

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

            renderWindow->setMouseCursor(m_arrowCursor);
        }
        imguiHasCursorPrev = imguiHasCursor;
    }
}

void Game::createTileFileFromImageFile(const std::string& fileName)
{
    std::fstream file;
    file.open("tiles.txt", std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("ERROR: Cannot open file: tiles.txt\n");
        return;
    }

    sf::Image image;
    if (image.loadFromFile(fileName) == false)
    {
        g_Log.write("ERROR: Cannot open file: {}\n", fileName);
        return;
    }

    // TODO: rotate image 90 degrees clockwise
    // TODO: flip image horizontal

    unsigned int imageWidth = image.getSize().x;
    unsigned int imageHeight = image.getSize().y;

    tb::SpriteIDList spriteIDList;

    for (unsigned int i = 0; i < imageWidth; i++)
    {
        for (unsigned int j = 0; j < imageHeight; j++)
        {
            sf::Color pixelColor = image.getPixel(i, j);

            //g_Log.write("pixelColor: {},{},{}\n", pixelColor.r, pixelColor.g, pixelColor.b);

            tb::SpriteID_t spriteID = 1;

            if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0)
            {
                // black = void
                spriteID = 0;
            }
            else if (pixelColor.r == 255 && pixelColor.g == 255 && pixelColor.b == 255)
            {
                // white = text
                spriteID = 17;
            }
            else if (pixelColor.r == 255 && pixelColor.g == 0 && pixelColor.b == 0)
            {
                // red = solid
                spriteID = 463;
            }
            else if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 255)
            {
                // blue = water
                spriteID = 69;
            }
            else if (pixelColor.r == 0 && pixelColor.g == 255 && pixelColor.b == 0)
            {
                // green = grass
                spriteID = 2;
            }
            else if (pixelColor.r == 0 && pixelColor.g == 64 && pixelColor.b == 0)
            {
                // dark green = trees
                spriteID = 25;
            }
            else if (pixelColor.r == 192 && pixelColor.g == 192 && pixelColor.b == 192)
            {
                // gray = cobblestone
                spriteID = 77;
            }
            else if (pixelColor.r == 64 && pixelColor.g == 64 && pixelColor.b == 64)
            {
                // dark gray = unknown
                spriteID = 44;
            }
            else if (pixelColor.r == 128 && pixelColor.g == 64 && pixelColor.b == 0)
            {
                // brown = dirt
                spriteID = 5;
            }
            else if (pixelColor.r == 255 && pixelColor.g == 255 && pixelColor.b == 0)
            {
                // yellow = stairs
                spriteID = 457;
            }

            //g_Log.write("spriteID: {}\n", spriteID);

            spriteIDList.push_back(spriteID);
        }
    }

    size_t spriteIDListSize = spriteIDList.size();

    for (unsigned int i = 0; i < spriteIDListSize; i++)
    {
        file << spriteIDList.at(i);

        if (i < spriteIDListSize - 1)
        {
            file << ",";
        }

        if (i != 0 && i % imageWidth == 0)
        {
            file << "\n";
        }
    }

    file.close();
}

void Game::doOverlayText()
{
    g_OverlayWindow.clearTextList();

    std::string playerCoordsText = std::format("Player X,Y,Z: {},{},{}\n", m_player->getTileX(), m_player->getTileY(), m_player->getZ());

    g_OverlayWindow.addTextToList(playerCoordsText);

    sf::Vector2i mousePositionInDesktop = getMousePositionInDesktop();

    std::string mousePositionInDesktopText = std::format("Desktop Mouse Position: {},{}\n", mousePositionInDesktop.x, mousePositionInDesktop.y);

    g_OverlayWindow.addTextToList(mousePositionInDesktopText);

    sf::Vector2f mousePositionInRenderWindow = g_RenderWindow.getMousePosition();

    std::string mousePositionInRenderWindowText = std::format("Render Window Mouse Position: {},{}\n", static_cast<int>(mousePositionInRenderWindow.x), static_cast<int>(mousePositionInRenderWindow.y));

    g_OverlayWindow.addTextToList(mousePositionInRenderWindowText);

    sf::Vector2f mousePixelCoordsInGameWindow = g_GameWindow.getMousePixelCoords();

    std::string mousePixelCoordsInGameWindowText = std::format("Game Window Mouse Pixel Coords: {},{}\n", mousePixelCoordsInGameWindow.x, mousePixelCoordsInGameWindow.y);

    g_OverlayWindow.addTextToList(mousePixelCoordsInGameWindowText);

    sf::Vector2i mouseTileCoordsInGameWindow = g_GameWindow.getMouseTileCoords();

    std::string mouseTileCoordsInGameWindowText = std::format("Game Window Mouse Tile Coords: {},{}\n", mouseTileCoordsInGameWindow.x, mouseTileCoordsInGameWindow.y);

    g_OverlayWindow.addTextToList(mouseTileCoordsInGameWindowText);
}

void Game::waitForKeyPress()
{
    g_Log.write("Press any key to continue...\n");

    std::cin.get();
}

void Game::exit()
{
    g_Log.write("Exiting...\n");

    ImGui::SFML::Shutdown();

    g_Log.close();

    waitForKeyPress();
}

void Game::run()
{
    g_Log.deleteContents();

    g_Log.open();

    g_Log.write("{} (Build: {} {})\n", tb::Constants::GameTitle, __DATE__, __TIME__);

    // TODO: LOAD CONFIG

    g_Log.write("Creating render window\n");
    if (g_RenderWindow.create() == false)
    {
        g_Log.write("ERROR: Failed to create render window\n");
        exit();
        return;
    }

    g_Log.write("Initializing ImGui\n");
    initImGui();

    g_Log.write("Loading data\n");
    if (loadData() == false)
    {
        g_Log.write("ERROR: Failed to load data\n");
        exit();
        return;
    }

    g_Log.write("Loading textures\n");
    if (loadTextures() == false)
    {
        g_Log.write("ERROR: Failed to load textures\n");
        exit();
        return;
    }

    g_Log.write("Loading bitmap fonts\n");
    if (loadBitmapFonts() == false)
    {
        g_Log.write("ERROR: Failed to load bitmap fonts\n");
        exit();
        return;
    }

    g_Log.write("Loading mouse cursors\n");
    // TODO: load all the cursors
    m_arrowCursor.loadFromSystem(sf::Cursor::Arrow);

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();
    if (renderWindow == nullptr)
    {
        g_Log.write("ERROR: Render window not found\n");
        exit();
        return;
    }

    g_Log.write("Start rendering...\n");

    while (renderWindow->isOpen() == true)
    {
        processEvents();

        fixMouseCursorForWindowResize(renderWindow);

        ImGui::SFML::Update(*renderWindow, m_deltaClock.restart());

        renderWindow->clear(sf::Color::Magenta);

        drawWoodBackground();

        if (m_gameState == tb::GameState::EnterGame)
        {
            doGameStateEnterGame();
        }
        else if (m_gameState == tb::GameState::MapSelect)
        {
            doGameStateMapSelect();
        }
        else if (m_gameState == tb::GameState::Loading)
        {
            doGameStateLoading();
        }
        else if (m_gameState == tb::GameState::InGame)
        {
            doGameStateInGame();

            doOverlayText();
        }

        g_MenuBar.draw();
        g_StatusBar.draw();

        drawDockSpace();

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

        if (m_gameState == tb::GameState::InGame)
        {
            if (*g_OverlayWindow.getIsVisible() == true)
            {
                g_OverlayWindow.draw();
            }
        }

        ImGui::SFML::Render(*renderWindow);

        renderWindow->display();
    }

    exit();
}

void Game::endGame()
{
    g_Game.setGameState(tb::GameState::EnterGame);
}

void Game::toggleDemoWindow()
{
    tb::Utility::toggleBool(m_showDemoWindow);
}

void Game::toggleStackToolWindow()
{
    tb::Utility::toggleBool(m_showStackToolWindow);
}

tb::GameState Game::getGameState()
{
    return m_gameState;
}

void Game::setGameState(tb::GameState gameState)
{
    m_gameState = gameState;
}

tb::Creature::Ptr Game::getPlayer()
{
    return m_player;
}

void Game::setLoadMapFileName(const std::string& fileName)
{
    m_loadMapFileName = fileName;
}

}
