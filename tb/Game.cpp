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

Game::Properties_t* Game::getProperties()
{
    return &m_properties;
}

Game::GuiProperties_t* Game::getGuiProperties()
{
    return &m_guiProperties;
}

void Game::initImGui()
{
    ImGui::SFML::Init(*g_RenderWindow.getWindow());

    ImGui::StyleColorsLight();

    ImGuiStyle* style = &ImGui::GetStyle();

    style->FrameBorderSize = 1.0f;
    style->TabBorderSize = 1.0f;

    ImGuiIO& imguiIO = ImGui::GetIO();

    imguiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    imguiIO.ConfigWindowsMoveFromTitleBarOnly = true;
    imguiIO.ConfigDockingWithShift = true;
}

bool Game::loadConfig()
{
    g_Log.write("Loading options data\n");
    if (g_OptionsData.load() == false)
    {
        g_Log.write("ERROR: Failed to load options data\n");
        return false;
    }

    g_Log.write("Loading hotkeys data\n");
    if (g_HotkeysData.load() == false)
    {
        g_Log.write("ERROR: Failed to load hotkeys data\n");
        return false;
    }

    return true;
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

    g_Log.write("Loading font data\n");
    if (g_FontData.load() == false)
    {
        g_Log.write("ERROR: Failed to load font data\n");
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

    g_Log.write("Loading outfit sprites data\n");
    if (g_OutfitSpritesData.load() == false)
    {
        g_Log.write("ERROR: Failed to load outfit sprites data\n");
        return false;
    }

    g_Log.write("Loading message of the day data\n");
    if (g_MessageOfTheDayData.load() == false)
    {
        g_Log.write("ERROR: Failed to load message of the day data\n");
        return false;
    }

    g_Log.write("Loading click rect data\n");
    if (g_ClickRectData.load() == false)
    {
        g_Log.write("ERROR: Failed to load click rect data\n");
        return false;
    }

    g_Log.write("Loading gui rect data\n");
    if (g_GuiRectData.load() == false)
    {
        g_Log.write("ERROR: Failed to load GUI rect data\n");
        return false;
    }

    g_Log.write("Loading cursor data\n");
    if (g_CursorData.load() == false)
    {
        g_Log.write("ERROR: Failed to load cursor data\n");
        return false;
    }

    g_Log.write("Loading animation data\n");
    if (g_AnimationData.load() == false)
    {
        g_Log.write("ERROR: Failed to load animation data\n");
        return false;
    }

    g_Log.write("Loading map generator data\n");
    if (g_MapGeneratorData.load() == false)
    {
        g_Log.write("ERROR: Failed to load map generator data\n");
        return false;
    }

    g_Log.write("Loading map generator pixel data\n");
    if (g_MapGeneratorPixelData.load() == false)
    {
        g_Log.write("ERROR: Failed to load map generator pixel data\n");
        return false;
    }

    return true;
}

bool Game::loadGlobalsFromData()
{
    g_Log.write("Loading textures\n");
    if (loadTextures() == false)
    {
        g_Log.write("ERROR: Failed to load textures\n");
        return false;
    }

    g_Log.write("Loading fonts\n");
    if (loadFonts() == false)
    {
        g_Log.write("ERROR: Failed to load fonts\n");
        return false;
    }

    g_Log.write("Loading bitmap fonts\n");
    if (loadBitmapFonts() == false)
    {
        g_Log.write("ERROR: Failed to load bitmap fonts\n");
        return false;
    }

    g_Log.write("Loading cursors\n");
    if (loadCursors() == false)
    {
        g_Log.write("ERROR: Failed to load cursors\n");
        return false;
    }

    g_Log.write("Loading sprites\n");
    if (loadSprites() == false)
    {
        g_Log.write("ERROR: Failed to load sprites\n");
        return false;
    }

    g_Log.write("Loading animations\n");
    if (loadAnimations() == false)
    {
        g_Log.write("ERROR: Failed to load animations\n");
        return false;
    }

    g_Log.write("Loading GUI rects\n");
    if (loadGuiRects() == false)
    {
        g_Log.write("ERROR: Failed to load gui rects\n");
        return false;
    }

    return true;
}

bool Game::loadTextures()
{
    std::uint32_t maximumTextureSize = sf::Texture::getMaximumSize();

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

bool Game::loadFonts()
{
    if (g_FontData.isLoaded() == false)
    {
        g_Log.write("ERROR: Font data is not loaded\n");
        return false;
    }

    tb::FontData::DataList* fontDataList = g_FontData.getDataList();

    for (auto& fontData : *fontDataList)
    {
        bool isFound = false;

        for (auto& [fontName, fontObject] : tb::Fonts::Names)
        {
            if (fontData.Name == fontName)
            {
                if (fontObject.loadFromFile(fontData.FileName) == true)
                {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded font '{}' from file: {}\n", fontData.Name, fontData.FileName);
        }
        else
        {
            g_Log.write("ERROR: Failed to load font '{}' from file: {}\n", fontData.Name, fontData.FileName);
            return false;
        }
    }

    return true;
}

bool Game::loadBitmapFonts()
{
    if (g_BitmapFontData.isLoaded() == false)
    {
        g_Log.write("ERROR: Bitmap Font data is not loaded\n");
        return false;
    }

    tb::BitmapFontData::DataList* bitmapFontDataList = g_BitmapFontData.getDataList();

    for (auto& bitmapFontData : *bitmapFontDataList)
    {
        bool isFound = false;

        for (auto& [bitmapFontName, bitmapFontObject] : m_bitmapFontNames)
        {
            if (bitmapFontData.Name == bitmapFontName)
            {
                if
                (
                    bitmapFontObject.load
                    (
                        bitmapFontData.FileName,
                        sf::Vector2u(bitmapFontData.GlyphWidth, bitmapFontData.GlyphHeight),
                        bitmapFontData.CharacterSpace,
                        bitmapFontData.CharacterHeight,
                        &bitmapFontData.CharacterWidthList
                    ) == true
                )
                {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded bitmap font '{}' from file: {}\n", bitmapFontData.Name, bitmapFontData.FileName);
        }
        else
        {
            g_Log.write("ERROR: Failed to load bitmap font '{}' from file: {}\n", bitmapFontData.Name, bitmapFontData.FileName);
            return false;
        }
    }

    return true;
}

bool Game::loadCursors()
{
    if (g_CursorData.isLoaded() == false)
    {
        g_Log.write("ERROR: Cursor data is not loaded\n");
        return false;
    }

    // system cursors
    for (auto& [cursorType, cursorObject] : tb::Cursors::SystemCursorTypes)
    {
        cursorObject.loadFromSystem(cursorType);
    }

    tb::CursorData::DataList* cursorDataList = g_CursorData.getDataList();

    // custom cursors
    for (auto& cursorData : *cursorDataList)
    {
        bool isFound = false;

        for (auto& [cursorName, cursorObject] : tb::Cursors::CustomCursorNames)
        {
            if (cursorData.Name == cursorName)
            {
                const sf::Uint8* cursorPixels = cursorData.Image.getPixelsPtr();

                sf::Vector2u cursorWidth = sf::Vector2u(cursorData.Width, cursorData.Height);

                sf::Vector2u cursorHotSpot = sf::Vector2u(cursorData.HotSpotX, cursorData.HotSpotY);

                if (cursorObject.loadFromPixels(cursorPixels, cursorWidth, cursorHotSpot) == true)
                {
                    isFound = true;
                    break;
                }
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded cursor '{}' from file: {}\n", cursorData.Name, cursorData.FileName);
        }
        else
        {
            g_Log.write("ERROR: Failed to load cursor '{}' from file: {}\n", cursorData.Name, cursorData.FileName);
            return false;
        }
    }

    return true;
}

bool Game::loadSprites()
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: Sprite data is not loaded\n");
        return false;
    }

    tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

    for (auto& [spriteName, spriteID] : tb::Sprites::Names)
    {
        bool isFound = false;

        for (auto& spriteData : *spriteDataList)
        {
            if (spriteData.Name == spriteName)
            {
                spriteID = spriteData.SpriteID;

                isFound = true;
                break;
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded sprite '{}' to sprite ID: {}\n", spriteName, spriteID);
        }
        else
        {
            g_Log.write("ERROR: Failed to load sprite '{}' to sprite ID: {}\n", spriteName, spriteID);
            return false;
        }
    }

    return true;
}

bool Game::loadAnimations()
{
    if (g_AnimationData.isLoaded() == false)
    {
        g_Log.write("ERROR: Animation data is not loaded\n");
        return false;
    }

    tb::AnimationData::DataList* animationDataList = g_AnimationData.getDataList();

    for (auto& [animationName, animationIndex] : tb::Animations::Names)
    {
        bool isFound = false;

        for (auto& animationData : *animationDataList)
        {
            if (animationData.Name == animationName)
            {
                animationIndex = animationData.Index;

                isFound = true;
                break;
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded animation '{}' to index: {}\n", animationName, animationIndex);
        }
        else
        {
            g_Log.write("ERROR: Failed to load animation '{}' to index: {}\n", animationName, animationIndex);
            return false;
        }
    }

    return true;
}

bool Game::loadGuiRects()
{
    if (g_GuiRectData.isLoaded() == false)
    {
        g_Log.write("ERROR: GUI Rect data is not loaded\n");
        return false;
    }

    tb::GuiRectData::DataList* guiRectDataList = g_GuiRectData.getDataList();

    for (auto& [guiRectName, guiRect] : tb::GuiRects::Names)
    {
        bool isFound = false;

        for (auto& guiRectData : *guiRectDataList)
        {
            if (guiRectData.Name == guiRectName)
            {
                guiRect.left   = guiRectData.X;
                guiRect.top    = guiRectData.Y;
                guiRect.width  = guiRectData.Width;
                guiRect.height = guiRectData.Height;

                isFound = true;
                break;
            }
        }

        if (isFound == true)
        {
            g_Log.write("Loaded gui rect for '{}'\n", guiRectName);
        }
        else
        {
            g_Log.write("ERROR: Failed to load gui rect for '{}'\n", guiRectName);
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
        g_Log.write("ERROR: Failed to load map from file: {}\n", fileName);
        return false;
    }

    g_GameWindow.resetViewPositionOffset();

    g_Log.write("Creating player\n");
    if (createPlayer() == false)
    {
        g_Log.write("ERROR: Failed to create player\n");
    }

    return true;
}

void Game::loadMapUsingThread(const std::string& fileName)
{
    m_loadMapThread = std::async(std::launch::async, &Game::loadMap, &g_Game, fileName);
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

    ImGui::Begin("DockSpace##DockSpaceWindow", &isDockSpaceVisible, dockSpaceWindowFlags);

    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceID = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);

    ImGui::End();
}

void Game::drawFramesPerSecond()
{
    m_framesPerSecondCurrentTime = m_framesPerSecondClock.getElapsedTime();

    m_framesPerSecond = 1.0f / (m_framesPerSecondCurrentTime.asSeconds() - m_framesPerSecondPreviousTime.asSeconds());

    std::string framesPerSecondText = std::format("FPS: {}", std::floorf(m_framesPerSecond));

    tb::BitmapFontText framesPerSecondBitmapFontText;
    framesPerSecondBitmapFontText.setText(&m_tinyBitmapFont, framesPerSecondText, sf::Color::White);
    framesPerSecondBitmapFontText.setPosition(sf::Vector2f(1.0f, 1.0f + g_MenuBar.getHeight()));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(framesPerSecondBitmapFontText);

    m_framesPerSecondPreviousTime = m_framesPerSecondCurrentTime;
}

void Game::drawLoadingText()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Font loadingTextFont;
    if (loadingTextFont.loadFromFile("fonts/system.ttf") == false)
    {
        g_Log.write("ERROR: Failed to draw loading text\n");

        renderWindow->clear(sf::Color::Blue);
        renderWindow->display();

        return;
    }

    sf::Text loadingText;
    loadingText.setFont(loadingTextFont);
    loadingText.setCharacterSize(13);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setString("Loading...");

    sf::FloatRect loadingTextRect = loadingText.getLocalBounds();

    loadingText.setOrigin(sf::Vector2f(loadingTextRect.left + loadingTextRect.width / 2.0f, loadingTextRect.top + loadingTextRect.height / 2.0f));
    loadingText.setPosition(renderWindow->getView().getCenter());

    renderWindow->clear(sf::Color::Black);
    renderWindow->draw(loadingText);
    renderWindow->display();
}

sf::FloatRect Game::getGuiFullLayoutRect()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    const float paddingRenderWindow = tb::Constants::PaddingRenderWindow;

    sf::FloatRect layoutRect;
    layoutRect.left   = paddingRenderWindow;
    layoutRect.top    = paddingRenderWindow + menuBarHeight;
    layoutRect.width  = renderWindowSize.x - (paddingRenderWindow * 2.0f);
    layoutRect.height = renderWindowSize.y - (paddingRenderWindow * 2.0f) - menuBarHeight - statusBarHeight;

    return layoutRect;
}

sf::FloatRect Game::getGuiLeftLayoutRect()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float paddingRenderWindow = tb::Constants::PaddingRenderWindow;

    float guiRightLayoutWidth = tb::Constants::GuiRightLayoutWidthAsFloat * m_guiProperties.Scale;

    float paddingBetweenLeftAndRightLayoutRect = tb::Constants::PaddingBetweenLeftAndRightLayoutRect;

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    sf::FloatRect layoutRect;
    layoutRect.left   = paddingRenderWindow;
    layoutRect.top    = paddingRenderWindow + menuBarHeight;
    layoutRect.width  = renderWindowSize.x - (paddingRenderWindow * 2.0f) - guiRightLayoutWidth - paddingBetweenLeftAndRightLayoutRect;
    layoutRect.height = renderWindowSize.y - (paddingRenderWindow * 2.0f) - menuBarHeight - statusBarHeight;

    return layoutRect;
}

sf::FloatRect Game::getGuiRightLayoutRect()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float paddingRenderWindow = tb::Constants::PaddingRenderWindow;

    float guiRightLayoutWidth = tb::Constants::GuiRightLayoutWidthAsFloat * m_guiProperties.Scale;

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    sf::FloatRect layoutRect;
    layoutRect.left   = renderWindowSize.x - paddingRenderWindow - guiRightLayoutWidth;
    layoutRect.top    = paddingRenderWindow + menuBarHeight;
    layoutRect.width  = guiRightLayoutWidth;
    layoutRect.height = renderWindowSize.y - (paddingRenderWindow * 2.0f) - menuBarHeight - statusBarHeight;

    return layoutRect;
}

void Game::drawToolTip(const std::string& text)
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    tb::BitmapFontText bitmapFontText;
    bitmapFontText.setText(&m_tinyBitmapFont, text, sf::Color::White);

    sf::FloatRect bitmapFontRect = bitmapFontText.getRect();

    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());

    sf::RectangleShape shape;
    shape.setTexture(&tb::Textures::Wood);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    shape.setSize(sf::Vector2f(bitmapFontRect.width, bitmapFontRect.height));
    shape.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y + 16.0f));

    renderWindow->draw(shape);
}

