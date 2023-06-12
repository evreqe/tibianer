#pragma once

#include "common.h"

#include "tb/SfmlGuiWindow.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/GuiData.h"

#include "tb/Sprite.h"

#include "tb/RenderWindow.h"
#include "tb/MiniMapWindow.h"
#include "tb/Game.h"

namespace tb
{

class TabButtonsWindow : public SfmlGuiWindow
{

public:

    TabButtonsWindow();
    ~TabButtonsWindow();

    static TabButtonsWindow& getInstance()
    {
        static TabButtonsWindow instance;
        return instance;
    }

private:

    TabButtonsWindow(const TabButtonsWindow&) = delete;
    TabButtonsWindow(TabButtonsWindow&&) = delete;
    TabButtonsWindow& operator=(const TabButtonsWindow&) = delete;
    TabButtonsWindow& operator=(TabButtonsWindow&&) = delete;

public:

    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);

    void updateButtons();

    void setPositionInLayout();

    void predraw();
    void draw();

    sf::FloatRect getInventoryButtonRect();
    sf::FloatRect getStatusButtonRect();
    sf::FloatRect getBattleButtonRect();
    sf::FloatRect getMiniMapButtonRect();

private:

    bool m_predraw = false;

    const sf::Vector2f m_viewSize = sf::Vector2f(tb::Constants::GuiRightLayoutWidthAsFloat, 24.0f);

    const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(tb::Constants::GuiRightLayoutWidthAsInt, 24);

    const sf::Vector2f m_buttonSize = sf::Vector2f(24.0f, 24.0f);

    const float m_buttonPaddingX = 4.0f;

    sf::Sprite m_inventoryButtonSprite;
    const sf::Vector2f m_inventoryButtonPosition = sf::Vector2f(0.0f, 0.0f);
    sf::IntRect m_inventoryButtonTextureRect = tb::GuiRects::TabButtonsWindowInventoryButtonPressed;
    const sf::FloatRect m_inventoryButtonRect = sf::FloatRect
    (
        m_inventoryButtonPosition.x, m_inventoryButtonPosition.y,
        m_buttonSize.x, m_buttonSize.y
    );

    sf::Sprite m_statusButtonSprite;
    const sf::Vector2f m_statusButtonPosition = sf::Vector2f(28.0f, 0.0f);
    sf::IntRect m_statusButtonTextureRect = tb::GuiRects::TabButtonsWindowStatusButtonReleased;
    const sf::FloatRect m_statusButtonRect = sf::FloatRect
    (
        m_statusButtonPosition.x, m_statusButtonPosition.y,
        m_buttonSize.x, m_buttonSize.y
    );

    sf::Sprite m_battleButtonSprite;
    const sf::Vector2f m_battleButtonPosition = sf::Vector2f(56.0f, 0.0f);
    sf::IntRect m_battleButtonTextureRect = tb::GuiRects::TabButtonsWindowBattleButtonReleased;
    const sf::FloatRect m_battleButtonRect = sf::FloatRect
    (
        m_battleButtonPosition.x, m_battleButtonPosition.y,
        m_buttonSize.x, m_buttonSize.y
    );

    sf::Sprite m_miniMapButtonSprite;
    const sf::Vector2f m_miniMapButtonPosition = sf::Vector2f(84.0f, 0.0f);
    sf::IntRect m_miniMapButtonTextureRect = tb::GuiRects::TabButtonsWindowMiniMapButtonReleased;
    const sf::FloatRect m_miniMapButtonRect = sf::FloatRect
    (
        m_miniMapButtonPosition.x, m_miniMapButtonPosition.y,
        m_buttonSize.x, m_buttonSize.y
    );

};

}

namespace
{
    inline tb::TabButtonsWindow& g_TabButtonsWindow = tb::TabButtonsWindow::getInstance();
}
