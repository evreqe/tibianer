#include "tb/GameWindow.h"

namespace tb
{

GameWindow::GameWindow()
{
    m_window.create(m_pixelWidth, m_pixelHeight);
    m_windowLayer.create(m_pixelWidth, m_pixelHeight);

    m_lightLayer.create(m_pixelWidth, m_pixelHeight);

    // this gives the lighting a deep fried burnt effect
    m_lightBlendMode.colorEquation = sf::BlendMode::Equation::ReverseSubtract;
    m_lightBlendMode.alphaEquation = sf::BlendMode::Equation::Add;
    m_lightBlendMode.colorSrcFactor = sf::BlendMode::Factor::OneMinusSrcColor;
    m_lightBlendMode.colorDstFactor = sf::BlendMode::Factor::SrcColor;
    m_lightBlendMode.alphaSrcFactor = sf::BlendMode::Factor::DstAlpha;
    m_lightBlendMode.alphaDstFactor = sf::BlendMode::Factor::DstAlpha;

    m_view.reset(sf::FloatRect(0.0f, 0.0f, m_pixelWidth, m_pixelHeight));
}

GameWindow::~GameWindow()
{
    //
}

GameWindow::Properties_t* GameWindow::getProperties()
{
    return &m_properties;
}

sf::Vector2f GameWindow::getPosition()
{
    return m_position;
}

void GameWindow::setPosition(const sf::Vector2f& position)
{
    m_position = position;
}

sf::FloatRect GameWindow::getRect()
{
    sf::FloatRect rect;

    rect.left = m_position.x;
    rect.top = m_position.y;

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_window.getSize());

    rect.width  = windowSize.x * m_scale;
    rect.height = windowSize.y * m_scale;

    return rect;
}

void GameWindow::drawDebugRect()
{
    sf::FloatRect windowRect = getRect();

    g_Game.drawDebugRect(windowRect);
}

void GameWindow::drawWoodBorder()
{
    sf::FloatRect windowRect = getRect();

    g_Game.drawWoodBorder(windowRect, true);
}

sf::Vector2f GameWindow::getMousePixelPosition()
{
    sf::Vector2f mousePosition2f = g_RenderWindow.getMousePosition2f();

    // game window is offset inside render window
    mousePosition2f.x -= m_position.x;
    mousePosition2f.y -= m_position.y;

    // apply scale
    mousePosition2f.x /= m_scale;
    mousePosition2f.y /= m_scale;

    sf::Vector2i mousePosition2i = static_cast<sf::Vector2i>(mousePosition2f);

    sf::Vector2f pixelPosition = m_window.mapPixelToCoords(mousePosition2i, m_view);

    return pixelPosition;
}

sf::Vector2f GameWindow::getMousePixelCoords()
{
    sf::Vector2f pixelCoords2f = getMousePixelPosition();

    float tileSize = tb::Constants::TileSizeFloat;

    // this accounts for when the mouse is out of bounds in the top left corner of the map, in the void
    {
        if (pixelCoords2f.x < 0.0f)
        {
            pixelCoords2f.x = pixelCoords2f.x - tileSize;
        }

        if (pixelCoords2f.y < 0.0f)
        {
            pixelCoords2f.y = pixelCoords2f.y - tileSize;
        }
    }

    // this rounds to the nearest tile size
    pixelCoords2f.x = pixelCoords2f.x - (std::fmodf(pixelCoords2f.x, tileSize));
    pixelCoords2f.y = pixelCoords2f.y - (std::fmodf(pixelCoords2f.y, tileSize));

    return pixelCoords2f;
}

sf::Vector2i GameWindow::getMouseTileCoords()
{
    sf::Vector2f pixelCoords = getMousePixelCoords();

    sf::Vector2i tileCoords = static_cast<sf::Vector2i>(pixelCoords);

    tileCoords.x /= tb::Constants::TileSize;
    tileCoords.y /= tb::Constants::TileSize;

    return tileCoords;
}

bool GameWindow::isMouseInsideWindow()
{
    sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

    sf::FloatRect windowRect = GameWindow::getRect();

    return windowRect.contains(mousePosition);
}

void GameWindow::handleMouseWheelMovedEvent(sf::Event event)
{
    // scroll up
    if (event.mouseWheel.delta > 0)
    {
        // zoom in
        m_zoomScale -= m_zoomStep;

        if (m_zoomScale <= m_zoomScaleMinimum)
        {
            m_zoomScale = m_zoomScaleMinimum;
        }
    }

    // scroll down
    else if (event.mouseWheel.delta < 0)
    {
        // zoom out
        m_zoomScale += m_zoomStep;

        if (m_zoomScale >= m_zoomScaleMaximum)
        {
            m_zoomScale = m_zoomScaleMaximum;
        }
    }

    m_view.setSize(sf::Vector2f(m_pixelWidth * m_zoomScale, m_pixelHeight * m_zoomScale));
}

void GameWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void GameWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void GameWindow::drawTileHighlight()
{
    sf::Vector2f mousePixelCoords = getMousePixelCoords();

    m_tileHighlightSprite.setIDByName(m_tileHightlightSpriteName);
    m_tileHighlightSprite.setPosition(mousePixelCoords);

    m_window.draw(m_tileHighlightSprite);
}