void Game::drawWoodBackground()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2u renderWindowSize = renderWindow->getSize();

    sf::Sprite wood;
    wood.setTexture(tb::Textures::Wood);
    wood.setTextureRect(sf::IntRect(0, 0, renderWindowSize.x, renderWindowSize.y));

    renderWindow->draw(wood);
}

void Game::drawWoodBorder(sf::FloatRect rect, bool drawBlackRectangle)
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    if (drawBlackRectangle == true)
    {
        sf::RectangleShape blackRect;
        blackRect.setPosition(sf::Vector2f(rect.left, rect.top));
        blackRect.setSize(sf::Vector2f(rect.width, rect.height));
        blackRect.setFillColor(sf::Color::Transparent);
        blackRect.setOutlineColor(sf::Color::Black);
        blackRect.setOutlineThickness(1.0f);

        renderWindow->draw(blackRect);

        // enlarge the rectangle by 1 pixel to account for the black rectangle
        rect.left -= 1.0f;
        rect.top -= 1.0f;
        rect.width += 2.0f;
        rect.height += 2.0f;
    }

    sf::Sprite woodHorizontal;
    sf::Sprite woodHorizontal2;
    sf::Sprite woodVertical;
    sf::Sprite woodVertical2;

    woodHorizontal.setTexture(tb::Textures::WoodHorizontal);
    woodHorizontal2.setTexture(tb::Textures::WoodHorizontal2);
    woodVertical.setTexture(tb::Textures::WoodVertical);
    woodVertical2.setTexture(tb::Textures::WoodVertical2);

    sf::Vector2u woodHorizontalSize = tb::Textures::WoodHorizontal.getSize();
    sf::Vector2u woodHorizontal2Size = tb::Textures::WoodHorizontal2.getSize();

    sf::Vector2u woodVerticalSize = tb::Textures::WoodVertical.getSize();
    sf::Vector2u woodVertical2Size = tb::Textures::WoodVertical2.getSize();

    // top
    woodHorizontal.setPosition(sf::Vector2f((float)(rect.left - woodVerticalSize.x), (float)(rect.top - woodHorizontalSize.y)));
    woodHorizontal.setTextureRect(sf::IntRect(0, 0, (int)(rect.width + (woodVerticalSize.x * 2)), (int)woodHorizontalSize.y));

    // bottom
    woodHorizontal2.setPosition(sf::Vector2f((float)(rect.left - woodVertical2Size.x), rect.top + rect.height));
    woodHorizontal2.setTextureRect(sf::IntRect(0, 0, (int)(rect.width + (woodVertical2Size.x * 2)), (int)woodHorizontal2Size.y));

    // left
    woodVertical.setPosition(sf::Vector2f((float)(rect.left - woodVerticalSize.x), rect.top));
    woodVertical.setTextureRect(sf::IntRect(0, 0, (int)woodVerticalSize.x, (int)rect.height));

    // right
    woodVertical2.setPosition(sf::Vector2f(rect.left + rect.width, rect.top));
    woodVertical2.setTextureRect(sf::IntRect(0, 0, (int)woodHorizontal2Size.y, (int)rect.height));

    renderWindow->draw(woodHorizontal);
    renderWindow->draw(woodHorizontal2);
    renderWindow->draw(woodVertical);
    renderWindow->draw(woodVertical2);
}

