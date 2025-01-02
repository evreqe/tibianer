#include "tb/SfmlGuiWindow.h"

namespace tb
{

SfmlGuiWindow::SfmlGuiWindow() :
    m_windowSprite(tb::Textures::Null)
{
    //
}

SfmlGuiWindow::~SfmlGuiWindow()
{
    //
}

void SfmlGuiWindow::initalize()
{
    bool resizeResult = m_windowRenderTexture.resize(static_cast<sf::Vector2u>(m_windowRenderTextureInitialSize));

    if (resizeResult == false)
    {
        g_Log.write("ERROR: Failed to resize RenderTexture\n");
    }

    sf::View resetView(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), static_cast<sf::Vector2f>(m_viewInitialSize)));
    setView(resetView);
}

void SfmlGuiWindow::drawToRenderWindow()
{
    sf::Texture windowSpriteTexture = m_windowRenderTexture.getTexture();

    m_windowSprite.setTexture(windowSpriteTexture, true);
    m_windowSprite.setPosition(m_position);
    m_windowSprite.setScale(sf::Vector2f(m_sizeScale, m_sizeScale));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(m_windowSprite);
}

sf::FloatRect SfmlGuiWindow::getRect()
{
    sf::FloatRect windowRect;
    windowRect.position = getPosition();
    windowRect.size = getSize();

    return windowRect;
}

sf::Vector2f SfmlGuiWindow::getSize()
{
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_windowRenderTexture.getSize());

    windowSize.x *= m_sizeScale;
    windowSize.y *= m_sizeScale;

    return windowSize;
}

sf::Vector2f SfmlGuiWindow::getMousePixelPosition()
{
    sf::Vector2f mousePosition2f = g_RenderWindow.getMousePosition2f();

    // game window is offset inside render window
    mousePosition2f.x -= m_position.x;
    mousePosition2f.y -= m_position.y;

    // apply size scale
    mousePosition2f.x /= m_sizeScale;
    mousePosition2f.y /= m_sizeScale;

    sf::Vector2i mousePosition2i = static_cast<sf::Vector2i>(mousePosition2f);

    sf::Vector2f pixelPosition = m_windowRenderTexture.mapPixelToCoords(mousePosition2i, m_view);

    return pixelPosition;
}

sf::Vector2f SfmlGuiWindow::getMousePixelCoords()
{
    sf::Vector2f mousePixelPosition = getMousePixelPosition();

    const float tileSize = tb::Constants::TileSizeAsFloat;

    // this accounts for when the mouse is out of bounds in the top left corner of the map, in the void
    if (mousePixelPosition.x < 0.0f)
    {
        mousePixelPosition.x -= tileSize;
    }

    if (mousePixelPosition.y < 0.0f)
    {
        mousePixelPosition.y -= tileSize;
    }

    // this rounds to the nearest tile size
    mousePixelPosition.x -= std::fmodf(mousePixelPosition.x, tileSize);
    mousePixelPosition.y -= std::fmodf(mousePixelPosition.y, tileSize);

    return mousePixelPosition;
}

sf::Vector2i SfmlGuiWindow::getMouseTileCoords()
{
    sf::Vector2f pixelCoords = getMousePixelCoords();

    sf::Vector2i tileCoords = static_cast<sf::Vector2i>(pixelCoords);

    tileCoords.x /= tb::Constants::TileSize;
    tileCoords.y /= tb::Constants::TileSize;

    return tileCoords;
}

bool SfmlGuiWindow::isMouseInsideWindow()
{
    sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

    sf::FloatRect windowRect = getRect();

    return windowRect.contains(mousePosition);
}

sf::Vector2f SfmlGuiWindow::getPosition()
{
    return m_position;
}

void SfmlGuiWindow::setPosition(const sf::Vector2f& position)
{
    m_position = position;
}

sf::View* SfmlGuiWindow::getView()
{
    return &m_view;
}

void SfmlGuiWindow::setView(sf::View view)
{
    m_view = view;
}

sf::Vector2f SfmlGuiWindow::getViewInitialSize()
{
    return m_viewInitialSize;
}