void GameWindow::drawLayer(tb::ZAxis_t z)
{
    sf::IntRect tileRect = getTileRect();

    sf::Vector2f spritePosition = sf::Vector2f
    (
        static_cast<float>((tileRect.left + m_numTilesToDrawFromOffscreen) * tb::Constants::TileSize),
        static_cast<float>((tileRect.top  + m_numTilesToDrawFromOffscreen) * tb::Constants::TileSize)
    );

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtZ(z);

    if (tileMapTiles == nullptr)
    {
        return;
    }

    m_windowLayer.setView(m_view);
    m_windowLayer.clear(sf::Color::Transparent);

    tileMapTiles->drawTiles(tileRect, m_windowLayer);

    tb::TileMap::Ptr tileMapTileEdges = g_Map.getTileMapOfTileEdgesAtZ(z);

    if (tileMapTileEdges != nullptr)
    {
        tileMapTileEdges->drawTiles(tileRect, m_windowLayer);
    }

    tileMapTiles->drawObjects(tileRect, m_windowLayer);

    m_lightLayer.setView(m_view);
    m_lightLayer.clear(sf::Color(m_lightBrightness, m_lightBrightness, m_lightBrightness));

    tileMapTiles->drawLights(tileRect, m_lightLayer, m_lightBrightness);

    m_lightLayer.display();

    m_lightLayerSprite.setTexture(m_lightLayer.getTexture());
    m_lightLayerSprite.setPosition(spritePosition);

    m_windowLayer.draw(m_lightLayerSprite, m_lightBlendMode);

    m_windowLayer.display();

    m_windowLayerSprite.setTexture(m_windowLayer.getTexture());
    m_windowLayerSprite.setPosition(spritePosition);

    m_window.draw(m_windowLayerSprite);
}

void GameWindow::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    setPosition(sf::Vector2f(32.0f, 32.0f + g_MenuBar.getHeight()));

    tb::Creature::Ptr player = g_Game.getPlayer();

    if (isDebugModeEnabled == false)
    {
        resetViewPositionOffset();
    }

    setViewPosition
    (
        sf::Vector2f
        (
            player->getPixelX() + tb::Constants::TileSizeHalfFloat,
            player->getPixelY() + tb::Constants::TileSizeHalfFloat
        )
    );

    m_view.setCenter(m_viewPosition.x, m_viewPosition.y);

    m_window.setView(m_view);

    if (isDebugModeEnabled == true)
    {
        m_window.clear(sf::Color::Magenta);
    }
    else
    {
        m_window.clear(sf::Color::Black);
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

    for (tb::ZAxis_t i = zBegin; i < zEnd; i++)
    {
        tb::TileMap::Ptr tileMap = g_Map.getTileMapOfTilesAtZ(i);

        if (tileMap == nullptr)
        {
            continue;
        }

        bool tileMapIsVisible = tileMap->isVisibleWithinTileRect(tileRect);

        if (tileMapIsVisible == true)
        {
            drawLayer(i);
        }

        // check for ceilings and rooftops above the player
        if (i < tb::Constants::NumZAxis)
        {
            if (g_Game.findTilesAboveThing(player, i + 1) == true)
            {
                break;
            }
        }
    }

    if (m_properties.ShowTileHighlight == true)
    {
        if (tb::Utility::MyImGui::isActive() == false)
        {
            drawTileHighlight();
        }
    }

    m_window.display();

    sf::Texture windowTexture = m_window.getTexture();

    m_windowSprite.setTexture(windowTexture);
    m_windowSprite.setPosition(m_position);
    m_windowSprite.setScale(sf::Vector2f(m_scale, m_scale));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(m_windowSprite);
}

sf::IntRect GameWindow::getTileRect()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    int x = player->getTileX();
    int y = player->getTileY();

    sf::Vector2i viewPositionOffset = static_cast<sf::Vector2i>(getViewPositionOffset());

    viewPositionOffset.x /= tb::Constants::TileSize;
    viewPositionOffset.y /= tb::Constants::TileSize;

    x += viewPositionOffset.x;
    y += viewPositionOffset.y;

    x = x - m_numTilesFromCenterX - m_numTilesToDrawFromOffscreen;
    y = y - m_numTilesFromCenterY - m_numTilesToDrawFromOffscreen;

    int width  = m_numTilesX + (m_numTilesToDrawFromOffscreen + 1);
    int height = m_numTilesY + (m_numTilesToDrawFromOffscreen + 1);

    return sf::IntRect(x, y, width, height);
}

sf::View* GameWindow::getView()
{
    return &m_view;
}

sf::Vector2f GameWindow::getViewPosition()
{
    return m_viewPosition + m_viewPositionOffset;
}

void GameWindow::setViewPosition(sf::Vector2f position)
{
    m_viewPosition = position + m_viewPositionOffset;
}

sf::Vector2f GameWindow::getViewPositionOffset()
{
    return m_viewPositionOffset;
}

void GameWindow::setViewPositionOffset(sf::Vector2f offset)
{
    m_viewPositionOffset = offset;
}

void GameWindow::resetViewPositionOffset()
{
    m_viewPositionOffset.x = 0.0f;
    m_viewPositionOffset.y = 0.0f;
}

void GameWindow::setScale(float scale)
{
    if (scale < 1.0f)
    {
        scale = 1.0f;
    }

    m_scale = scale;
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

}