void Game::drawBackgroundTextureWithWoodBorder(const sf::Texture& texture)
{
    sf::FloatRect layoutRect = getGuiFullLayoutRect();

    m_backgroundTextureShape.setTexture(&texture, true);
    m_backgroundTextureShape.setPosition(sf::Vector2f(layoutRect.left, layoutRect.top));
    m_backgroundTextureShape.setSize(sf::Vector2f(layoutRect.width, layoutRect.height));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(m_backgroundTextureShape);

    drawWoodBorder(m_backgroundTextureShape.getGlobalBounds(), true);
}

sf::FloatRect Game::getClickRect(const sf::Texture& texture, const std::string& name)
{
    sf::FloatRect clickRect;

    tb::ClickRectData::Data* clickRectData = g_ClickRectData.getDataByName(name);

    if (clickRectData == nullptr)
    {
        g_Log.write("ERROR: clickRectData == nullptr with name '{}'\n", name);

        clickRect.left = 0.0f;
        clickRect.top = 0.0f;
        clickRect.width = 0.0f;
        clickRect.height = 0.0f;

        return clickRect;
    }

    sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture.getSize());

    sf::Vector2f backgroundTextureSize = m_backgroundTextureShape.getSize();

    sf::Vector2f backgroundTextureScale;
    backgroundTextureScale.x = backgroundTextureSize.x / textureSize.x;
    backgroundTextureScale.y = backgroundTextureSize.y / textureSize.y;

    sf::Vector2f backgroundTexturePosition = m_backgroundTextureShape.getPosition();

    clickRect.left = backgroundTexturePosition.x + (static_cast<float>(clickRectData->X) * backgroundTextureScale.x);
    clickRect.top  = backgroundTexturePosition.y + (static_cast<float>(clickRectData->Y) * backgroundTextureScale.y);

    clickRect.width  = static_cast<float>(clickRectData->Width)  * backgroundTextureScale.x;
    clickRect.height = static_cast<float>(clickRectData->Height) * backgroundTextureScale.y;

    return clickRect;
}

void Game::drawDebugRect(sf::FloatRect rect)
{
    sf::RectangleShape clickRectShape;
    clickRectShape.setPosition(sf::Vector2f(rect.left, rect.top));
    clickRectShape.setSize(sf::Vector2f(rect.width, rect.height));
    clickRectShape.setFillColor(sf::Color::Transparent);
    clickRectShape.setOutlineColor(sf::Color::Magenta);
    clickRectShape.setOutlineThickness(1.0f);

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(clickRectShape);
}

void Game::drawSfmlWindows()
{
    g_GameWindow.draw();

    if (m_guiProperties.ShowEquipmentWindow == true)
    {
        g_EquipmentWindow.draw();
    }

    if (m_guiProperties.ShowStatusWindow == true)
    {
        g_StatusWindow.draw();
    }

    if (m_guiProperties.ShowMiniMapWindow == true)
    {
        g_MiniMapWindow.draw();
    }

    g_TabButtonsWindow.draw();

    if (m_guiProperties.ShowSkillsWindow == true)
    {
        g_SkillsWindow.draw();
    }

    drawWoodBorderForSfmlWindows();

    if (isDebugModeEnabled() == true)
    {
        drawDebugRectForSfmlWindows();
    }
}

void Game::drawDebugRectForSfmlWindows()
{
    if (tb::Utility::LibImGui::isActive() == true)
    {
        return;
    }

    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        drawDebugRect(g_GameWindow.getRect());
    }

    if (m_guiProperties.ShowEquipmentWindow == true)
    {
        if (g_EquipmentWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_EquipmentWindow.getRect());
        }
    }

    if (m_guiProperties.ShowStatusWindow == true)
    {
        if (g_StatusWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_StatusWindow.getRect());
        }
    }

    if (m_guiProperties.ShowMiniMapWindow == true)
    {
        if (g_MiniMapWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_MiniMapWindow.getRect());
        }
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        drawDebugRect(g_TabButtonsWindow.getRect());
    }

    if (m_guiProperties.ShowSkillsWindow == true)
    {
        if (g_SkillsWindow.isMouseInsideWindow() == true)
        {
            drawDebugRect(g_SkillsWindow.getRect());
        }
    }
}

void Game::drawWoodBorderForSfmlWindows()
{
    drawWoodBorder(g_GameWindow.getRect(), true);

    if (m_guiProperties.ShowEquipmentWindow == true)
    {
        drawWoodBorder(g_EquipmentWindow.getRect(), true);
    }

    if (m_guiProperties.ShowStatusWindow == true)
    {
        drawWoodBorder(g_StatusWindow.getRect(), true);
    }

    if (m_guiProperties.ShowMiniMapWindow == true)
    {
        drawWoodBorder(g_MiniMapWindow.getRect(), true);
    }

    if (m_guiProperties.ShowSkillsWindow == true)
    {
        drawWoodBorder(g_SkillsWindow.getRect(), true);
    }
}

void Game::setSizeInLayoutForSfmlWindows()
{
    g_SkillsWindow.setSizeInLayout();
}