void SfmlGuiWindow::setViewInitialSize(sf::Vector2f size)
{
    m_viewInitialSize = size;
}

sf::Vector2f SfmlGuiWindow::getViewPosition()
{
    return m_view.getCenter();
}

void SfmlGuiWindow::setViewPosition(sf::Vector2f position)
{
    m_view.setCenter(position);
}

sf::Vector2f SfmlGuiWindow::getViewPositionOffset()
{
    return m_viewPositionOffset;
}

void SfmlGuiWindow::setViewPositionOffset(sf::Vector2f offset)
{
    m_viewPositionOffset = offset;
}

void SfmlGuiWindow::resetViewPositionOffset()
{
    m_viewPositionOffset.x = 0.0f;
    m_viewPositionOffset.y = 0.0f;
}

sf::RenderTexture* SfmlGuiWindow::getWindowRenderTexture()
{
    return &m_windowRenderTexture;
}

sf::Vector2i SfmlGuiWindow::getWindowRenderTextureInitialSize()
{
    return m_windowRenderTextureInitialSize;
}

void SfmlGuiWindow::setWindowRenderTextureInitialSize(sf::Vector2i size)
{
    m_windowRenderTextureInitialSize = size;
}

sf::Sprite* SfmlGuiWindow::getWindowSprite()
{
    return &m_windowSprite;
}

sf::FloatRect SfmlGuiWindow::getRectOfSprite(const sf::Sprite& sprite)
{
    sf::FloatRect spriteRect;
    spriteRect.position = sprite.getPosition();
    spriteRect.size = sprite.getLocalBounds().size;

    return spriteRect;
}

float SfmlGuiWindow::getSizeScale()
{
    return m_sizeScale;
}

void SfmlGuiWindow::setSizeScale(float scale)
{
    clampSizeScale(scale);

    m_sizeScale = scale;
}

void SfmlGuiWindow::clampSizeScale(float& scale)
{
    scale = std::clamp(scale, m_sizeScaleMinimum, m_sizeScaleMaximum);
}

float SfmlGuiWindow::getSizeScaleStep()
{
    return m_sizeScaleStep;
}

float SfmlGuiWindow::getSizeScaleMinimum()
{
    return m_sizeScaleMinimum;
}

float SfmlGuiWindow::getSizeScaleMaximum()
{
    return m_sizeScaleMaximum;
}

bool SfmlGuiWindow::isSized()
{
    return m_sizeScale != m_sizeScaleDefault;
}

void SfmlGuiWindow::sizeReset()
{
    m_sizeScale = m_sizeScaleDefault;
}

float SfmlGuiWindow::getZoomScale()
{
    return m_zoomScale;
}

void SfmlGuiWindow::setZoomScale(float scale)
{
    clampZoomScale(scale);

    m_sizeScale = scale;
}

void SfmlGuiWindow::clampZoomScale(float& scale)
{
    scale = std::clamp(scale, m_zoomScaleMinimum, m_zoomScaleMaximum);
}

float SfmlGuiWindow::getZoomScaleStep()
{
    return m_zoomScaleStep;
}

float SfmlGuiWindow::getZoomScaleMinimum()
{
    return m_zoomScaleMinimum;
}

float SfmlGuiWindow::getZoomScaleMaximum()
{
    return m_zoomScaleMaximum;
}


bool SfmlGuiWindow::isZoomed()
{
    return m_zoomScale != m_zoomScaleDefault;
}

void SfmlGuiWindow::zoomIn()
{
    m_zoomScale -= m_zoomScaleStep;

    clampZoomScale(m_zoomScale);

    m_view.setSize(sf::Vector2f(m_viewInitialSize.x * m_zoomScale, m_viewInitialSize.y * m_zoomScale));
}

void SfmlGuiWindow::zoomOut()
{
    m_zoomScale += m_zoomScaleStep;

    clampZoomScale(m_zoomScale);

    m_view.setSize(sf::Vector2f(m_viewInitialSize.x * m_zoomScale, m_viewInitialSize.y * m_zoomScale));
}

void SfmlGuiWindow::zoomReset()
{
    m_zoomScale = m_zoomScaleDefault;

    m_view.setSize(m_viewInitialSize);
}

}
