#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Sprite.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/RenderWindow.h"
#include "tb/Map.h"
#include "tb/Game.h"

namespace tb
{

class GameWindow
{

public:

    GameWindow();
    ~GameWindow();

    static GameWindow& getInstance()
    {
        static GameWindow instance;
        return instance;
    }

private:

    GameWindow(const GameWindow&) = delete;
    GameWindow(GameWindow&&) = delete;
    GameWindow& operator=(const GameWindow&) = delete;
    GameWindow& operator=(GameWindow&&) = delete;

public:

    struct Properties_t
    {
        bool ShowTileHighlight = true;
    };

    Properties_t* getProperties();

    sf::Vector2f getPosition();
    void setPosition(const sf::Vector2f& position);

    sf::FloatRect getRect();
    void drawRect();

    sf::Vector2f getMousePixelCoords();
    sf::Vector2i getMouseTileCoords();

    bool isMouseInsideWindow();

    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);

    void drawTileHighlight();

    void drawLayer(tb::ZAxis_t z);
    void draw();

    sf::IntRect getTileRect();

    sf::Vector2f getViewPosition();
    void setViewPosition(sf::Vector2f position);

    sf::Vector2f getViewPositionOffset();
    void setViewPositionOffset(sf::Vector2f offset);

    void resetViewPositionOffset();

private:

    Properties_t m_properties;

    sf::Vector2f m_position;

    sf::View m_view;
    sf::Vector2f m_viewPosition;
    sf::Vector2f m_viewPositionOffset;

    sf::RenderTexture m_window;
    sf::Sprite m_windowSprite;

    sf::RenderTexture m_windowLayer;
    sf::Sprite m_windowLayerSprite;

    sf::RenderTexture m_lightLayer;
    sf::Sprite m_lightLayerSprite;
    sf::BlendMode m_lightBlendMode;

    float m_zoomScale = 1.0f;
    float m_zoomScaleMinimum = 1.0f;
    float m_zoomFactor = 0.2f;

    float m_scale = 2.0f;

    tb::Sprite m_tileHighlightSprite;
    const std::string m_tileHightlightSpriteName = "TileHighlight";

    const int m_tileWidth = 13; // number of tiles visible on the x-axis
    const int m_tileHeight = 9; // number of tiles visible on the y-axis

    const int m_numTilesFromCenterX = 6; // number of tiles visible to the west or east of the player on the x-axis
    const int m_numTilesFromCenterY = 4; // number of tiles visible to the north or south of the player on the y-axis

    const int m_numTilesToDrawFromOffscreen = 1; // need to draw some tiles that are not visible in order to account for large objects that take up 4 tiles

    const float m_pixelWidth = 416.0f; // number of pixels visible on the x-axis
    const float m_pixelHeight = 288.0f; // number of pixels visible on the y-axis

};

}

namespace
{
    inline tb::GameWindow& g_GameWindow = tb::GameWindow::getInstance();
}
