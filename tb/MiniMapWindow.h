#pragma once

#include "common.h"

#include "tb/SfmlGuiWindow.h"

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

    class MiniMapWindow : public SfmlGuiWindow
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

        void handleMouseWheelMovedEvent(sf::Event event);
        void handleMouseButtonPressedEvent(sf::Event event);
        void handleMouseButtonReleasedEvent(sf::Event event);

        void draw();
        void drawTileMap(const sf::IntRect& tileRect, tb::TileMap::Ptr tileMap);
        void drawTileHighlight();

    private:

        const sf::Vector2f m_viewSize = sf::Vector2f(416.0f, 416.0f);

        const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(108, 108);

        sf::VertexArray m_vertexArray;

    };

}

namespace
{
    inline tb::MiniMapWindow& g_MiniMapWindow = tb::MiniMapWindow::getInstance();
}