void Game::setPositionInLayoutForSfmlWindows()
{
    // order is important

    g_EquipmentWindow.setPositionInLayout();

    g_StatusWindow.setPositionInLayout();

    g_MiniMapWindow.setPositionInLayout();

    g_TabButtonsWindow.setPositionInLayout();

    g_SkillsWindow.setPositionInLayout();

    g_GameWindow.setPositionInLayout();
}

void Game::setSizeScaleForSfmlWindows(float scale)
{
    m_guiProperties.Scale = scale;

    g_EquipmentWindow.setSizeScale(scale);
    g_StatusWindow.setSizeScale(scale);
    g_MiniMapWindow.setSizeScale(scale);
    g_TabButtonsWindow.setSizeScale(scale);
    g_SkillsWindow.setSizeScale(scale);

    updateLayoutForSfmlWindows();
}

void Game::updateLayoutForSfmlWindows()
{
    setPositionInLayoutForSfmlWindows();
    setSizeInLayoutForSfmlWindows();
}

void Game::drawImGuiWindows()
{
    if (*g_MenuBar.getIsVisible() == true)
    {
        g_MenuBar.draw();
    }

    if (*g_StatusBar.getIsVisible() == true)
    {
        g_StatusBar.draw();
    }

    drawDockSpace();

    if (m_properties.ShowDemoWindow == true)
    {
        ImGui::ShowDemoWindow(&m_properties.ShowDemoWindow);
    }

    if (m_properties.ShowStackToolWindow == true)
    {
        ImGui::ShowStackToolWindow(&m_properties.ShowStackToolWindow);
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

    if (*g_OptionsWindow.getIsVisible() == true)
    {
        g_OptionsWindow.draw();
    }

    if (*g_HotkeysWindow.getIsVisible() == true)
    {
        g_HotkeysWindow.draw();
    }

    if (*g_SetOutfitWindow.getIsVisible() == true)
    {
        g_SetOutfitWindow.draw();
    }

    if (*g_CommentsWindow.getIsVisible() == true)
    {
        g_CommentsWindow.draw();
    }

    if (*g_MessageOfTheDayWindow.getIsVisible() == true)
    {
        g_MessageOfTheDayWindow.draw();
    }

    if (*g_ConnectionWindow.getIsVisible() == true)
    {
        g_ConnectionWindow.draw();
    }

    if (*g_ControlsWindow.getIsVisible() == true)
    {
        g_ControlsWindow.draw();
    }

    if (*g_TipsAndTricksWindow.getIsVisible() == true)
    {
        g_TipsAndTricksWindow.draw();
    }

    if (*g_AboutTibiaWindow.getIsVisible() == true)
    {
        g_AboutTibiaWindow.draw();
    }

    if (*g_AboutTibianerWindow.getIsVisible() == true)
    {
        g_AboutTibianerWindow.draw();
    }

    if (*g_MapGeneratorWindow.getIsVisible() == true)
    {
        g_MapGeneratorWindow.draw();
    }

    if (m_gameState == tb::GameState::InGame)
    {
        if (*g_OverlayWindow.getIsVisible() == true)
        {
            g_OverlayWindow.draw();
        }
    }
}

void Game::doEndGamePopup()
{
    if (m_properties.ShowEndGamePopup == true)
    {
        ImGui::OpenPopup("End Game##EndGamePopup");
    }

    ImVec2 viewportCenter = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(viewportCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("End Game##EndGamePopup", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::TextUnformatted("Are you sure you want to end this game?");

        ImGui::Separator();

        if (ImGui::Button("Yes##EndGamePopupButtonYes", tb::Constants::LibImGui::PopupButtonSize))
        {
            ImGui::CloseCurrentPopup();

            m_properties.ShowEndGamePopup = false;

            endGame();
        }

        ImGui::SameLine();

        if (ImGui::Button("No##EndGamePopupButtonNo", tb::Constants::LibImGui::PopupButtonSize))
        {
            ImGui::CloseCurrentPopup();

            m_properties.ShowEndGamePopup = false;
        }

        ImGui::EndPopup();
    }
}

void Game::doErrorLoadingMapPopup()
{
    if (m_properties.ShowErrorLoadingMapPopup == true)
    {
        ImGui::OpenPopup("Error##ErrorLoadingMapPopup");
    }

    ImVec2 viewportCenter = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(viewportCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Error##ErrorLoadingMapPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::TextUnformatted("Failed to load map file!\nSee log for details.");

        ImGui::Separator();

        if (ImGui::Button("OK##ErrorLoadingMapPopupButtonOK", tb::Constants::LibImGui::PopupButtonSize))
        {
            m_properties.ShowErrorLoadingMapPopup = false;

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Game::doGameStateTesting()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->clear(sf::Color::White);

/*
    sf::Vector2f drawPosition = sf::Vector2f(100.0f, 100.0f);

    sf::Text testText;
    testText.setFont(tb::Fonts::SystemFixed);
    testText.setCharacterSize(tb::Fonts::CharacterSize::SystemFixed);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 0; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            drawPosition.x = 100.0f;
            drawPosition.y += 16.0f;
        }

        std::string character;
        character = (char)i;

        testText.setString(character);

        testText.setPosition(drawPosition);

        renderWindow->draw(testText);

        drawPosition.x += 16.0f;
    }

    sf::FloatRect rect;
    rect.left = 100.0f;
    rect.top = 100.0f + 3.0f;
    rect.width = 256.0f;
    rect.height = 256.0f;

    drawDebugRect(rect);
*/

/*
    sf::Vector2f drawPosition = sf::Vector2f(10.0f, 40.0f);

    sf::Text testText;
    testText.setFont(tb::Fonts::System);
    testText.setCharacterSize(13);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 32; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 32 && i % 16 == 0)
        {
            drawPosition.x += 100.0f;
            drawPosition.y = 40.0f;
        }

        char character = (char)i;

        std::string text = std::format("{}: {}{}", i, character, character);

        testText.setString(text);

        testText.setPosition(drawPosition);

        renderWindow->draw(testText);

        drawPosition.y += 16.0f;
    }
*/

/*
    sf::Font* font = &tb::Fonts::System;

    sf::Vector2f drawPosition = sf::Vector2f(100.0f, 100.0f);

    sf::Text testText;
    testText.setFont(*font);
    testText.setCharacterSize(13);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 0; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            drawPosition.x = 100.0f;
            drawPosition.y += 16.0f;
        }

        sf::Glyph glyph = font->getGlyph(i, 13, false, 0.0f);

        float characterLeft = glyph.bounds.left;
        float characterWidth = glyph.bounds.width;

        std::string characterText = std::format("{}", characterLeft + characterWidth);

        testText.setString(characterText);

        testText.setPosition(drawPosition);

        renderWindow->draw(testText);

        drawPosition.x += 32.0f;
    }
*/

/*
    sf::Vector2f drawPosition = sf::Vector2f(100.0f, 100.0f);

    sf::Text testText;
    testText.setFont(tb::Fonts::System);
    testText.setCharacterSize(13);
    testText.setFillColor(sf::Color::Black);

    for (std::uint32_t i = 0; i < tb::Constants::BitmapFonts::NumGlyphs; i++)
    {
        if (i != 0 && i % 16 == 0)
        {
            drawPosition.x = 100.0f;
            drawPosition.y += 16.0f;
        }

        std::string character;
        character = (char)i;

        std::string text = std::format("x{}x", character);

        testText.setString(text);

        testText.setPosition(drawPosition);

        sf::FloatRect textRect = testText.getLocalBounds();

        float characterWidth = textRect.width - 16.0f;

        text = std::format("{}", characterWidth);

        testText.setString(text);

        renderWindow->draw(testText);

        drawPosition.x += 32.0f;
    }
*/

/*
    tb::BitmapFontText bitmapText;
    bitmapText.setText(&m_systemBitmapFont, "Hello, world!", sf::Color::Black);
    bitmapText.setPosition(sf::Vector2f(100.0f, 100.0f));

    renderWindow->draw(bitmapText);

    sf::Text text;
    text.setString("Hello, world!");
    text.setFont(tb::Fonts::System);
    text.setCharacterSize(tb::Fonts::CharacterSize::System);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(100.0f, 116.0f));

    renderWindow->draw(text);
*/

    tb::BitmapFontText bitmapText;
    bitmapText.setText(&m_systemFixedBitmapFont, "Hello, world! ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqqrstuvwxyz\n1234567890\n!@#$%^&*()-+[]\n", sf::Color::Black);
    bitmapText.setPosition(sf::Vector2f(100.0f, 100.0f));

    renderWindow->draw(bitmapText);
}

void Game::doGameStateEnterGame()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::EnterGame);

    if (isDebugModeEnabled() == true)
    {
        if (tb::Utility::LibImGui::isActive() == false)
        {
            sf::FloatRect enterGameClickRect = getClickRect(tb::Textures::EnterGame, "EnterGame");

            sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

            if (enterGameClickRect.contains(mousePosition) == true)
            {
                drawDebugRect(enterGameClickRect);
            }
        }
    }

    if (*g_EnterGameWindow.getIsVisible() == true)
    {
        g_EnterGameWindow.draw();
    }
}

void Game::doGameStateLoadingMap()
{
    drawBackgroundTextureWithWoodBorder(tb::Textures::Loading);

    m_loadMapThreadStatus = m_loadMapThread.wait_for(std::chrono::milliseconds(1));

    if (m_loadMapThreadStatus == std::future_status::ready)
    {
        bool isMapLoaded = m_loadMapThread.get();

        if (isMapLoaded == true)
        {
            setGameState(tb::GameState::InGame);
        }
        else
        {
            m_properties.ShowErrorLoadingMapPopup = true;

            setGameState(tb::GameState::MapSelect);

            g_MapSelectWindow.setIsVisible(true);
        }
    }
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

    doErrorLoadingMapPopup();
}

void Game::doGameStateInGame()
{
    drawSfmlWindows();

    doEndGamePopup();
}

sf::Vector2i Game::getMousePositionInDesktop()
{
    // get mouse position in operating system desktop
    return sf::Mouse::getPosition();
}

tb::VisibleZ_t Game::getVisibleZOfPlayer()
{
    tb::VisibleZ_t visibleZ;
    visibleZ.Begin = tb::ZAxis::Min;
    visibleZ.End   = tb::ZAxis::Max;

    tb::ZAxis_t playerZ = m_player->getZ();

    // check if the player is underground
    if (playerZ < tb::ZAxis::Default)
    {
        // get all z-axis that are underground
        visibleZ.Begin = tb::ZAxis::Min;
        visibleZ.End   = tb::ZAxis::Default - 1;
    }
    else
    {
        // get all z-axis that are aboveground
        visibleZ.Begin = tb::ZAxis::Default;
        visibleZ.End   = tb::ZAxis::Max;
    }

    return visibleZ;
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

    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    player->setOutfit(optionsData->PlayerOutfitHead, optionsData->PlayerOutfitBody, optionsData->PlayerOutfitLegs, optionsData->PlayerOutfitFeet);

    std::string playerName = optionsData->PlayerName;
    if (playerName.size() == 0)
    {
        playerName = tb::Constants::PlayerNameDefault;
    }

    player->setName(playerName);

    player->setMovementSpeed(0.1f);

    m_player = player;

    tb::Tile::Ptr tile = g_Map.getTileOfThing(m_player);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addCreature(m_player);

    g_Log.write("Tile Index: {}\n", tile->getTileIndex());
    g_Log.write("Tile X: {}\n", tile->getTileX());
    g_Log.write("Tile Y: {}\n", tile->getTileY());
    g_Log.write("Tile Z: {}\n", tile->getZ());
    g_Log.write("Tile Sprite ID: {}\n", tile->getSpriteID());

    sf::Vector2i playerTileCoords = m_player->getTileCoords();

    tb::ZAxis_t playerZ = m_player->getZ();

    g_Log.write("Player Tile Coords: {},{},{}\n", playerTileCoords.x, playerTileCoords.y, playerZ);

    spawnAnimationByIndex(playerTileCoords, playerZ, tb::Animations::BlueOrbSpell);

    return true;
}

bool Game::spawnAnimationByIndex(const sf::Vector2i& tileCoords, tb::ZAxis_t z, std::uint32_t index)
{
    tb::Animation::Ptr animation = std::make_shared<tb::Animation>(tileCoords, z, index);

    tb::Tile::Ptr tile = g_Map.getTile(tileCoords, z);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addAnimation(animation);

    return true;
}

bool Game::spawnAnimationByName(const sf::Vector2i& tileCoords, tb::ZAxis_t z, const std::string& name)
{
    tb::Animation::Ptr animation = std::make_shared<tb::Animation>(tileCoords, z, name);

    tb::Tile::Ptr tile = g_Map.getTile(tileCoords, z);

    if (tile == nullptr)
    {
        g_Log.write("ERROR: tile == nullptr\n");
        return false;
    }

    tile->addAnimation(animation);

    return true;
}

void Game::handleClosedEvent(sf::Event event)
{
    g_RenderWindow.handleClosedEvent(event);
}

void Game::handleResizedEvent(sf::Event event)
{
    g_RenderWindow.handleResizedEvent(event);

    g_SkillsWindow.handleResizedEvent(event);
}

void Game::handleGainedFocusEvent(sf::Event event)
{
    g_RenderWindow.handleGainedFocusEvent(event);
}

void Game::handleLostFocusEvent(sf::Event event)
{
    g_RenderWindow.handleLostFocusEvent(event);
}

void Game::handleMouseWheelMovedEvent(sf::Event event)
{
    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        g_GameWindow.handleMouseWheelMovedEvent(event);
    }

    if (g_MiniMapWindow.isMouseInsideWindow() == true)
    {
        g_MiniMapWindow.handleMouseWheelMovedEvent(event);
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        g_TabButtonsWindow.handleMouseWheelMovedEvent(event);
    }

    if (g_SkillsWindow.isMouseInsideWindow() == true)
    {
        g_SkillsWindow.handleMouseWheelMovedEvent(event);
    }
}

void Game::handleMouseButtonPressedEvent(sf::Event event)
{
    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        g_GameWindow.handleMouseButtonPressedEvent(event);
    }

    if (g_MiniMapWindow.isMouseInsideWindow() == true)
    {
        g_MiniMapWindow.handleMouseButtonPressedEvent(event);
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        g_TabButtonsWindow.handleMouseButtonPressedEvent(event);
    }

    if (g_SkillsWindow.isMouseInsideWindow() == true)
    {
        g_SkillsWindow.handleMouseButtonPressedEvent(event);
    }

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        //
    }
}

