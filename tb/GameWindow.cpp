#include "tb/GameWindow.h"

namespace tb
{

GameWindow::GameWindow() :
    m_windowLayerSprite(tb::Textures::Null),
    m_lightLayerSprite(tb::Textures::Null),
    m_tileHighlightSprite(tb::Textures::Sprites)
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    sf::Vector2u windowRenderTextureSize2u = static_cast<sf::Vector2u>(m_windowRenderTextureSize);

    if (m_windowLayerRenderTexture.resize(windowRenderTextureSize2u) == false)
    {
        g_Log.write("ERROR: Failed to resize RenderTexture\n");
    }

    if (m_lightLayerRenderTexture.resize(windowRenderTextureSize2u) == false)
    {
        g_Log.write("ERROR: Failed to resize RenderTexture\n");
    }

    // this makes the lighting look like old tibia
    m_lightBlendMode.colorEquation = sf::BlendMode::Equation::ReverseSubtract;
    m_lightBlendMode.alphaEquation = sf::BlendMode::Equation::Add;
    m_lightBlendMode.colorSrcFactor = sf::BlendMode::Factor::OneMinusSrcColor;
    m_lightBlendMode.colorDstFactor = sf::BlendMode::Factor::SrcColor;
    m_lightBlendMode.alphaSrcFactor = sf::BlendMode::Factor::DstAlpha;
    m_lightBlendMode.alphaDstFactor = sf::BlendMode::Factor::DstAlpha;
}

GameWindow::~GameWindow()
{
    //
}

GameWindow::Properties_t* GameWindow::getProperties()
{
    return &m_properties;
}

void GameWindow::handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled)
{
    // scrolled up
    if (eventMouseWheelScrolled->delta > 0.0f)
    {
        // zoom in
        zoomIn();
    }
    // scrolled down
    else if (eventMouseWheelScrolled->delta < 0.0f)
    {
        // zoom out
        zoomOut();
    }
}

void GameWindow::handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed)
{
    //
}

void GameWindow::handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased)
{
    //
}

sf::FloatRect GameWindow::getLayoutRect()
{
/*
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    float menuBarHeight = g_MenuBar.getHeight();
    float statusBarHeight = g_StatusBar.getHeight();

    sf::FloatRect miniMapWindowRect = g_MiniMapWindow.getRect();

    float miniMapWindowRightPadding = tb::Constants::PaddingRenderWindow;

    float leftPadding = tb::Constants::PaddingRenderWindow;
    float topPadding = tb::Constants::PaddingRenderWindow;
    float rightPadding = ((tb::Constants::PaddingWoodBorder + tb::Constants::PaddingBlackRectangle) * 2.0f) + 4.0f;
    float bottomPadding = tb::Constants::PaddingRenderWindow; // TODO

    sf::FloatRect layoutRect;
    layoutRect.left = leftPadding;
    layoutRect.top = menuBarHeight + topPadding;
    layoutRect.width = renderWindowSize.x - miniMapWindowRect.width - miniMapWindowRightPadding - (leftPadding + rightPadding);
    layoutRect.height = renderWindowSize.y - menuBarHeight - topPadding - statusBarHeight - bottomPadding; // TODO
*/

    sf::FloatRect guiLeftLayoutRect = g_Game.getGuiLeftLayoutRect();

    return guiLeftLayoutRect;
}

void GameWindow::setPositionInLayout()
{
    sf::FloatRect windowRect = getRect();

    sf::FloatRect layoutRect = getLayoutRect();

    sf::Vector2f windowPosition;
    windowPosition.x = layoutRect.position.x + ((layoutRect.size.x - windowRect.size.x) / 2.0f);
    windowPosition.y = layoutRect.position.y + ((layoutRect.size.y - windowRect.size.y) / 2.0f);

    setPosition(windowPosition);
}

