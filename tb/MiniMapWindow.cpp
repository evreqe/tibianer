#include "tb/MiniMapWindow.h"

namespace tb
{

MiniMapWindow::MiniMapWindow()
{
    m_window.create(m_pixelWidth, m_pixelHeight);

    m_view.reset(sf::FloatRect(0.0f, 0.0f, m_pixelWidth, m_pixelHeight));
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

bool MiniMapWindow::isMouseInsideWindow()
{
    sf::Vector2f mousePosition = g_RenderWindow.getMousePosition2f();

    sf::FloatRect windowRect = MiniMapWindow::getRect();

    return windowRect.contains(mousePosition);
}

void MiniMapWindow::handleMouseWheelMovedEvent(sf::Event event)
{
    //
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
    //bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2f renderWindowSize = static_cast<sf::Vector2f>(renderWindow->getSize());

    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_window.getSize());

    float padding = tb::Constants::PaddingRenderWindow + tb::Constants::PaddingWoodBorder + tb::Constants::PaddingBlackRectangle;

    sf::Vector2f windowPosition;
    windowPosition.x = renderWindowSize.x - padding - windowSize.x;
    windowPosition.y = g_MenuBar.getHeight() + padding;

    setPosition(windowPosition);

/*
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
*/

    m_window.setView(m_view);

    m_window.clear(sf::Color::White);

    // TODO: draw it

    m_window.display();

    sf::Texture windowTexture = m_window.getTexture();

    m_windowSprite.setTexture(windowTexture);
    m_windowSprite.setPosition(m_position);

    renderWindow->draw(m_windowSprite);
}

sf::View* MiniMapWindow::getView()
{
    return &m_view;
}

}
