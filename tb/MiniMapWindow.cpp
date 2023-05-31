#include "tb/MiniMapWindow.h"

namespace tb
{

MiniMapWindow::MiniMapWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    m_vertexArray.setPrimitiveType(sf::Quads);

    initalize();
}

MiniMapWindow::~MiniMapWindow()
{
    //
}

void MiniMapWindow::handleMouseWheelMovedEvent(sf::Event event)
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

void MiniMapWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void MiniMapWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void MiniMapWindow::setPositionInLayout()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(windowRenderTexture->getSize());

    float windowSizeScale = getSizeScale();

    float padding = tb::Constants::PaddingRenderWindow + tb::Constants::PaddingWoodBorder + tb::Constants::PaddingBlackRectangle;

    sf::Vector2f windowPosition;
    windowPosition.x = renderWindowSize.x - padding - (windowSize.x * windowSizeScale);
    windowPosition.y = g_MenuBar.getHeight() + padding;

    setPosition(windowPosition);
}

void MiniMapWindow::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    if (isDebugModeEnabled == false)
    {
        resetViewPositionOffset();
    }

    setPositionInLayout();

    tb::Creature::Ptr player = g_Game.getPlayer();

    sf::Vector2f viewPosition =
    (
        sf::Vector2f
        (
            player->getPixelX() + tb::Constants::TileSizeHalfFloat,
            player->getPixelY() + tb::Constants::TileSizeHalfFloat
        )
    );

    sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

    setViewPositionOffset(viewPositionOffset);

    viewPosition.x += viewPositionOffset.x;
    viewPosition.y += viewPositionOffset.y;

    sf::View* view = getView();

    view->setCenter(viewPosition);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    windowRenderTexture->clear(sf::Color::Black);

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtZ(player->getZ());

    if (tileMapTiles != nullptr)
    {
        sf::IntRect tileRect = g_GameWindow.getTileRect();

        if (isZoomed() == true)
        {
            // only use X and not Y because the minimap is a square with 1:1 ratio

            int numTilesFromCenterX = g_GameWindow.getNumTilesFromCenterX();

            float zoomScale = getZoomScale();

            int tileScale = static_cast<int>(zoomScale);

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

    windowRenderTexture->display();

    drawToRenderWindow();
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

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->draw(m_vertexArray);
}

void MiniMapWindow::drawTileHighlight()
{
    sf::Vector2f mousePixelCoords = getMousePixelCoords();

    sf::RectangleShape rectangleShape;
    rectangleShape.setSize(sf::Vector2f(tb::Constants::TileSizeFloat, tb::Constants::TileSizeFloat));
    rectangleShape.setPosition(mousePixelCoords);
    rectangleShape.setFillColor(sf::Color::Cyan);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->draw(rectangleShape);
}

}
