#pragma once

#include "common.h"

#include "tb/SfmlGuiWindow.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Sprite.h"

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

    void handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled);
    void handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed);
    void handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased);

    void setPositionInLayout();

    void draw();
    void drawTileMap(const sf::IntRect& tileRect, tb::TileMap::Ptr tileMap);
    void drawTileHighlight();

    std::vector<sf::Vertex> getCrosshairVertexList();

private:

    const std::size_t m_numCrosshairTiles = 5;

    const sf::Vector2f m_viewSize = sf::Vector2f(416.0f, 416.0f);

    const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(tb::Constants::GuiRightLayoutWidthAsInt, tb::Constants::GuiRightLayoutWidthAsInt);

    std::vector<sf::Vertex> m_vertexList;

    static const std::uint32_t m_numVertexPerTile = 6;

};

}

namespace
{
    inline tb::MiniMapWindow& g_MiniMapWindow = tb::MiniMapWindow::getInstance();
}
