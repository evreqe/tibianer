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

        sf::Vector2f getMousePixelPosition();

        sf::Vector2f getMousePixelCoords();
        sf::Vector2i getMouseTileCoords();

        bool isMouseInsideWindow();

        void handleMouseWheelMovedEvent(sf::Event event);
        void handleMouseButtonPressedEvent(sf::Event event);
        void handleMouseButtonReleasedEvent(sf::Event event);

        void draw();
        void drawTileMap(const sf::IntRect& tileRect, tb::TileMap::Ptr tileMap);
        void drawTileHighlight();

        sf::View* getView();

        sf::Vector2f getViewPosition();
        void setViewPosition(sf::Vector2f position);

        sf::Vector2f getViewPositionOffset();
        void setViewPositionOffset(sf::Vector2f offset);

        void resetViewPositionOffset();

        float getZoomScale();
        float getZoomScaleMinimum();
        float getZoomScaleMaximum();
        bool isZoomed();

    private:

        sf::Vector2f m_position;

        sf::View m_view;
        sf::Vector2f m_viewPosition;
        sf::Vector2f m_viewPositionOffset;
        const sf::Vector2f m_viewSize = sf::Vector2f(416.0f, 416.0f);

        float m_zoomScale = 1.0f;
        const float m_zoomScaleMinimum = 1.0f;
        const float m_zoomScaleMaximum = 10.0f;
        const float m_zoomStep = 1.0f;

        const sf::Vector2i m_windowSize = sf::Vector2i(108, 108);

        sf::RenderTexture m_window;
        sf::Sprite m_windowSprite;

        sf::VertexArray m_vertexArray;

    };

}

namespace
{
    inline tb::MiniMapWindow& g_MiniMapWindow = tb::MiniMapWindow::getInstance();
}
