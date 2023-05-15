#include "tb/MiniMapWindow.h"

namespace tb
{

MiniMapWindow::MiniMapWindow()
{
    m_window.create(m_windowSize.x, m_windowSize.y);

    m_view.reset(sf::FloatRect(0.0f, 0.0f, m_viewSize.x, m_viewSize.y));

    m_vertexArray.setPrimitiveType(sf::Quads);
}

MiniMapWindow::~MiniMapWindow()
{
    //
}

sf::Vector2f MiniMapWindow::getPosition()
{
    return m_position;
}

void MiniMapWindow::setPosition(const sf::Vector2f& position)
{
    m_position = position;
}

sf::FloatRect MiniMapWindow::getRect()
{
    sf::FloatRect rect;

    rect.left = m_position.x;
    rect.top = m_position.y;

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_window.getSize());

    rect.width = windowSize.x;
    rect.height = windowSize.y;

    return rect;
}

void MiniMapWindow::drawDebugRect()
{
    sf::FloatRect windowRect = getRect();

    g_Game.drawDebugRect(windowRect);
}

void MiniMapWindow::drawWoodBorder()
{
    sf::FloatRect windowRect = getRect();

    g_Game.drawWoodBorder(windowRect, true);
}

sf::Vector2f MiniMapWindow::getMousePixelPosition()
{
    sf::Vector2f mousePosition2f = g_RenderWindow.getMousePosition2f();

    // game window is offset inside render window
    mousePosition2f.x -= m_position.x;
    mousePosition2f.y -= m_position.y;

    sf::Vector2i mousePosition2i = static_cast<sf::Vector2i>(mousePosition2f);

    sf::Vector2f pixelPosition = m_window.mapPixelToCoords(mousePosition2i, m_view);

    return pixelPosition;
}

sf::Vector2f MiniMapWindow::getMousePixelCoords()
{
    sf::Vector2f pixelCoords2f = getMousePixelPosition();

    const float tileSize = tb::Constants::TileSizeFloat;

    // this accounts for when the mouse is out of bounds in the top left corner of the map, in the void
    if (pixelCoords2f.x < 0.0f)
    {
        pixelCoords2f.x -= tileSize;
    }

    if (pixelCoords2f.y < 0.0f)
    {
        pixelCoords2f.y -= tileSize;
    }

    // this rounds to the nearest tile size
    pixelCoords2f.x -= std::fmodf(pixelCoords2f.x, tileSize);
    pixelCoords2f.y -= std::fmodf(pixelCoords2f.y, tileSize);

    return pixelCoords2f;
}

sf::Vector2i MiniMapWindow::getMouseTileCoords()
{
    sf::Vector2f pixelCoords = getMousePixelCoords();

    sf::Vector2i tileCoords = static_cast<sf::Vector2i>(pixelCoords);

    tileCoords.x /= tb::Constants::TileSize;
    tileCoords.y /= tb::Constants::TileSize;

    return tileCoords;
}

bool MiniMapWindow::isMouseInsideWindow()
{
    sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

    sf::FloatRect windowRect = MiniMapWindow::getRect();

    return windowRect.contains(mousePosition);
}

void MiniMapWindow::handleMouseWheelMovedEvent(sf::Event event)
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

    m_view.setSize(sf::Vector2f(m_viewSize.x * m_zoomScale, m_viewSize.y * m_zoomScale));
}

void MiniMapWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void MiniMapWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void MiniMapWindow::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    if (isDebugModeEnabled == false)
    {
        resetViewPositionOffset();
    }

    setViewPositionOffset(g_GameWindow.getViewPositionOffset());

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_window.getSize());

    float padding = tb::Constants::PaddingRenderWindow + tb::Constants::PaddingWoodBorder + tb::Constants::PaddingBlackRectangle;

    sf::Vector2f windowPosition;
    windowPosition.x = renderWindowSize.x - padding - windowSize.x;
    windowPosition.y = g_MenuBar.getHeight() + padding;

    setPosition(windowPosition);

    tb::Creature::Ptr player = g_Game.getPlayer();

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

    m_window.clear(sf::Color::Black);

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtZ(player->getZ());

    if (tileMapTiles != nullptr)
    {
        sf::IntRect tileRect = g_GameWindow.getTileRect();

        if (isZoomed() == true)
        {
            // only use X and not Y because the minimap is a square with 1:1 ratio

            int numTilesFromCenterX = g_GameWindow.getNumTilesFromCenterX();

            int tileScale = static_cast<int>(m_zoomScale);

            int tileScaleXY = numTilesFromCenterX * tileScale;

            tileRect.left   -= tileScaleXY;
            tileRect.top    -= tileScaleXY;
            tileRect.width  += tileScaleXY * 2;
            tileRect.height += tileScaleXY * 2;
        }
        else
        {
            // need to draw 1 tile extra to fill whole window
            tileRect.left   -= 1;
            tileRect.top    -= 1;
            tileRect.width  += 2;
            tileRect.height += 2;
        }

        drawTileMap(tileRect, tileMapTiles);
    }

    if (isDebugModeEnabled == true)
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

    renderWindow->draw(m_windowSprite);
}