void GameWindow::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    if (isDebugModeEnabled == false)
    {
        resetViewPositionOffset();
    }

    tb::Creature::Ptr player = g_Game.getPlayer();

    sf::Vector2f viewPosition =
    (
        sf::Vector2f
        (
            player->getPixelX() + tb::Constants::TileSizeHalfAsFloat,
            player->getPixelY() + tb::Constants::TileSizeHalfAsFloat
        )
    );

    sf::Vector2 viewPositionOffset = getViewPositionOffset();

    viewPosition.x += viewPositionOffset.x;
    viewPosition.y += viewPositionOffset.y;

    sf::View* view = getView();

    view->setCenter(viewPosition);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    if (isDebugModeEnabled == true)
    {
        windowRenderTexture->clear(sf::Color::Magenta);

        sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();
        sf::FloatRect layoutRect = getLayoutRect();
        sf::RectangleShape rectangleShape;
        rectangleShape.setPosition(layoutRect.position);
        rectangleShape.setSize(layoutRect.size);
        rectangleShape.setFillColor(sf::Color::Transparent);
        rectangleShape.setOutlineColor(sf::Color::Cyan);
        rectangleShape.setOutlineThickness(1.0f);
        renderWindow->draw(rectangleShape);
    }
    else
    {
        windowRenderTexture->clear(sf::Color::Black);
    }

    tb::ZAxis_t playerZ = player->getZ();

    tb::VisibleZ_t playerVisibleZ = g_Game.getVisibleZOfPlayer();

    sf::IntRect tileRect = getTileRect();

    for (tb::ZAxis_t z = playerVisibleZ.Begin; z < playerVisibleZ.End; z++)
    {
        // check for ceilings and rooftops above the player
        if (z < tb::Constants::NumZAxis && z > playerZ)
        {
            if (g_Game.findCeilingAbovePlayerAtZ(z) == true)
            {
                break;
            }
        }

        tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtZ(z);

        if (tileMap == nullptr)
        {
            continue;
        }

        bool tileMapIsVisible = tileMap->isVisibleWithinTileRect(tileRect);

        if (tileMapIsVisible == true)
        {
            drawMapLayerAtZ(z);
        }
    }

    windowRenderTexture->display();

    drawToRenderWindow();
}

void GameWindow::drawMapLayerAtZ(tb::ZAxis_t z)
{
    sf::IntRect tileRect = getTileRect();

    sf::IntRect tileRectIncreased = tileRect;

    float zoomScale = getZoomScale();

    if (isZoomed() == true)
    {
        std::uint32_t tileScale = static_cast<std::uint32_t>(zoomScale);

        std::uint32_t tileScaleX = m_numTilesFromCenterX * tileScale;
        std::uint32_t tileScaleY = m_numTilesFromCenterY * tileScale;

        tileRect.position.x    -= tileScaleX;
        tileRect.position.y    -= tileScaleY;
        tileRect.size.x        += tileScaleX * 2;
        tileRect.size.y        += tileScaleY * 2;

        tileRectIncreased = tileRect;
    }
    else
    {
        // this increases the number of tiles to prevent pop in
        tileRectIncreased.position.x    -= m_numTilesX;
        tileRectIncreased.position.y    -= m_numTilesY;
        tileRectIncreased.size.x        += m_numTilesX * 2;
        tileRectIncreased.size.y        += m_numTilesY * 2;
    }

    sf::View* view = getView();

    sf::Vector2f spritePosition = view->getCenter();

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtZ(z);

    if (tileMapTiles == nullptr)
    {
        return;
    }

    tb::ZAxis_t playerZ = g_Game.getPlayer()->getZ();

    // only animate water for the default z-axis and while the player is aboveground
    if (playerZ >= tb::ZAxis::Default && z == tb::ZAxis::Default)
    {
        sf::Time animatedWaterTimeElapsed = m_animatedWaterClock.getElapsedTime();
        if (animatedWaterTimeElapsed >= m_animatedWaterTime)
        {
            if (tileMapTiles->doAnimatedWater(tileRectIncreased) == false)
            {
                g_Log.write("ERROR: Failed to animate water at z: {}\n", z);
            }

            m_animatedWaterClock.restart();
        }
    }

    sf::Time animatedObjectsTimeElapsed = m_animatedObjectsClock.getElapsedTime();
    if (animatedObjectsTimeElapsed >= m_animatedObjectsTime)
    {
        if (tileMapTiles->doAnimatedObjects(tileRectIncreased) == false)
        {
            g_Log.write("ERROR: Failed to animate objects at z: {}\n", z);
        }

        m_animatedObjectsClock.restart();
    }

    m_windowLayerRenderTexture.setView(*view);
    m_windowLayerRenderTexture.clear(sf::Color::Transparent);

    tileMapTiles->drawTiles(tileRect, m_windowLayerRenderTexture);

    tb::TileMap::Ptr tileMapTileEdges = g_Map.getTileMapOfTileEdgesAtZ(z);

    if (tileMapTileEdges != nullptr)
    {
        tileMapTileEdges->drawTiles(tileRect, m_windowLayerRenderTexture);
    }

    tileMapTiles->drawThings(tileRect, m_windowLayerRenderTexture);

    m_lightLayerRenderTexture.setView(*view);
    m_lightLayerRenderTexture.clear(sf::Color(m_lightBrightness, m_lightBrightness, m_lightBrightness));

    tileMapTiles->drawLights(tileRectIncreased, m_lightLayerRenderTexture, m_lightBrightness);

    m_lightLayerRenderTexture.display();

    sf::FloatRect lightLayerSpriteLocalBounds = m_lightLayerSprite.getLocalBounds();

    m_lightLayerSprite.setTexture(m_lightLayerRenderTexture.getTexture(), true);
    m_lightLayerSprite.setPosition(spritePosition);
    m_lightLayerSprite.setOrigin
    (
        sf::Vector2f
        (
            lightLayerSpriteLocalBounds.size.x / 2.0f,
            lightLayerSpriteLocalBounds.size.y / 2.0f
        )
    );
    m_lightLayerSprite.setScale(sf::Vector2f(zoomScale, zoomScale));

    m_windowLayerRenderTexture.draw(m_lightLayerSprite, m_lightBlendMode);

    if (m_properties.ShowTileHighlight == true)
    {
        if (tb::Utility::LibImGui::isActive() == false)
        {
            drawTileHighlight();
        }
    }

    m_windowLayerRenderTexture.display();

    sf::Texture windowLayerTexture = m_windowLayerRenderTexture.getTexture();

    sf::FloatRect windowLayerSpriteLocalBounds = m_windowLayerSprite.getLocalBounds();

    m_windowLayerSprite.setTexture(windowLayerTexture, true);
    m_windowLayerSprite.setPosition(spritePosition);
    m_windowLayerSprite.setOrigin
    (
        sf::Vector2f
        (
            windowLayerSpriteLocalBounds.size.x / 2.0f,
            windowLayerSpriteLocalBounds.size.y / 2.0f
        )
    );
    m_windowLayerSprite.setScale(sf::Vector2f(zoomScale, zoomScale));

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->draw(m_windowLayerSprite);
}

