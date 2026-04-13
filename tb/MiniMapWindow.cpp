#include "common.h"

#include "tb/MiniMapWindow.h"

namespace tb
{

MiniMapWindow::MiniMapWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();
}

MiniMapWindow::~MiniMapWindow()
{
    //
}

void MiniMapWindow::handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled)
{
    // scrolled up
    if (eventMouseWheelScrolled->delta > 0)
    {
        // zoom in
        zoomIn();
    }
    // scrolled down
    else if (eventMouseWheelScrolled->delta < 0)
    {
        // zoom out
        zoomOut();
    }
}

void MiniMapWindow::handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed)
{
    //
}

void MiniMapWindow::handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased)
{
    //
}

void MiniMapWindow::setPositionInLayout()
{
    sf::FloatRect GUIRightLayoutRect = g_GUI.getRightLayoutRect();

    setPosition(GUIRightLayoutRect.position);
}

void MiniMapWindow::draw()
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

    sf::Vector2f viewPositionOffset = g_GameWindow.getViewPositionOffset();

    setViewPositionOffset(viewPositionOffset);

    viewPosition.x += viewPositionOffset.x;
    viewPosition.y += viewPositionOffset.y;

    sf::View* view = getView();

    view->setCenter(viewPosition);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    windowRenderTexture->clear(sf::Color::Black);

    tb::TileMap::Ptr tileMapTiles = g_Map.getTileMapOfTilesAtAxisZ(player->getAxisZ());

    if (tileMapTiles != nullptr)
    {
        tb::TileRect tileRect = g_GameWindow.getTileRect();

        if (isZoomed() == true)
        {
            // can use either X or Y because the minimap is a square with equal width and height
            std::uint32_t numTilesFromCenterX = g_GameWindow.getNumTilesFromCenterX();

            float zoomScale = getZoomScale();

            std::uint32_t tileScale = static_cast<std::uint32_t>(zoomScale);

            std::uint32_t tileScaleXY = numTilesFromCenterX * tileScale;

            tileRect.position.x    -= tileScaleXY;
            tileRect.position.y    -= tileScaleXY;
            tileRect.size.x        += tileScaleXY * 2;
            tileRect.size.y        += tileScaleXY * 2;
        }
        else
        {
            // need to draw 1 tile extra to fill whole window
            tileRect.position.x    -= 1;
            tileRect.position.y    -= 1;
            tileRect.size.x        += 2;
            tileRect.size.y        += 2;
        }

        drawTileMap(tileRect, tileMapTiles);
    }

    if (isDebugModeEnabled == true)
    {
        if (tb::LibIMGUI::isActive() == false)
        {
            drawTileHighlight();
        }
    }

    windowRenderTexture->display();

    drawToRenderWindow();
}

void MiniMapWindow::drawTileMap(const tb::TileRect& tileRect, tb::TileMap::Ptr tileMap)
{
    tb::Tile::List tileList = tileMap->getTileListWithinTileRect(tileRect);

    if (tileList.size() == 0)
    {
        return;
    }

    const float tileSize = tb::Constants::TileSizeAsFloat;

    const std::uint32_t numVertices = static_cast<std::uint32_t>(tileRect.size.x * tileRect.size.y) * m_numVertexPerTile;

    m_vertexList.clear();
    m_vertexList.reserve(numVertices);

    for (auto& tile : tileList)
    {
        tb::SpriteID tileSpriteID = tile->getSpriteID();

        if (tileSpriteID == tb::Constants::SpriteIDNull)
        {
            continue;
        }

        tb::SpriteFlags* tileSpriteFlags = tile->getSpriteFlags();

        float tileX = tile->getPixelX();
        float tileY = tile->getPixelY();

        // we have to render the square as two triangles
        // ______
        // |\   |
        // | \  |
        // |__\ |
        sf::Vertex vertex[m_numVertexPerTile];

        // first triangle
        vertex[0].position = sf::Vector2f(tileX,            tileY);            // top left
        vertex[1].position = sf::Vector2f(tileX + tileSize, tileY);            // top right
        vertex[2].position = sf::Vector2f(tileX,            tileY + tileSize); // bottom left

        // second triangle
        vertex[3].position = sf::Vector2f(tileX,            tileY + tileSize); // bottom left
        vertex[4].position = sf::Vector2f(tileX + tileSize, tileY);            // top right
        vertex[5].position = sf::Vector2f(tileX + tileSize, tileY + tileSize); // bottom right

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
            color.r = 255;
            color.g = 0;
            color.b = 0;
        }

        color.a = 255;

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;
        vertex[4].color = color;
        vertex[5].color = color;

        m_vertexList.push_back(vertex[0]);
        m_vertexList.push_back(vertex[1]);
        m_vertexList.push_back(vertex[2]);
        m_vertexList.push_back(vertex[3]);
        m_vertexList.push_back(vertex[4]);
        m_vertexList.push_back(vertex[5]);
    }

    tb::VertexList crosshairVertexList = createCrosshairVertexList();

    m_vertexList.insert(m_vertexList.end(), crosshairVertexList.begin(), crosshairVertexList.end());

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    sf::RenderStates renderStates = sf::RenderStates::Default;

    windowRenderTexture->draw(&m_vertexList[0], m_vertexList.size(), sf::PrimitiveType::Triangles, renderStates);
}

