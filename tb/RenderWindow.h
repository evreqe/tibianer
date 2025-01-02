#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include <windows.h>

namespace tb
{

class RenderWindow
{

public:

    RenderWindow();
    ~RenderWindow();

    static RenderWindow& getInstance()
    {
        static RenderWindow instance;
        return instance;
    }

private:

    RenderWindow(const RenderWindow&) = delete;
    RenderWindow(RenderWindow&&) = delete;
    RenderWindow& operator=(const RenderWindow&) = delete;
    RenderWindow& operator=(RenderWindow&&) = delete;

public:

    struct Properties_t
    {
        std::uint32_t FrameRateLimit = 60;

        bool VerticalSync = true;
        bool StartMaximized = true;

        bool IsFocused = true;
    };

    Properties_t* getProperties();

    bool create();

    void setSizeAndCenter(sf::Vector2u size);

    void handleEventClosed();
    void handleEventResized(const sf::Event::Resized* eventResized);
    void handleEventFocusLost();
    void handleEventFocusGained();

    sf::Vector2f getMousePosition2f();
    sf::Vector2i getMousePosition2i();

    sf::RenderWindow* getWindow();

    sf::Vector2u getDefaultSize();

private:

    Properties_t m_properties;

    sf::RenderWindow m_window;

    std::uint32_t m_widthDefault = 1280;
    std::uint32_t m_heightDefault = 720;

    std::uint32_t m_widthMinimum = 640;
    std::uint32_t m_heightMinimum = 480;

    std::uint32_t m_style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
    sf::State m_state = sf::State::Windowed;

    sf::Image m_icon;

    const std::filesystem::path m_iconFileName = "icons/tb.png";

};

}

namespace
{
    inline tb::RenderWindow& g_RenderWindow = tb::RenderWindow::getInstance();
}
