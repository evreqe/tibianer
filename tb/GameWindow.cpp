#include "tb/GameWindow.h"

namespace tb
{

GameWindow::GameWindow()
{
    m_window.create(m_pixelWidth, m_pixelHeight);
    m_windowLayer.create(m_pixelWidth, m_pixelHeight);

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

    m_position.y = m_position.y + g_MenuBar.getHeight();
}

sf::Vector2f GameWindow::getMousePixelCoords()
{
    sf::Vector2f mousePosition2f = g_RenderWindow.getMousePosition();

    // game window is offset inside render window
    mousePosition2f.x = mousePosition2f.x - m_position.x;
    mousePosition2f.y = mousePosition2f.y - m_position.y;

    // apply scale
    mousePosition2f.x = mousePosition2f.x / m_scale;
    mousePosition2f.y = mousePosition2f.y / m_scale;

    //g_Log.write("mousePosition2f: {},{}\n", mousePosition2f.x, mousePosition2f.y);

    sf::Vector2i mousePosition2i = static_cast<sf::Vector2i>(mousePosition2f);

    sf::Vector2f pixelCoords2f = m_window.mapPixelToCoords(mousePosition2i, m_view);

    // this accounts for when the mouse is out of bounds in the top left corner of the map, in the void
    {
        if (pixelCoords2f.x < 0.0f)
        {
            pixelCoords2f.x = pixelCoords2f.x - tb::Constants::TileSizeFloat;
        }

        if (pixelCoords2f.y < 0.0f)
        {
            pixelCoords2f.y = pixelCoords2f.y - tb::Constants::TileSizeFloat;
        }
    }

    //g_Log.write("pixelCoords2f: {},{}\n", pixelCoords2f.x, pixelCoords2f.y);

    pixelCoords2f.x = pixelCoords2f.x - (std::fmodf(pixelCoords2f.x, tb::Constants::TileSizeFloat));
    pixelCoords2f.y = pixelCoords2f.y - (std::fmodf(pixelCoords2f.y, tb::Constants::TileSizeFloat));

    //g_Log.write("pixelCoords2f: {},{}\n", pixelCoords2f.x, pixelCoords2f.y);

    //g_Log.write("--------\n");

    return pixelCoords2f;
}

sf::Vector2i GameWindow::getMouseTileCoords()
{
    sf::Vector2f pixelCoords = getMousePixelCoords();

    sf::Vector2i tileCoords;

    tileCoords.x = static_cast<int>(pixelCoords.x / tb::Constants::TileSizeFloat);
    tileCoords.y = static_cast<int>(pixelCoords.y / tb::Constants::TileSizeFloat);

    return tileCoords;
}

sf::FloatRect GameWindow::getRect()
{
    sf::FloatRect rect;

    rect.left = m_position.x;
    rect.top = m_position.y;

    rect.width = m_window.getSize().x * m_scale;
    rect.height = m_window.getSize().y * m_scale;

    return rect;
}

void GameWindow::drawRect()
{
    sf::FloatRect rect = GameWindow::getRect();

    sf::RectangleShape rs;
    rs.setPosition(sf::Vector2f(rect.left, rect.top));
    rs.setSize(sf::Vector2f(rect.width, rect.height));
    rs.setFillColor(sf::Color::Transparent);
    rs.setOutlineColor(sf::Color::Blue);
    rs.setOutlineThickness(1.0f);

    g_RenderWindow.getWindow()->draw(rs);
}

bool GameWindow::isMouseInsideWindow()
{
    sf::Vector2f position = g_RenderWindow.getMousePosition();

    sf::FloatRect rect = GameWindow::getRect();

    return tb::Utility::isPositionInsideRectangle<float, float>(position, rect);
}

void GameWindow::handleMouseWheelMovedEvent(sf::Event event)
{
    if (isMouseInsideWindow() == false)
    {
        return;
    }

    // scroll up
    if (event.mouseWheel.delta > 0)
    {
        // zoom in
        m_zoomScale -= m_zoomFactor;

        if (m_zoomScale < m_zoomScaleMinimum)
        {
            m_zoomScale = m_zoomScaleMinimum;
        }
    }

    // scroll down
    else if (event.mouseWheel.delta < 0)
    {
        // zoom out
        m_zoomScale += m_zoomFactor;
    }

    m_view.setSize(sf::Vector2f(m_pixelWidth * m_zoomScale, m_pixelHeight * m_zoomScale));
}

void GameWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    if (isMouseInsideWindow() == false)
    {
        return;
    }

    //
}

void GameWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    if (isMouseInsideWindow() == false)
    {
        return;
    }

    //
}

void GameWindow::drawTileHighlight()
{
    sf::Vector2f mousePixelCoords = getMousePixelCoords();

    m_tileHighlightSprite.setID(m_tileHighlightSpriteID);
    m_tileHighlightSprite.setPosition(mousePixelCoords);

    m_window.draw(m_tileHighlightSprite);
}

void GameWindow::drawLayer(tb::ZAxis_t z)
{
    m_windowLayer.setView(m_view);
    m_windowLayer.clear(sf::Color::Transparent);

    sf::IntRect tileRect = getTileRect();

    g_Map.getTileMapTiles(z)->draw(tileRect, m_windowLayer);
    g_Map.getTileMapTileEdges(z)->draw(tileRect, m_windowLayer);

    m_windowLayer.display();

    m_windowLayerSprite.setTexture(m_windowLayer.getTexture());

    m_windowLayerSprite.setPosition
    (
        static_cast<float>((tileRect.left + 1) * tb::Constants::TileSize),
        static_cast<float>((tileRect.top  + 1) * tb::Constants::TileSize)
    );

    m_window.draw(m_windowLayerSprite);
}

void GameWindow::draw()
{
    setPosition(sf::Vector2f(32.0f, 32.0f));

    tb::Creature::Ptr player = g_Game.getPlayer();

    m_view.setCenter
    (
        player->getPixelX() + tb::Constants::TileSizeHalf,
        player->getPixelY() + tb::Constants::TileSizeHalf
    );

    m_window.setView(m_view);
    m_window.clear(sf::Color::Red);

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

    for (tb::ZAxis_t i = zBegin; i < zEnd + 1; i++)
    {
        bool tileMapIsVisible = g_Map.getTileMapTiles(i)->isVisibleWithinTileRect(tileRect);

        if (tileMapIsVisible == true)
        {
            //g_Log.write("drawGameWindowLayer: {}\n", i);

            drawLayer(i);
        }
    }

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

    if (m_properties.ShowTileHighlight== true)
    {
        drawTileHighlight();
    }

    m_window.display();

    m_windowSprite.setTexture(m_window.getTexture());
    m_windowSprite.setPosition(m_position);
    m_windowSprite.setScale(sf::Vector2f(m_scale, m_scale));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(m_windowSprite);

    //drawRect();
}

sf::IntRect GameWindow::getTileRect()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    int x1 = player->getTileX();
    int y1 = player->getTileY();

    x1 = x1 - m_numTilesFromCenterX - m_numTilesToDrawFromOffscreen;
    y1 = y1 - m_numTilesFromCenterY - m_numTilesToDrawFromOffscreen;

    int x2 = m_tileWidth  + (m_numTilesToDrawFromOffscreen + 1);
    int y2 = m_tileHeight + (m_numTilesToDrawFromOffscreen + 1);

    return sf::IntRect(x1, y1, x2, y2);
}

}