void MiniMapWindow::drawTileHighlight()
{
    tb::PixelCoords mousePixelCoords = getMousePixelCoords();

    sf::RectangleShape rectangleShape;
    rectangleShape.setSize(sf::Vector2f(tb::Constants::TileSizeAsFloat, tb::Constants::TileSizeAsFloat));
    rectangleShape.setPosition(mousePixelCoords);
    rectangleShape.setFillColor(sf::Color::Cyan);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->draw(rectangleShape);
}

tb::VertexList MiniMapWindow::createCrosshairVertexList()
{
    tb::Creature::Ptr player = g_Game.getPlayer();

    tb::PixelCoords playerPixelCoords = player->getPixelCoords();

    const float tileSize = tb::Constants::TileSizeAsFloat;

    std::vector<tb::PixelCoords> pixelCoordsList;
    pixelCoordsList.reserve(m_numCrosshairTiles);

    pixelCoordsList.push_back(playerPixelCoords);

    if (isZoomed() == true)
    {
        tb::PixelCoords northPixelCoords = playerPixelCoords;
        tb::PixelCoords southPixelCoords = playerPixelCoords;
        tb::PixelCoords westPixelCoords = playerPixelCoords;
        tb::PixelCoords eastPixelCoords = playerPixelCoords;

        northPixelCoords.y -= tileSize;
        southPixelCoords.y += tileSize;
        westPixelCoords.x -= tileSize;
        eastPixelCoords.x += tileSize;

        pixelCoordsList.push_back(northPixelCoords);
        pixelCoordsList.push_back(southPixelCoords);
        pixelCoordsList.push_back(westPixelCoords);
        pixelCoordsList.push_back(eastPixelCoords);
    }

    const std::uint32_t numVertices = static_cast<std::uint32_t>(m_numCrosshairTiles * m_numVertexPerTile);

    tb::VertexList vertexList;
    vertexList.reserve(numVertices);

    for (auto& pixelCoords : pixelCoordsList)
    {
        sf::Vertex vertex[m_numVertexPerTile];

        // first triangle
        vertex[0].position = sf::Vector2f(pixelCoords.x,            pixelCoords.y);            // top left
        vertex[1].position = sf::Vector2f(pixelCoords.x + tileSize, pixelCoords.y);            // top right
        vertex[2].position = sf::Vector2f(pixelCoords.x,            pixelCoords.y + tileSize); // bottom left

        // second triangle
        vertex[3].position = sf::Vector2f(pixelCoords.x,            pixelCoords.y + tileSize); // bottom left
        vertex[4].position = sf::Vector2f(pixelCoords.x + tileSize, pixelCoords.y);            // top right
        vertex[5].position = sf::Vector2f(pixelCoords.x + tileSize, pixelCoords.y + tileSize); // bottom right

        sf::Color color;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;
        vertex[4].color = color;
        vertex[5].color = color;

        vertexList.push_back(vertex[0]);
        vertexList.push_back(vertex[1]);
        vertexList.push_back(vertex[2]);
        vertexList.push_back(vertex[3]);
        vertexList.push_back(vertex[4]);
        vertexList.push_back(vertex[5]);
    }

    return vertexList;
}

}