void MiniMapWindow::drawTileMap(const sf::IntRect& tileRect, tb::TileMap::Ptr tileMap)
{
    tb::Tile::List tileList = tileMap->getTileListWithinTileRect(tileRect);

    if (tileList.size() == 0)
    {
        return;
    }

    int numVertices = (tileRect.width * tileRect.height) * 4;

    m_vertexArray.clear();
    m_vertexArray.resize(numVertices);

    for (auto& tile : tileList)
    {
        tb::SpriteID_t tileSpriteID = tile->getSpriteID();

        if (tileSpriteID == tb::Constants::SpriteIDNull)
        {
            continue;
        }

        tb::SpriteFlags* tileSpriteFlags = tile->getSpriteFlags();

        float tileX = tile->getPixelX();
        float tileY = tile->getPixelY();

        const float tileSize = tb::Constants::TileSizeFloat;

        sf::Vertex vertex[4];

        // top left, top right, bottom right, bottom left
        vertex[0].position = sf::Vector2f(tileX,            tileY);
        vertex[1].position = sf::Vector2f(tileX + tileSize, tileY);
        vertex[2].position = sf::Vector2f(tileX + tileSize, tileY + tileSize);
        vertex[3].position = sf::Vector2f(tileX,            tileY + tileSize);

        sf::Color color;
        color.r = 8;
        color.g = 8;
        color.b = 8;

        if (tileSpriteFlags->hasFlag(tb::SpriteFlag::Water) == true)
        {
            color.r = 0;
            color.g = 0;
            color.b = 255;
        }

        tb::Object::List* objectList = tile->getObjectList();

        if (objectList->size() != 0)
        {
            color.r = 255;
            color.g = 255;
            color.b = 255;
        }

        tb::Creature::List* creatureList = tile->getCreatureList();

        if (creatureList->size() != 0)
        {
            color.r = 0;
            color.g = 255;
            color.b = 0;
        }

        color.a = 255;

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;

        m_vertexArray.append(vertex[0]);
        m_vertexArray.append(vertex[1]);
        m_vertexArray.append(vertex[2]);
        m_vertexArray.append(vertex[3]);
    }

    m_window.draw(m_vertexArray);
}

void MiniMapWindow::drawTileHighlight()
{
    sf::Vector2f mousePixelCoords = getMousePixelCoords();

    sf::RectangleShape rectangleShape;
    rectangleShape.setSize(sf::Vector2f(tb::Constants::TileSizeFloat, tb::Constants::TileSizeFloat));
    rectangleShape.setPosition(mousePixelCoords);
    rectangleShape.setFillColor(sf::Color::Cyan);

    m_window.draw(rectangleShape);
}

sf::View* MiniMapWindow::getView()
{
    return &m_view;
}

sf::Vector2f MiniMapWindow::getViewPosition()
{
    return m_viewPosition + m_viewPositionOffset;
}

void MiniMapWindow::setViewPosition(sf::Vector2f position)
{
    m_viewPosition = position + m_viewPositionOffset;
}

sf::Vector2f MiniMapWindow::getViewPositionOffset()
{
    return m_viewPositionOffset;
}

void MiniMapWindow::setViewPositionOffset(sf::Vector2f offset)
{
    m_viewPositionOffset = offset;
}

void MiniMapWindow::resetViewPositionOffset()
{
    m_viewPositionOffset.x = 0.0f;
    m_viewPositionOffset.y = 0.0f;
}

float MiniMapWindow::getZoomScale()
{
    return m_zoomScale;
}

float MiniMapWindow::getZoomScaleMinimum()
{
    return m_zoomScaleMinimum;
}

float MiniMapWindow::getZoomScaleMaximum()
{
    return m_zoomScaleMaximum;
}

bool MiniMapWindow::isZoomed()
{
    return m_zoomScale > m_zoomScaleMinimum;
}

}