void Game::handleMouseButtonReleasedEvent(sf::Event event)
{
    if (g_GameWindow.isMouseInsideWindow() == true)
    {
        g_GameWindow.handleMouseButtonReleasedEvent(event);
    }

    if (g_MiniMapWindow.isMouseInsideWindow() == true)
    {
        g_MiniMapWindow.handleMouseButtonReleasedEvent(event);
    }

    if (g_TabButtonsWindow.isMouseInsideWindow() == true)
    {
        g_TabButtonsWindow.handleMouseButtonReleasedEvent(event);
    }

    if (g_SkillsWindow.isMouseInsideWindow() == true)
    {
        g_SkillsWindow.handleMouseButtonReleasedEvent(event);
    }

    sf::Vector2f mousePosition;
    mousePosition.x = static_cast<float>(event.mouseButton.x);
    mousePosition.y = static_cast<float>(event.mouseButton.y);

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if (m_gameState == tb::GameState::EnterGame)
        {
            sf::FloatRect enterGameClickRect = getClickRect(tb::Textures::EnterGame, "EnterGame");

            if (enterGameClickRect.contains(mousePosition) == true)
            {
                g_EnterGameWindow.setIsVisible(true);
            }
        }
    }
}

void Game::handleKeyPressedEvent(sf::Event event)
{
    m_properties.IsAnyKeyboardKeyPressed = true;

    if (m_gameState == tb::GameState::InGame)
    {
        if (event.key.code == sf::Keyboard::Key::B)
        {
            spawnAnimationByName(m_player->getTileCoords(), m_player->getZ(), "BlueOrbSpell");
        }
    }
}

