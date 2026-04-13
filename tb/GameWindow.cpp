#include "common.h"

#include "tb/GameWindow.h"

namespace tb
{

GameWindow::GameWindow() :
    m_windowLayerSprite(tb::Resources::Textures::Null),
    m_lightLayerSprite(tb::Resources::Textures::Null),
    m_tileHighlightSprite(tb::Resources::Textures::SpriteSheet)
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    sf::Vector2u windowRenderTextureSize2u = static_cast<sf::Vector2u>(m_windowRenderTextureSize);

    if (m_windowLayerRenderTexture.resize(windowRenderTextureSize2u) == false)
    {
        g_Log.write("ERROR: failed to resize RenderTexture\n");
    }

    if (m_lightLayerRenderTexture.resize(windowRenderTextureSize2u) == false)
    {
        g_Log.write("ERROR: failed to resize RenderTexture\n");
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

GameWindow::Properties* GameWindow::getProperties()
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
    sf::FloatRect GUILeftLayoutRect = g_GUI.getLeftLayoutRect();

    return GUILeftLayoutRect;
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

    sf::View* view = getView();

    view->setCenter(viewPosition);
    view->move(viewPositionOffset);

    //sf::Vector2f viewCenter = view->getCenter();
    //sf::Vector2f viewSize = view->getSize();
    //sf::FloatRect viewViewport = view->getViewport();
    //g_Log.write("----- View Debug -----\n");
    //g_Log.write("--> View Center: x{},y{}\n", viewCenter.x, viewCenter.y);
    //g_Log.write("--> View Size: x{},y{}\n", viewSize.x, viewSize.y);
    //g_Log.write("--> View Viewport: x{},y{},w{},h{}\n", viewViewport.position.x, viewViewport.position.y, viewViewport.size.x, viewViewport.size.y);

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

    tb::AxisZ playerAxisZ = player->getAxisZ();

    tb::AxisZVisibility playerAxisZVisibility = g_Game.getPlayerAxisZVisibility();

    tb::TileRect tileRect = getTileRect();

    //g_Log.write("Tile Rect Debug: x{},y{},w{},h{}\n", tileRect.position.x, tileRect.position.y, tileRect.size.x, tileRect.size.y);

    for (tb::AxisZ axisZ = playerAxisZVisibility.Begin; axisZ < playerAxisZVisibility.End; axisZ++)
    {
        // check for ceilings and rooftops above the player
        if (axisZ < tb::Constants::NumAxisZ && axisZ > playerAxisZ)
        {
            if (g_Game.doesCeilingExistAbovePlayerAtAxisZ(axisZ) == true)
            {
                break;
            }
        }

        tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtAxisZ(axisZ);

        if (tileMap == nullptr)
        {
            continue;
        }

        bool tileMapIsVisible = tileMap->isVisibleWithinTileRect(tileRect);

        if (tileMapIsVisible == true)
        {
            drawMapLayerAtAxisZ(axisZ);
        }
    }

    windowRenderTexture->display();

    drawToRenderWindow();
}

void GameWindow::drawMapLayerAtAxisZ(tb::AxisZ axisZ)
{
    tb::TileRect tileRect = getTileRect();

    //g_Log.write("Tile Rect Debug: x{},y{},w{},h{}\n", tileRect.position.x, tileRect.position.y, tileRect.size.x, tileRect.size.y);

    tb::TileRect tileRectIncreased = tileRect;

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

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtAxisZ(axisZ);

    if (tileMapTiles == nullptr)
    {
        g_Log.write("ERROR: tileMapTiles == nullptr at axis Z: {}\n", axisZ);
        return;
    }

    tb::AxisZ playerAxisZ = g_Game.getPlayer()->getAxisZ();

    // only animate water for the default z-axis and while the player is aboveground
    if (playerAxisZ >= tb::Constants::AxisZDefault && axisZ == tb::Constants::AxisZDefault)
    {
        sf::Time animatedWaterTimeElapsed = m_animatedWaterClock.getElapsedTime();
        if (animatedWaterTimeElapsed >= m_animatedWaterTime)
        {
            if (tileMapTiles->doAnimatedWater(tileRectIncreased) == false)
            {
                g_Log.write("ERROR: failed to animate water at axis Z: {}\n", axisZ);
            }

            m_animatedWaterClock.restart();
        }
    }

    sf::Time animatedObjectsTimeElapsed = m_animatedObjectsClock.getElapsedTime();
    if (animatedObjectsTimeElapsed >= m_animatedObjectsTime)
    {
        if (tileMapTiles->doAnimatedObjects(tileRectIncreased) == false)
        {
            g_Log.write("ERROR: failed to animate objects at axis Z: {}\n", axisZ);
        }

        m_animatedObjectsClock.restart();
    }

    m_windowLayerRenderTexture.setView(*view);
    m_windowLayerRenderTexture.clear(sf::Color::Transparent);

    tileMapTiles->drawTiles(tileRect, m_windowLayerRenderTexture);

    tb::TileMap::Ptr tileMapTileEdges = g_Map.getTileMapOfTileEdgesAtAxisZ(axisZ);

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
        if (tb::LibIMGUI::isActive() == false)
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
    tb::PixelCoords mousePixelCoords = getMousePixelCoords();

    if (isZoomed() == false)
    {
        m_tileHighlightSprite.setID(tb::Resources::Sprites::TileHighlight);
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

tb::TileRect GameWindow::getTileRect()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    tb::TileCoords tileCoords = player->getTileCoords();

    sf::Vector2i viewPositionOffset = static_cast<sf::Vector2i>(getViewPositionOffset());

    // convert from pixel coords to tile coords
    if (viewPositionOffset.x != 0)
    {
        viewPositionOffset.x /= tb::Constants::TileSize;
    }
    if (viewPositionOffset.y != 0)
    {
        viewPositionOffset.y /= tb::Constants::TileSize;
    }

    tileCoords.x += viewPositionOffset.x;
    tileCoords.y += viewPositionOffset.y;

    tileCoords.x -= (m_numTilesFromCenterX + m_numTilesToDrawOffscreen);
    tileCoords.y -= (m_numTilesFromCenterY + m_numTilesToDrawOffscreen);

    std::int32_t tileWidth  = m_numTilesX + (m_numTilesToDrawOffscreen * 2);
    std::int32_t tileHeight = m_numTilesY + (m_numTilesToDrawOffscreen * 2);

    return tb::TileRect(tileCoords, sf::Vector2i(tileWidth, tileHeight));
}

void GameWindow::setLightBrightness(tb::LightBrightness lightBrightness)
{
    m_lightBrightness = lightBrightness;
}

tb::LightBrightness GameWindow::getLightBrightness()
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
