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

void GameWindow::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    if (isDebugModeEnabled == false)
    {
        resetViewPositionOffset();
    }

    float windowSizeScale = getSizeScale();

    sf::Vector2f windowPosition = sf::Vector2f(32.0f, 32.0f + g_MenuBar.getHeight());

    setPosition(windowPosition);

    tb::Creature::Ptr player = g_Game.getPlayer();

    sf::Vector2f viewPosition =
    (
        sf::Vector2f
        (
            player->getPixelX() + tb::Constants::TileSizeHalfFloat,
            player->getPixelY() + tb::Constants::TileSizeHalfFloat
        )
    );

    sf::View* view = getView();

    view->setCenter(viewPosition);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    if (isDebugModeEnabled == true)
    {
        windowRenderTexture->clear(sf::Color::Magenta);
    }
    else
    {
        windowRenderTexture->clear(sf::Color::Black);
    }

    tb::ZAxis_t zBegin = tb::ZAxis::Min;
    tb::ZAxis_t zEnd = tb::ZAxis::Max;

    // check if the player is underground
    if (player->getZ() < tb::ZAxis::Default)
    {
        // draw from the bottom to 1 level below the default
        // this will draw everything that is underground
        zBegin = tb::ZAxis::Min;
        zEnd = tb::ZAxis::Default - 1;
    }
    else
    {
        // draw from the default level to the top
        // this will draw everything that is aboveground
        zBegin = tb::ZAxis::Default;
        zEnd = tb::ZAxis::Max;
    }

    //g_Log.write("zBegin,zEnd: {},{}\n", zBegin, zEnd);

    sf::IntRect tileRect = getTileRect();

    for (tb::ZAxis_t z = zBegin; z < zEnd; z++)
    {
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

        // check for ceilings and rooftops above the player
        if (z < tb::Constants::NumZAxis)
        {
            if (g_Game.findTilesAboveThing(player, z + 1) == true)
            {
                break;
            }
        }
    }

    windowRenderTexture->display();

    sf::Texture windowSpriteTexture = windowRenderTexture->getTexture();

    sf::Sprite* windowSprite = getWindowSprite();

    windowSprite->setTexture(windowSpriteTexture);
    windowSprite->setPosition(windowPosition);
    windowSprite->setScale(sf::Vector2f(windowSizeScale, windowSizeScale));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(*windowSprite);
}

void GameWindow::drawMapLayerAtZ(tb::ZAxis_t z)
{
    sf::IntRect tileRect = getTileRect();

    sf::IntRect tileRectForLights;

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

        tileRectForLights = tileRect;
    }
    else
    {
        // this checks for lights from farther away so they
        // don't pop in suddenly when walking around
        tileRectForLights = getTileRect();
        tileRectForLights.left   -= m_numTilesX;
        tileRectForLights.top    -= m_numTilesY;
        tileRectForLights.width  += m_numTilesX * 2;
        tileRectForLights.height += m_numTilesY * 2;
    }

    sf::View* view = getView();

    sf::Vector2f spritePosition = view->getCenter();

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtZ(z);

    if (tileMapTiles == nullptr)
    {
        return;
    }

    m_windowLayerRenderTexture.setView(*view);
    m_windowLayerRenderTexture.clear(sf::Color::Transparent);

    tileMapTiles->drawTiles(tileRect, m_windowLayerRenderTexture);

    tb::TileMap::Ptr tileMapTileEdges = g_Map.getTileMapOfTileEdgesAtZ(z);

    if (tileMapTileEdges != nullptr)
    {
        tileMapTileEdges->drawTiles(tileRect, m_windowLayerRenderTexture);
    }

    tileMapTiles->drawObjects(tileRect, m_windowLayerRenderTexture);

    m_lightLayerRenderTexture.setView(*view);
    m_lightLayerRenderTexture.clear(sf::Color(m_lightBrightness, m_lightBrightness, m_lightBrightness));

    tileMapTiles->drawLights(tileRectForLights, m_lightLayerRenderTexture, m_lightBrightness);

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
        m_tileHighlightSprite.setIDByName(m_tileHightlightSpriteName);
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
