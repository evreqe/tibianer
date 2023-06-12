#pragma once

#include "common.h"

#include "tb/SfmlGuiWindow.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Sprite.h"

#include "tb/RenderWindow.h"
#include "tb/MiniMapWindow.h"
#include "tb/Map.h"
#include "tb/Game.h"

namespace tb
{

class GameWindow : public SfmlGuiWindow
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

    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);

    sf::FloatRect getLayoutRect();

    void setPositionInLayout();

    void draw();
    void drawMapLayerAtZ(tb::ZAxis_t z);
    void drawTileHighlight();

    sf::IntRect getTileRect();

    void setLightBrightness(tb::LightBrightness_t lightBrightness);
    tb::LightBrightness_t getLightBrightness();

    int getNumTilesX();
    int getNumTilesY();

    int getNumTilesFromCenterX();
    int getNumTilesFromCenterY();

    int getNumTilesToDrawOffscreen();

private:

    Properties_t m_properties;

    const sf::Vector2f m_viewSize = sf::Vector2f(416.0f, 288.0f);

    const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(416, 288);

    sf::RenderTexture m_windowLayerRenderTexture;
    sf::Sprite m_windowLayerSprite;

    sf::RenderTexture m_lightLayerRenderTexture;
    sf::Sprite m_lightLayerSprite;
    sf::BlendMode m_lightBlendMode;
    tb::LightBrightness_t m_lightBrightness = tb::LightBrightness::Max;

    tb::Sprite m_tileHighlightSprite;

    sf::Clock m_animatedWaterClock;
    const sf::Time m_animatedWaterTime = sf::seconds(0.5f);

    sf::Clock m_animatedObjectsClock;
    const sf::Time m_animatedObjectsTime = sf::seconds(0.5f);

    const int m_numTilesX = 13; // number of tiles visible on the x-axis
    const int m_numTilesY = 9; // number of tiles visible on the y-axis

    const int m_numTilesFromCenterX = 6; // number of tiles visible to the west or east of the player on the x-axis
    const int m_numTilesFromCenterY = 4; // number of tiles visible to the north or south of the player on the y-axis

    const int m_numTilesToDrawOffscreen = 1; // need to draw some tiles that are not visible in order to account for large objects that take up 4 tiles

};

}

namespace
{
    inline tb::GameWindow& g_GameWindow = tb::GameWindow::getInstance();
}
