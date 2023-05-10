#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Sprite.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/RenderWindow.h"
#include "tb/GameWindow.h"
#include "tb/Map.h"
#include "tb/Game.h"

namespace tb
{

    class MiniMapWindow
    {

    public:

        MiniMapWindow();
        ~MiniMapWindow();

        static MiniMapWindow& getInstance()
        {
            static MiniMapWindow instance;
            return instance;
        }

    private:

        MiniMapWindow(const MiniMapWindow&) = delete;
        MiniMapWindow(MiniMapWindow&&) = delete;
        MiniMapWindow& operator=(const MiniMapWindow&) = delete;
        MiniMapWindow& operator=(MiniMapWindow&&) = delete;

    public:

        sf::Vector2f getPosition();
        void setPosition(const sf::Vector2f& position);

        sf::FloatRect getRect();
        void drawDebugRect();

        void drawWoodBorder();

        //sf::Vector2f getMousePixelCoords();
        //sf::Vector2i getMouseTileCoords();

        bool isMouseInsideWindow();

        void handleMouseWheelMovedEvent(sf::Event event);
        void handleMouseButtonPressedEvent(sf::Event event);
        void handleMouseButtonReleasedEvent(sf::Event event);

        void draw();

        sf::View* getView();

    private:

        sf::Vector2f m_position;

        sf::View m_view;

        sf::RenderTexture m_window;
        sf::Sprite m_windowSprite;

        const float m_pixelWidth = 108.0f; // size of the window
        const float m_pixelHeight = 108.0f; // size of the window

    };

}

namespace
{
    inline tb::MiniMapWindow& g_MiniMapWindow = tb::MiniMapWindow::getInstance();
}
