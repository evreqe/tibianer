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
        unsigned int FrameRateLimit = 60;

        bool VerticalSync = false;
        bool StartMaximized = true;
    };

    Properties_t* getProperties();

    bool create();

    void setSizeAndCenter(sf::Vector2u size);

    void handleClosedEvent(sf::Event event);
    void handleResizedEvent(sf::Event event);

    sf::Vector2f getMousePosition();

    sf::RenderWindow* getWindow();

private:

    Properties_t m_properties;

    sf::RenderWindow m_window;

    unsigned int m_width = 1280;
    unsigned int m_height = 720;

    sf::Uint32 m_style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;

    sf::Image m_icon;

    const std::string m_iconFileName = "images/icon.png";

};

}

namespace
{
    inline tb::RenderWindow& g_RenderWindow = tb::RenderWindow::getInstance();
}
