#include "tb/GameWindow.h"

namespace tb
{

GameWindow::GameWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    m_windowLayerRenderTexture.create(m_windowRenderTextureSize.x, m_windowRenderTextureSize.y);
    m_lightLayerRenderTexture.create(m_windowRenderTextureSize.x, m_windowRenderTextureSize.y);

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

void GameWindow::handleMouseWheelMovedEvent(sf::Event event)
{
    // scroll up
    if (event.mouseWheel.delta > 0)
    {
        // zoom in
        zoomIn();
    }
    // scroll down
    else if (event.mouseWheel.delta < 0)
    {
        // zoom out
        zoomOut();
    }
}

void GameWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void GameWindow::handleMouseButtonReleasedEvent(sf::Event event)
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
    windowPosition.x = layoutRect.left + ((layoutRect.width  - windowRect.width)  / 2.0f);
    windowPosition.y = layoutRect.top  + ((layoutRect.height - windowRect.height) / 2.0f);

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
            player->getPixelX() + tb::Constants::TileSizeHalfFloat,
            player->getPixelY() + tb::Constants::TileSizeHalfFloat
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
        sf::RectangleShape rs;
        rs.setPosition(sf::Vector2f(layoutRect.left, layoutRect.top));
        rs.setSize(sf::Vector2f(layoutRect.width, layoutRect.height));
        rs.setFillColor(sf::Color::Transparent);
        rs.setOutlineColor(sf::Color::Cyan);
        rs.setOutlineThickness(1.0f);
        renderWindow->draw(rs);
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
        int tileScale = static_cast<int>(zoomScale);

        int tileScaleX = m_numTilesFromCenterX * tileScale;
        int tileScaleY = m_numTilesFromCenterY * tileScale;

        tileRect.left   -= tileScaleX;
        tileRect.top    -= tileScaleY;
        tileRect.width  += tileScaleX * 2;
        tileRect.height += tileScaleY * 2;

        tileRectIncreased = tileRect;
    }
    else
    {
        // this increases the number of tiles to prevent pop in
        tileRectIncreased.left   -= m_numTilesX;
        tileRectIncreased.top    -= m_numTilesY;
        tileRectIncreased.width  += m_numTilesX * 2;
        tileRectIncreased.height += m_numTilesY * 2;
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

    m_lightLayerSprite.setTexture(m_lightLayerRenderTexture.getTexture());
    m_lightLayerSprite.setPosition(spritePosition);
    m_lightLayerSprite.setOrigin
    (
        lightLayerSpriteLocalBounds.width  / 2,
        lightLayerSpriteLocalBounds.height / 2
    );
    m_lightLayerSprite.setScale(sf::Vector2f(zoomScale, zoomScale));

    m_windowLayerRenderTexture.draw(m_lightLayerSprite, m_lightBlendMode);

    if (m_properties.ShowTileHighlight == true)
    {
        if (tb::Utility::MyImGui::isActive() == false)
        {
            drawTileHighlight();
        }
    }

    m_windowLayerRenderTexture.display();

    sf::Texture windowLayerTexture = m_windowLayerRenderTexture.getTexture();

    sf::FloatRect windowLayerSpriteLocalBounds = m_windowLayerSprite.getLocalBounds();

    m_windowLayerSprite.setTexture(windowLayerTexture);
    m_windowLayerSprite.setPosition(spritePosition);
    m_windowLayerSprite.setOrigin
    (
        windowLayerSpriteLocalBounds.width  / 2,
        windowLayerSpriteLocalBounds.height / 2
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
        rectangleShape.setSize(sf::Vector2f(tb::Constants::TileSizeFloat, tb::Constants::TileSizeFloat));
        rectangleShape.setPosition(mousePixelCoords);
        rectangleShape.setFillColor(sf::Color::Cyan);

        m_windowLayerRenderTexture.draw(rectangleShape);
    }
}

sf::IntRect GameWindow::getTileRect()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    int tileX = player->getTileX();
    int tileY = player->getTileY();

    sf::Vector2i viewPositionOffset = static_cast<sf::Vector2i>(getViewPositionOffset());

    // convert from pixel coords to tile coords
    viewPositionOffset.x /= tb::Constants::TileSize;
    viewPositionOffset.y /= tb::Constants::TileSize;

    tileX += viewPositionOffset.x;
    tileY += viewPositionOffset.y;

    tileX -= (m_numTilesFromCenterX + m_numTilesToDrawOffscreen);
    tileY -= (m_numTilesFromCenterY + m_numTilesToDrawOffscreen);

    int tileWidth  = m_numTilesX + (m_numTilesToDrawOffscreen * 2);
    int tileHeight = m_numTilesY + (m_numTilesToDrawOffscreen * 2);

    return sf::IntRect(tileX, tileY, tileWidth, tileHeight);
}

void GameWindow::setLightBrightness(tb::LightBrightness_t lightBrightness)
{
    m_lightBrightness = lightBrightness;
}

tb::LightBrightness_t GameWindow::getLightBrightness()
{
    return m_lightBrightness;
}

int GameWindow::getNumTilesX()
{
    return m_numTilesX;
}

int GameWindow::getNumTilesY()
{
    return m_numTilesY;
}

int GameWindow::getNumTilesFromCenterX()
{
    return m_numTilesFromCenterX;
}

int GameWindow::getNumTilesFromCenterY()
{
    return m_numTilesFromCenterY;
}

int GameWindow::getNumTilesToDrawOffscreen()
{
    return m_numTilesToDrawOffscreen;
}

}
