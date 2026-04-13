#include "common.h"

#include "tb/SFMLGUIWindow.h"

namespace tb
{

SFMLGUIWindow::SFMLGUIWindow() :
    m_windowSprite(tb::Resources::Textures::Null)
{
    //
}

SFMLGUIWindow::~SFMLGUIWindow()
{
    //
}

void SFMLGUIWindow::initalize()
{
    bool resizeResult = m_windowRenderTexture.resize(static_cast<sf::Vector2u>(m_windowRenderTextureInitialSize));

    if (resizeResult == false)
    {
        g_Log.write("ERROR: failed to resize RenderTexture\n");
    }

    sf::View resetView(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), static_cast<sf::Vector2f>(m_viewInitialSize)));
    setView(resetView);
}

void SFMLGUIWindow::drawToRenderWindow()
{
    sf::Texture windowSpriteTexture = m_windowRenderTexture.getTexture();

    m_windowSprite.setTexture(windowSpriteTexture, true);
    m_windowSprite.setPosition(m_position);
    m_windowSprite.setScale(sf::Vector2f(m_sizeScale, m_sizeScale));

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    renderWindow->draw(m_windowSprite);
}

sf::FloatRect SFMLGUIWindow::getRect()
{
    sf::FloatRect windowRect;
    windowRect.position = getPosition();
    windowRect.size = getSize();

    return windowRect;
}

sf::Vector2f SFMLGUIWindow::getSize()
{
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_windowRenderTexture.getSize());

    windowSize.x *= m_sizeScale;
    windowSize.y *= m_sizeScale;

    return windowSize;
}

sf::Vector2f SFMLGUIWindow::getMousePixelPosition()
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

tb::PixelCoords SFMLGUIWindow::getMousePixelCoords()
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

tb::TileCoords SFMLGUIWindow::getMouseTileCoords()
{
    tb::PixelCoords pixelCoords = getMousePixelCoords();

    tb::TileCoords tileCoords = static_cast<tb::TileCoords>(pixelCoords);

    tileCoords.x /= tb::Constants::TileSize;
    tileCoords.y /= tb::Constants::TileSize;

    return tileCoords;
}

bool SFMLGUIWindow::isMouseInsideWindow()
{
    sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

    sf::FloatRect windowRect = getRect();

    return windowRect.contains(mousePosition);
}

sf::Vector2f SFMLGUIWindow::getPosition()
{
    return m_position;
}

void SFMLGUIWindow::setPosition(const sf::Vector2f& position)
{
    m_position = position;
}

sf::View* SFMLGUIWindow::getView()
{
    return &m_view;
}

void SFMLGUIWindow::setView(sf::View view)
{
    m_view = view;
}

sf::Vector2f SFMLGUIWindow::getViewInitialSize()
{
    return m_viewInitialSize;
}

void SFMLGUIWindow::setViewInitialSize(sf::Vector2f size)
{
    m_viewInitialSize = size;
}

sf::Vector2f SFMLGUIWindow::getViewPosition()
{
    return m_view.getCenter();
}

void SFMLGUIWindow::setViewPosition(sf::Vector2f position)
{
    m_view.setCenter(position);
}

sf::Vector2f SFMLGUIWindow::getViewPositionOffset()
{
    return m_viewPositionOffset;
}

void SFMLGUIWindow::setViewPositionOffset(sf::Vector2f offset)
{
    m_viewPositionOffset = offset;
}

void SFMLGUIWindow::resetViewPositionOffset()
{
    m_viewPositionOffset.x = 0.0f;
    m_viewPositionOffset.y = 0.0f;
}

sf::RenderTexture* SFMLGUIWindow::getWindowRenderTexture()
{
    return &m_windowRenderTexture;
}

sf::Vector2i SFMLGUIWindow::getWindowRenderTextureInitialSize()
{
    return m_windowRenderTextureInitialSize;
}

void SFMLGUIWindow::setWindowRenderTextureInitialSize(sf::Vector2i size)
{
    m_windowRenderTextureInitialSize = size;
}

sf::Sprite* SFMLGUIWindow::getWindowSprite()
{
    return &m_windowSprite;
}

sf::FloatRect SFMLGUIWindow::getRectOfSprite(const sf::Sprite& sprite)
{
    sf::FloatRect spriteRect;
    spriteRect.position = sprite.getPosition();
    spriteRect.size = sprite.getLocalBounds().size;

    return spriteRect;
}

float SFMLGUIWindow::getSizeScale()
{
    return m_sizeScale;
}

void SFMLGUIWindow::setSizeScale(float scale)
{
    clampSizeScale(scale);

    m_sizeScale = scale;
}

void SFMLGUIWindow::clampSizeScale(float& scale)
{
    scale = std::clamp(scale, m_sizeScaleMinimum, m_sizeScaleMaximum);
}

float SFMLGUIWindow::getSizeScaleStep()
{
    return m_sizeScaleStep;
}

float SFMLGUIWindow::getSizeScaleMinimum()
{
    return m_sizeScaleMinimum;
}

float SFMLGUIWindow::getSizeScaleMaximum()
{
    return m_sizeScaleMaximum;
}

bool SFMLGUIWindow::isSized()
{
    return m_sizeScale != m_sizeScaleDefault;
}

void SFMLGUIWindow::sizeReset()
{
    m_sizeScale = m_sizeScaleDefault;
}

float SFMLGUIWindow::getZoomScale()
{
    return m_zoomScale;
}

void SFMLGUIWindow::setZoomScale(float scale)
{
    clampZoomScale(scale);

    m_sizeScale = scale;
}

void SFMLGUIWindow::clampZoomScale(float& scale)
{
    scale = std::clamp(scale, m_zoomScaleMinimum, m_zoomScaleMaximum);
}

float SFMLGUIWindow::getZoomScaleStep()
{
    return m_zoomScaleStep;
}

float SFMLGUIWindow::getZoomScaleMinimum()
{
    return m_zoomScaleMinimum;
}

float SFMLGUIWindow::getZoomScaleMaximum()
{
    return m_zoomScaleMaximum;
}


bool SFMLGUIWindow::isZoomed()
{
    return m_zoomScale != m_zoomScaleDefault;
}

void SFMLGUIWindow::zoomIn()
{
    m_zoomScale -= m_zoomScaleStep;

    clampZoomScale(m_zoomScale);

    m_view.setSize(sf::Vector2f(m_viewInitialSize.x * m_zoomScale, m_viewInitialSize.y * m_zoomScale));
}

void SFMLGUIWindow::zoomOut()
{
    m_zoomScale += m_zoomScaleStep;

    clampZoomScale(m_zoomScale);

    m_view.setSize(sf::Vector2f(m_viewInitialSize.x * m_zoomScale, m_viewInitialSize.y * m_zoomScale));
}

void SFMLGUIWindow::zoomReset()
{
    m_zoomScale = m_zoomScaleDefault;

    m_view.setSize(m_viewInitialSize);
}

}
