#include "common.h"

#include "tb/RenderWindow.h"

namespace tb
{

RenderWindow::RenderWindow()
{
    //
}

RenderWindow::~RenderWindow()
{
    //
}

RenderWindow::Properties_t* RenderWindow::getProperties()
{
    return &m_properties;
}

bool RenderWindow::create()
{
    m_window.create(sf::VideoMode(sf::Vector2u(m_widthDefault, m_heightDefault)), tb::Constants::GameTitle, m_style, m_state);

    if (m_icon.loadFromFile(m_iconFileName) == true)
    {
        m_window.setIcon(m_icon);
    }
    else
    {
        g_Log.write("ERROR: Failed to load icon file: {}\n", m_iconFileName);
        return false;
    }

    std::uint32_t frameRateLimit = m_properties.FrameRateLimit;

    m_window.setFramerateLimit(frameRateLimit);

    g_Log.write("Frame Rate Limit: {}\n", frameRateLimit);

    bool verticalSync = m_properties.VerticalSync;

    m_window.setVerticalSyncEnabled(verticalSync);

    g_Log.write("Vertical Sync: {}\n", verticalSync);

    bool startMaximized = m_properties.StartMaximized;

    g_Log.write("Start Maximized: {}\n", startMaximized);

    if (startMaximized == true)
    {
        m_window.setSize(sf::VideoMode::getDesktopMode().size);
        m_window.setPosition(sf::Vector2i(0, 0));

        tb::WindowsApi::MaximizeWindow(m_window.getNativeHandle());
    }

    const std::optional<sf::Cursor> arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow);
    if (arrowCursor.has_value() == false)
    {
        g_Log.write("ERROR: Failed to create arrow cursor\n");
        return false;
    }

    m_window.setMouseCursor(arrowCursor.value());
    m_window.setMouseCursorVisible(true);

    return true;
}

void RenderWindow::setSizeAndCenter(sf::Vector2u size)
{
    sf::WindowHandle renderWindowHandle = m_window.getNativeHandle();

    // normalize render window
    tb::WindowsApi::NormalizeWindow(renderWindowHandle);

    sf::Vector2u desktopWindowSize = sf::VideoMode::getDesktopMode().size;

    g_Log.write("desktop window size: {},{}\n", desktopWindowSize.x, desktopWindowSize.y);

    // size is too small, set to minimum width and height
    if (size.x < m_widthMinimum)
    {
        size.x = m_widthMinimum;
    }

    if (size.y < m_heightMinimum)
    {
        size.y = m_heightMinimum;
    }

    // size is too big to fit inside the desktop window, set to desktop window size
    if (size.x > desktopWindowSize.x)
    {
        size.x = desktopWindowSize.x;
    }

    if (size.y > desktopWindowSize.y)
    {
        size.y = desktopWindowSize.y;
    }

    g_Log.write("size: {},{}\n", size.x, size.y);

    m_window.setSize(size);

    // size is the same as or greather than the desktop window size, maximize render window
    if (size.x >= desktopWindowSize.x || size.y >= desktopWindowSize.y)
    {
        // maximize render window
        tb::WindowsApi::MaximizeWindow(renderWindowHandle);
        return;
    }

    sf::Vector2u renderWindowSize = m_window.getSize();

    g_Log.write("render window size: {},{}\n", renderWindowSize.x, renderWindowSize.y);

    if (desktopWindowSize.x != 0 && desktopWindowSize.y != 0 && renderWindowSize.x != 0 && renderWindowSize.y != 0)
    {
        sf::Vector2i centerPosition =
        {
            static_cast<int>((desktopWindowSize.x / 2) - (renderWindowSize.x / 2)),
            static_cast<int>((desktopWindowSize.y / 2) - (renderWindowSize.y / 2))
        };

        g_Log.write("center position: {},{}\n", centerPosition.x, centerPosition.y);

        // center render window
        if (centerPosition.x != 0 && centerPosition.y != 0)
        {
            m_window.setPosition(centerPosition);
        }
    }
}

void RenderWindow::handleEventClosed()
{
    m_window.close();
}

void RenderWindow::handleEventResized(const sf::Event::Resized* eventResized)
{
    // stretch to fill window
    sf::FloatRect visibleArea
    (
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f
        (
            static_cast<float>(eventResized->size.x),
            static_cast<float>(eventResized->size.y)
        )
    );

    m_window.setView(sf::View(visibleArea));
}

void RenderWindow::handleEventFocusLost()
{
    m_properties.IsFocused = false;
}

void RenderWindow::handleEventFocusGained()
{
    m_properties.IsFocused = true;
}

sf::Vector2f RenderWindow::getMousePosition2f()
{
    sf::Vector2i mousePosition2i = sf::Mouse::getPosition(m_window);

    sf::Vector2f mousePosition2f = m_window.mapPixelToCoords(mousePosition2i);

    return mousePosition2f;
}

sf::Vector2i RenderWindow::getMousePosition2i()
{
    sf::Vector2f mousePosition2f = getMousePosition2f();

    sf::Vector2i mousePosition2i = static_cast<sf::Vector2i>(mousePosition2f);

    return mousePosition2i;
}

sf::RenderWindow* RenderWindow::getWindow()
{
    return &m_window;
}

sf::Vector2u RenderWindow::getDefaultSize()
{
    return {m_widthDefault, m_heightDefault};
}

}