void Game::handleKeyReleasedEvent(sf::Event event)
{
    m_properties.IsAnyKeyboardKeyPressed = false;
}

void Game::handleKeyboardInput()
{
    if (m_gameState == tb::GameState::InGame)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Down);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Left);
        }
    }

    if (isDebugModeEnabled() == true)
    {
        if (m_gameState == tb::GameState::InGame)
        {
            sf::Time cameraKeyPressedTimeElapsed = m_cameraKeyPressedClock.getElapsedTime();

            if (cameraKeyPressedTimeElapsed >= m_cameraKeyPressedTime)
            {
                // camera reset
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) == true)
                {
                    g_GameWindow.resetViewPositionOffset();

                    m_cameraKeyPressedClock.restart();
                }

                // camera up
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) == true)
                {
                    sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

                    viewPositionOffset.y -= tb::Constants::TileSizeAsFloat;

                    g_GameWindow.setViewPositionOffset(viewPositionOffset);

                    m_cameraKeyPressedClock.restart();
                }

                // camera right
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) == true)
                {
                    sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

                    viewPositionOffset.x += tb::Constants::TileSizeAsFloat;

                    g_GameWindow.setViewPositionOffset(viewPositionOffset);

                    m_cameraKeyPressedClock.restart();
                }

                // camera down
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) == true)
                {
                    sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

                    viewPositionOffset.y += tb::Constants::TileSizeAsFloat;

                    g_GameWindow.setViewPositionOffset(viewPositionOffset);

                    m_cameraKeyPressedClock.restart();
                }

                // camera left
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) == true || sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) == true)
                {
                    sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

                    viewPositionOffset.x -= tb::Constants::TileSizeAsFloat;

                    g_GameWindow.setViewPositionOffset(viewPositionOffset);

                    m_cameraKeyPressedClock.restart();
                }
            }
        }
    }
}

void Game::handleJoystickConnectedEvent(sf::Event event)
{
    m_joystickIndex = event.joystickConnect.joystickId;

    updateJoystickPropertiesForAll();

    g_Log.write("Joystick Connected Index: {}\n", m_joystickIndex);

    tb::Joystick::Properties_t* joystickProperties = m_joystickList[m_joystickIndex].getProperties();

    g_Log.write("--> Name: {}\n", joystickProperties->Name);
    g_Log.write("--> Product ID: {}\n", joystickProperties->ProductID);
    g_Log.write("--> Vendor ID: {}\n", joystickProperties->VendorID);
    g_Log.write("--> Button Count: {}\n", joystickProperties->ButtonCount);
}

void Game::handleJoystickDisconnectedEvent(sf::Event event)
{
    unsigned int joystickIndex = event.joystickConnect.joystickId;

    updateJoystickPropertiesForAll();

    g_Log.write("Joystick Disconnected Index: {}\n", joystickIndex);

    tb::Joystick::Properties_t* joystickProperties = m_joystickList[joystickIndex].getProperties();

    g_Log.write("--> Name: {}\n", joystickProperties->Name);
    g_Log.write("--> Product ID: {}\n", joystickProperties->ProductID);
    g_Log.write("--> Vendor ID: {}\n", joystickProperties->VendorID);
    g_Log.write("--> Button Count: {}\n", joystickProperties->ButtonCount);
}

void Game::handleJoystickMovedEvent(sf::Event event)
{
    g_Log.write("Joystick Moved Axis and Position: {} = {}\n", magic_enum::enum_name(event.joystickMove.axis), event.joystickMove.position);
}

void Game::handleJoystickButtonPressedEvent(sf::Event event)
{
    m_properties.IsAnyJoystickButtonPressed = true;
}

void Game::handleJoystickButtonReleasedEvent(sf::Event event)
{
    m_properties.IsAnyJoystickButtonPressed = false;

    g_Log.write("Joystick Button Released: {}\n", event.joystickButton.button);
}

void Game::handleJoystickInput()
{
    tb::Joystick* joystick = &m_joystickList[m_joystickIndex];

    if (joystick == nullptr)
    {
        return;
    }

    if (joystick->isConnected() == false)
    {
        return;
    }

    tb::Joystick::State_t* joystickState = joystick->getState();

    if (m_gameState == tb::GameState::InGame)
    {
        if (joystickState->AxisPOVY >= 50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Up);
        }

        if (joystickState->AxisPOVX >= 50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Right);
        }

        if (joystickState->AxisPOVY <= -50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Down);
        }

        if (joystickState->AxisPOVX <= -50.0f)
        {
            handleCreatureMovement(m_player, tb::MovementDirection::Left);
        }
    }
}

void Game::processEvents()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    tb::RenderWindow::Properties_t* renderWindowProperties = g_RenderWindow.getProperties();

    bool renderWindowIsFocused = renderWindowProperties->IsFocused;

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
        else if (event.type == sf::Event::LostFocus)
        {
            handleLostFocusEvent(event);
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            handleGainedFocusEvent(event);
        }

        if (tb::Utility::LibImGui::isActive() == false)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                handleMouseButtonPressedEvent(event);
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                handleMouseButtonReleasedEvent(event);
            }
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                handleMouseWheelMovedEvent(event);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                handleKeyPressedEvent(event);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                handleKeyReleasedEvent(event);
            }
            else if (event.type == sf::Event::JoystickConnected)
            {
                handleJoystickConnectedEvent(event);
            }
            else if (event.type == sf::Event::JoystickDisconnected)
            {
                handleJoystickDisconnectedEvent(event);
            }
            else if (event.type == sf::Event::JoystickMoved)
            {
                handleJoystickMovedEvent(event);
            }
            else if (event.type == sf::Event::JoystickButtonPressed)
            {
                handleJoystickButtonPressedEvent(event);
            }
            else if (event.type == sf::Event::JoystickButtonReleased)
            {
                handleJoystickButtonReleasedEvent(event);
            }
        }
    }

    if (renderWindowIsFocused == true && tb::Utility::LibImGui::isActive() == false)
    {
        handleKeyboardInput();

        updateJoystickStateForAll();
        handleJoystickInput();
    }
}

void Game::setMouseCursor(const sf::Cursor& cursor)
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->setMouseCursor(cursor);
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

            renderWindow->setMouseCursor(tb::Cursors::Arrow);
        }
        imguiHasCursorPrev = imguiHasCursor;
    }
}

unsigned int Game::getJoystickIndex()
{
    return m_joystickIndex;
}

void Game::setJoystickIndex(unsigned int index)
{
    m_joystickIndex = index;
}

tb::JoystickList* Game::getJoystickList()
{
    return &m_joystickList;
}

void Game::updateJoystickIndexForAll()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; i++)
    {
        m_joystickList[i].setIndex(i);
    }
}

void Game::updateJoystickPropertiesForAll()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; i++)
    {
        if (sf::Joystick::isConnected(i) == true)
        {
            m_joystickList[i].updateProperties();
        }
    }
}

