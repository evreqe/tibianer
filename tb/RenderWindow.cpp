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
    m_window.create(sf::VideoMode(m_widthDefault, m_heightDefault), tb::Constants::GameTitle, m_style);

    if (m_icon.loadFromFile(m_iconFileName) == true)
    {
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
    }
    else
    {
        g_Log.write("ERROR: Failed to load icon file: {}\n", m_iconFileName);
        return false;
    }

    unsigned int frameRateLimit = m_properties.FrameRateLimit;

    m_window.setFramerateLimit(frameRateLimit);

    g_Log.write("Frame Rate Limit: {}\n", frameRateLimit);

    bool verticalSync = m_properties.VerticalSync;

    m_window.setVerticalSyncEnabled(verticalSync);

    g_Log.write("Vertical Sync: {}\n", verticalSync);

    bool startMaximized = m_properties.StartMaximized;

    g_Log.write("Start Maximized: {}\n", startMaximized);

    if (startMaximized == true)
    {
        m_window.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
        m_window.setPosition(sf::Vector2i(0, 0));

        ::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE);
    }

    sf::Cursor arrowCursor;
    if (arrowCursor.loadFromSystem(sf::Cursor::Arrow) == false)
    {
        g_Log.write("ERROR: Failed to load arrow cursor\n");
        return false;
    }

    m_window.setMouseCursor(arrowCursor);
    m_window.setMouseCursorVisible(true);

    return true;
}

void RenderWindow::setSizeAndCenter(sf::Vector2u size)
{
    if (size.x < m_widthMinimum)
    {
        size.x = m_widthMinimum;
    }

    if (size.y < m_heightMinimum)
    {
        size.y = m_heightMinimum;
    }

    HWND renderWindow = m_window.getSystemHandle();

    HWND desktopWindow = ::GetDesktopWindow();

    RECT desktopRect;
    ::GetWindowRect(desktopWindow, &desktopRect);

    std::uint32_t desktopWidth  = desktopRect.right  - desktopRect.left;
    std::uint32_t desktopHeight = desktopRect.bottom - desktopRect.top;

    g_Log.write("desktop window size: {},{}\n", desktopWidth, desktopHeight);

    // new size is too big to fit inside the desktop
    if (size.x > desktopWidth || size.y > desktopHeight)
    {
        ::ShowWindow(renderWindow, SW_MAXIMIZE);
        return;
    }

    // check if window is minimized or maximized
    if (::IsIconic(renderWindow) == TRUE || ::IsZoomed(renderWindow) == TRUE)
    {
        // restore window
        ::ShowWindow(renderWindow, SW_NORMAL);
    }

    m_window.setSize(size);

    RECT renderWindowRect;
    ::GetWindowRect(renderWindow, &renderWindowRect);

    std::uint32_t renderWindowWidth  = renderWindowRect.right  - renderWindowRect.left;
    std::uint32_t renderWindowHeight = renderWindowRect.bottom - renderWindowRect.top;

    // center window
    m_window.setPosition
    (
        sf::Vector2i
        (
            (desktopWidth  / 2) - (renderWindowWidth  / 2),
            (desktopHeight / 2) - (renderWindowHeight / 2)
        )
    );

    // prevent window from going offscreen
    ::GetWindowRect(renderWindow, &renderWindowRect);

    if (renderWindowRect.left < 0 || renderWindowRect.top < 0)
    {
        // cut window size in half
        setSizeAndCenter(sf::Vector2u(desktopWidth / 2, desktopHeight / 2));

        // maximize window
        ::ShowWindow(renderWindow, SW_MAXIMIZE);
    }
}

void RenderWindow::handleClosedEvent(sf::Event event)
{
    m_window.close();
}

void RenderWindow::handleResizedEvent(sf::Event event)
{
    // stretch to fill window
    sf::FloatRect visibleArea
    (
        0.0f,
        0.0f,
        static_cast<float>(event.size.width),
        static_cast<float>(event.size.height)
    );

    m_window.setView(sf::View(visibleArea));
}

void RenderWindow::handleLostFocusEvent(sf::Event event)
{
    m_properties.IsFocused = false;
}

void RenderWindow::handleGainedFocusEvent(sf::Event event)
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