void GameWindow::drawTileHighlight()
{
    sf::Vector2f mousePixelCoords = getMousePixelCoords();

    if (isZoomed() == false)
    {
        m_tileHighlightSprite.setID(tb::Sprites::TileHighlight);
        m_tileHighlightSprite.setPosition(mousePixelCoords);

        m_windowLayerRenderTexture.draw(m_tileHighlightSprite);
    }
    else
    {
        sf::RectangleShape rectangleShape;
        rectangleShape.setSize(sf::Vector2f(tb::Constants::TileSizeAsFloat, tb::Constants::TileSizeAsFloat));
        rectangleShape.setPosition(mousePixelCoords);
        rectangleShape.setFillColor(sf::Color::Cyan);

        m_windowLayerRenderTexture.draw(rectangleShape);
    }
}

sf::IntRect GameWindow::getTileRect()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    std::int32_t tileX = player->getTileX();
    std::int32_t tileY = player->getTileY();

    sf::Vector2i viewPositionOffset = static_cast<sf::Vector2i>(getViewPositionOffset());

    // convert from pixel coords to tile coords
    viewPositionOffset.x /= tb::Constants::TileSize;
    viewPositionOffset.y /= tb::Constants::TileSize;

    tileX += viewPositionOffset.x;
    tileY += viewPositionOffset.y;

    tileX -= (m_numTilesFromCenterX + m_numTilesToDrawOffscreen);
    tileY -= (m_numTilesFromCenterY + m_numTilesToDrawOffscreen);

    std::int32_t tileWidth  = m_numTilesX + (m_numTilesToDrawOffscreen * 2);
    std::int32_t tileHeight = m_numTilesY + (m_numTilesToDrawOffscreen * 2);

    return sf::IntRect(sf::Vector2i(tileX, tileY), sf::Vector2i(tileWidth, tileHeight));
}

void GameWindow::setLightBrightness(tb::LightBrightness_t lightBrightness)
{
    m_lightBrightness = lightBrightness;
}

tb::LightBrightness_t GameWindow::getLightBrightness()
{
    return m_lightBrightness;
}

std::uint32_t GameWindow::getNumTilesX()
{
    return m_numTilesX;
}

std::uint32_t GameWindow::getNumTilesY()
{
    return m_numTilesY;
}

std::uint32_t GameWindow::getNumTilesFromCenterX()
{
    return m_numTilesFromCenterX;
}

std::uint32_t GameWindow::getNumTilesFromCenterY()
{
    return m_numTilesFromCenterY;
}

std::uint32_t GameWindow::getNumTilesToDrawOffscreen()
{
    return m_numTilesToDrawOffscreen;
}

}