void Game::updateJoystickStateForAll()
{
    for (unsigned int i = 0; i < sf::Joystick::Count; i++)
    {
        m_joystickList[i].updateState();
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

    std::uint32_t imageWidth = image.getSize().x;
    std::uint32_t imageHeight = image.getSize().y;

    tb::SpriteIDList spriteIDList;

    for (std::uint32_t i = 0; i < imageWidth; i++)
    {
        for (std::uint32_t j = 0; j < imageHeight; j++)
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

    std::size_t spriteIDListSize = spriteIDList.size();

    for (std::size_t i = 0; i < spriteIDListSize; i++)
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    tb::Creature::Outfit_t* playerOutfit = m_player->getOutfit();

    std::string playerText = std::format
    (
"\
Player X,Y,Z: {},{},{}\n\
Player Outfit: {},{},{},{}\n\
",
        m_player->getTileX(), m_player->getTileY(), m_player->getZ(),
        playerOutfit->Head, playerOutfit->Body, playerOutfit->Legs, playerOutfit->Feet
    );

    g_OverlayWindow.addTextToList(playerText);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2i mousePositionInDesktop = getMousePositionInDesktop();
    sf::Vector2i mousePositionInRenderWindow = g_RenderWindow.getMousePosition2i();
    sf::Vector2f mousePixelPositionInGameWindow = g_GameWindow.getMousePixelPosition();
    sf::Vector2f mousePixelCoordsInGameWindow = g_GameWindow.getMousePixelCoords();
    sf::Vector2i mouseTileCoordsInGameWindow = g_GameWindow.getMouseTileCoords();

    std::string mouseText = std::format
    (
"\
Desktop Mouse Position: {},{}\n\
Render Window Mouse Position: {},{}\n\
Game Window Mouse Pixel Position: {},{}\n\
Game Window Mouse Pixel Coords: {},{}\n\
Game Window Mouse Tile Coords: {},{}\n\
",
        mousePositionInDesktop.x, mousePositionInDesktop.y,
        mousePositionInRenderWindow.x, mousePositionInRenderWindow.y,
        mousePixelPositionInGameWindow.x, mousePixelPositionInGameWindow.y,
        mousePixelCoordsInGameWindow.x, mousePixelCoordsInGameWindow.y,
        mouseTileCoordsInGameWindow.x, mouseTileCoordsInGameWindow.y
    );

    g_OverlayWindow.addTextToList(mouseText);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    tb::Joystick* joystick = &m_joystickList[m_joystickIndex];

    if (joystick->isConnected() == false)
    {
        std::string joystickDisconnectedText = std::format("Joystick Index {} is disconnected!\n", m_joystickIndex);

        g_OverlayWindow.addTextToList(joystickDisconnectedText);
    }
    else
    {
        tb::Joystick::State_t* joystickState = joystick->getState();

        std::string joystickButtonText;
        joystickButtonText.reserve(1024);

        for (unsigned int i = 0; i < sf::Joystick::ButtonCount; i++)
        {
            bool buttonState = joystickState->Button[i];

            if (buttonState == true)
            {
                joystickButtonText.append(std::format("Joystick Button {}: Pressed\n", i));
            }
        }

        if (joystickButtonText.empty() == false)
        {
            g_OverlayWindow.addTextToList(joystickButtonText);
        }

        std::string joystickAxisText = std::format
        (
"\
Joystick Axis X: {}\n\
Joystick Axis Y: {}\n\
Joystick Axis Z: {}\n\
Joystick Axis R: {}\n\
Joystick Axis U: {}\n\
Joystick Axis V: {}\n\
Joystick Axis POVX: {}\n\
Joystick Axis POVY: {}\n\
",
            joystickState->AxisX,
            joystickState->AxisY,
            joystickState->AxisZ,
            joystickState->AxisR,
            joystickState->AxisU,
            joystickState->AxisV,
            joystickState->AxisPOVX,
            joystickState->AxisPOVY
        );

        g_OverlayWindow.addTextToList(joystickAxisText);
    }
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
    g_Log.deleteFileContents();
    g_Log.open();
    g_Log.write("{} (Build: {} {})\n", tb::Constants::GameTitle, __DATE__, __TIME__);

    g_Log.write("Loading config\n");
    if (loadConfig() == false)
    {
        g_Log.write("ERROR: Failed to load config\n");
        exit();
        return;
    }

    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    tb::Log::Properties_t* logProperties = g_Log.getProperties();
    logProperties->IsEnabled = optionsData->LogIsEnabled;
    logProperties->PrintToConsole = optionsData->LogPrintToConsole;
    logProperties->WriteToFile = optionsData->LogWriteToFile;

    g_Log.write("Creating render window\n");
    if (g_RenderWindow.create() == false)
    {
        g_Log.write("ERROR: Failed to create render window\n");
        exit();
        return;
    }

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();
    if (renderWindow == nullptr)
    {
        g_Log.write("ERROR: renderWindow == nullptr\n");
        exit();
        return;
    }

    drawLoadingText();

    g_Log.write("Initializing ImGui\n");
    initImGui();

    g_Log.write("Loading data\n");
    if (loadData() == false)
    {
        g_Log.write("ERROR: Failed to load data\n");
        exit();
        return;
    }

    g_Log.write("Loading globals from data\n");
    if (loadGlobalsFromData() == false)
    {
        g_Log.write("ERROR: Failed to load globals from data\n");
        exit();
        return;
    }

    updateLayoutForSfmlWindows();

    g_Log.write("Updating joystick\n");

    sf::Joystick::update();
    updateJoystickIndexForAll();
    updateJoystickPropertiesForAll();

    g_Log.write("Start rendering...\n");

    m_framesPerSecondPreviousTime = m_framesPerSecondClock.getElapsedTime();

    while (renderWindow->isOpen() == true)
    {
        processEvents();

        // fixed in imgui-sfml 2.6
        //fixMouseCursorForWindowResize(renderWindow);

        ImGui::SFML::Update(*renderWindow, m_deltaClock.restart());

        renderWindow->clear(sf::Color::Black);

        drawWoodBackground();

        setPositionInLayoutForSfmlWindows();

        if (m_gameState == tb::GameState::Testing)
        {
            doGameStateTesting();
        }
        else if (m_gameState == tb::GameState::EnterGame)
        {
            doGameStateEnterGame();
        }
        else if (m_gameState == tb::GameState::MapSelect)
        {
            doGameStateMapSelect();
        }
        else if (m_gameState == tb::GameState::LoadingMap)
        {
            doGameStateLoadingMap();
        }
        else if (m_gameState == tb::GameState::InGame)
        {
            doGameStateInGame();

            doOverlayText();
        }

        drawImGuiWindows();

        drawFramesPerSecond();

        ImGui::SFML::Render(*renderWindow);

        renderWindow->display();
    }

    exit();
}

void Game::endGame()
{
    setGameState(tb::GameState::EnterGame);
}

bool Game::isDeveloperModeEnabled()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    return optionsData->GameDeveloperMode;
}

void Game::toggleDeveloperMode()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    tb::Utility::toggleBool(optionsData->GameDeveloperMode);

    g_OptionsData.save();
}

bool Game::isDebugModeEnabled()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    return optionsData->GameDebugMode;
}

void Game::toggleDebugMode()
{
    tb::OptionsData::Data* optionsData = g_OptionsData.getData();

    tb::Utility::toggleBool(optionsData->GameDebugMode);

    g_OptionsData.save();
}

void Game::toggleDemoWindow()
{
    tb::Utility::toggleBool(m_properties.ShowDemoWindow);
}

