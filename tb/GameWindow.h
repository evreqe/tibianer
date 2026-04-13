#pragma once

#include "common.h"

#include "tb/SFMLGUIWindow.h"

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

class GameWindow : public SFMLGUIWindow
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

    struct Properties
    {
        bool ShowTileHighlight = true;
    };

    Properties* getProperties();

    void handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled);
    void handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed);
    void handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased);

    sf::FloatRect getLayoutRect();

    void setPositionInLayout();

    void draw();
    void drawMapLayerAtAxisZ(tb::AxisZ axisZ);
    void drawTileHighlight();

    tb::TileRect getTileRect();

    void setLightBrightness(tb::LightBrightness lightBrightness);
    tb::LightBrightness getLightBrightness();

    std::uint32_t getNumTilesX();
    std::uint32_t getNumTilesY();

    std::uint32_t getNumTilesFromCenterX();
    std::uint32_t getNumTilesFromCenterY();

    std::uint32_t getNumTilesToDrawOffscreen();

private:

    Properties m_properties;

    const sf::Vector2f m_viewSize = sf::Vector2f(416.0f, 288.0f);
    const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(416, 288);

    sf::RenderTexture m_windowLayerRenderTexture;
    sf::Sprite m_windowLayerSprite;

    sf::RenderTexture m_lightLayerRenderTexture;
    sf::Sprite m_lightLayerSprite;
    sf::BlendMode m_lightBlendMode;
    tb::LightBrightness m_lightBrightness = tb::Constants::LightBrightnessMax;

    tb::Sprite m_tileHighlightSprite;

    sf::Clock m_animatedWaterClock;
    const sf::Time m_animatedWaterTime = sf::seconds(0.5f);

    sf::Clock m_animatedObjectsClock;
    const sf::Time m_animatedObjectsTime = sf::seconds(0.5f);

    const std::uint32_t m_numTilesX = 13; // number of tiles visible on the x-axis
    const std::uint32_t m_numTilesY = 9; // number of tiles visible on the y-axis

    const std::uint32_t m_numTilesFromCenterX = 6; // number of tiles visible to the west or east of the player on the x-axis
    const std::uint32_t m_numTilesFromCenterY = 4; // number of tiles visible to the north or south of the player on the y-axis

    const std::uint32_t m_numTilesToDrawOffscreen = 1; // need to draw some tiles that are not visible in order to account for large objects that take up 4 tiles

};

}

namespace
{
    inline tb::GameWindow& g_GameWindow = tb::GameWindow::getInstance();
}