void Game::toggleStackToolWindow()
{
    tb::Utility::toggleBool(m_properties.ShowStackToolWindow);
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

sf::Vector2i Game::getVectorByMovementDirection(tb::MovementDirection movementDirection)
{
    sf::Vector2i vector(0, 0);

    switch (movementDirection)
    {
        case tb::MovementDirection::Up:
            vector.y = -1;
            break;

        case tb::MovementDirection::Right:
            vector.x = 1;
            break;

        case tb::MovementDirection::Down:
            vector.y = 1;
            break;

        case tb::MovementDirection::Left:
            vector.x = -1;
            break;

        case tb::MovementDirection::UpLeft:
            vector.x = -1;
            vector.y = -1;
            break;

        case tb::MovementDirection::UpRight:
            vector.x++;
            vector.y = -1;
            break;

        case tb::MovementDirection::DownLeft:
            vector.x = -1;
            vector.y = 1;
            break;

        case tb::MovementDirection::DownRight:
            vector.x = 1;
            vector.y = 1;
            break;
    }

    return vector;
}

tb::MovementDirection Game::getMovementDirectionByVector(sf::Vector2i vector)
{
    tb::MovementDirection movementDirection = tb::MovementDirection::Null;

    if (vector.x == 0 && vector.y < 0)
    {
        movementDirection = tb::MovementDirection::Up;
    }
    else if (vector.x > 0 && vector.y == 0)
    {
        movementDirection = tb::MovementDirection::Right;
    }
    else if (vector.x == 0 && vector.y > 0)
    {
        movementDirection = tb::MovementDirection::Down;
    }
    else if (vector.x < 0 && vector.y == 0)
    {
        movementDirection = tb::MovementDirection::Left;
    }
    else if (vector.x < 0 && vector.y < 0)
    {
        movementDirection = tb::MovementDirection::UpLeft;
    }
    else if (vector.x > 0 && vector.y < 0)
    {
        movementDirection = tb::MovementDirection::UpRight;
    }
    else if (vector.x < 0 && vector.y > 0)
    {
        movementDirection = tb::MovementDirection::DownLeft;
    }
    else if (vector.x > 0 && vector.y > 0)
    {
        movementDirection = tb::MovementDirection::DownRight;
    }

    return movementDirection;
}

tb::Tile::Ptr Game::getTileByThingMovementDirection(tb::Thing::Ptr thing, tb::MovementDirection movementDirection)
{
    sf::Vector2i vectorByMovementDirection = getVectorByMovementDirection(movementDirection);

    tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtZ(thing->getZ());

    if (tileMap == nullptr)
    {
        return nullptr;
    }

    tb::Tile::List* tileList = tileMap->getTileList();

    if (tileList == nullptr)
    {
        return nullptr;
    }

    sf::Vector2i tileCoords = sf::Vector2i(thing->getTileX() + vectorByMovementDirection.x, thing->getTileY() + vectorByMovementDirection.y);

    if (g_Map.isTileCoordsOutOfBounds(tileCoords) == true)
    {
        return nullptr;
    }

    std::uint32_t tileIndex = g_Map.getTileIndexByTileCoords(tileCoords);

    if (g_Map.isTileIndexOutOfBounds(tileIndex) == true)
    {
        return nullptr;
    }

    return tileList->at(tileIndex);
}

bool Game::findCeilingAbovePlayerAtZ(tb::ZAxis_t z)
{
    tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtZ(z);

    if (tileMap == nullptr)
    {
        return false;
    }

    tb::Tile::List* tileList = tileMap->getTileList();

    if (tileList == nullptr)
    {
        return false;
    }

    if (tileList->size() == 0)
    {
        return false;
    }

    std::int32_t playerX = m_player->getTileX();
    std::int32_t playerY = m_player->getTileY();

    tb::ZAxis_t playerZ = m_player->getZ();

    std::vector<std::uint32_t> tileIndexList;
    tileIndexList.reserve(16);

    for (int i = -2; i < 2; i++)
    {
        sf::Vector2i tileCoords1 = sf::Vector2i(playerX - 2, playerY + i);
        sf::Vector2i tileCoords2 = sf::Vector2i(playerX - 1, playerY + i);
        sf::Vector2i tileCoords3 = sf::Vector2i(playerX,     playerY + i);
        sf::Vector2i tileCoords4 = sf::Vector2i(playerX + 1, playerY + i);

        if (g_Map.isTileCoordsOutOfBounds(tileCoords1) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords1));
        }

        if (g_Map.isTileCoordsOutOfBounds(tileCoords2) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords2));
        }

        if (g_Map.isTileCoordsOutOfBounds(tileCoords3) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords3));
        }

        if (g_Map.isTileCoordsOutOfBounds(tileCoords4) == false)
        {
            tileIndexList.push_back(g_Map.getTileIndexByTileCoords(tileCoords4));
        }
    }

    for (std::uint32_t tileIndex : tileIndexList)
    {
        if (g_Map.isTileIndexOutOfBounds(tileIndex) == true)
        {
            continue;
        }

        tb::Tile::Ptr tile = tileList->at(tileIndex);

        if (tile->getSpriteID() == tb::Constants::SpriteIDNull)
        {
            continue;
        }

        if (tile->getZ() > playerZ)
        {
            return true;
        }
    }

    return false;
}

void Game::handleCreatureMovement(tb::Creature::Ptr creature, tb::MovementDirection movementDirection)
{
    if (movementDirection == tb::MovementDirection::Null)
    {
        return;
    }

    tb::Creature::Properties_t* creatureProperties = creature->getProperties();

    if (creatureProperties->IsDead == true || creatureProperties->IsSleeping == true)
    {
        return;
    }

    sf::Time timeMovement = creature->getMovementClock()->getElapsedTime();

    if (timeMovement.asSeconds() < creature->getMovementSpeed())
    {
        return;
    }

    creature->setDirectionByMovementDirection(movementDirection);

    tb::Tile::Ptr toTile = getTileByThingMovementDirection(creature, movementDirection);

    if (toTile == nullptr)
    {
        return;
    }

    doMoveThingFromTileToTile(creature, toTile);

    creature->getMovementClock()->restart();

    creature->update();
}

bool Game::doMoveThingFromTileToTile(tb::Thing::Ptr thing, tb::Tile::Ptr toTile)
{
    tb::Tile::Ptr fromTile = g_Map.getTileOfThing(thing);

    if (fromTile == nullptr || toTile == nullptr)
    {
        return false;
    }

    tb::SpriteID_t toTileSpriteID = toTile->getSpriteID();

    if (toTileSpriteID == tb::Constants::SpriteIDNull)
    {
        return false;
    }

    tb::ThingType thingType = thing->getThingType();

    tb::ZAxis_t fromTileZ = fromTile->getZ();
    tb::ZAxis_t toTileZ = toTile->getZ();

    tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

    tb::Object::List* toTileObjectList = toTile->getObjectList();

    for (auto& toTileObject : *toTileObjectList)
    {
        tb::SpriteID_t toTileObjectSpriteID = toTileObject->getSpriteID();

        tb::SpriteData::Data* toTileObjectSpriteData = &spriteDataList->at(toTileObjectSpriteID);

        tb::SpriteFlags* toTileObjectSpriteFlags = &toTileObjectSpriteData->SpriteFlags;

        // TODO: account for throwing items in water or dustbin, etc

        if (toTileObjectSpriteFlags->hasFlag(tb::SpriteFlag::Solid) == true)
        {
            return false;
        }
    }

    if (thingType == tb::ThingType::Creature)
    {
        tb::Creature::Ptr creature = std::static_pointer_cast<tb::Creature>(thing);

        tb::Creature::List* fromTileCreatureList = fromTile->getCreatureList();

        if (fromTileCreatureList->size() == 0)
        {
            return false;
        }

        auto fromTileCreatureIt = std::find(fromTileCreatureList->begin(), fromTileCreatureList->end(), creature);

        if (fromTileCreatureIt == fromTileCreatureList->end())
        {
            return false;
        }

        toTile->addCreature(creature);

        fromTileCreatureList->erase(fromTileCreatureIt);

        thing->setTileCoords(toTile->getTileCoords());
        thing->setZ(toTileZ);
    }

    // Object

    return true;
}

tb::BitmapFont* Game::getClassicBitmapFont()
{
    return &m_classicBitmapFont;
}

tb::BitmapFont* Game::getTinyBitmapFont()
{
    return &m_tinyBitmapFont;
}

tb::BitmapFont* Game::getModernBitmapFont()
{
    return &m_modernBitmapFont;
}

tb::BitmapFont* Game::getSystemBitmapFont()
{
    return &m_systemBitmapFont;
}

}
