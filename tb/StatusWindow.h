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

class StatusWindow : public SfmlGuiWindow
{

public:

    StatusWindow();
    ~StatusWindow();

    static StatusWindow& getInstance()
    {
        static StatusWindow instance;
        return instance;
    }

private:

    StatusWindow(const StatusWindow&) = delete;
    StatusWindow(StatusWindow&&) = delete;
    StatusWindow& operator=(const StatusWindow&) = delete;
    StatusWindow& operator=(StatusWindow&&) = delete;

public:

    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);

    void setPositionInLayout();

    void predraw();
    void draw();

    sf::FloatRect getHitPointsSlotRect();
    sf::FloatRect getCapSlotRect();
    sf::FloatRect getExperiencePointsSlotRect();
    sf::FloatRect getManaPointsSlotRect();
    sf::FloatRect getLevelSlotRect();
    sf::FloatRect getMagicLevelSlotRect();

private:

    bool m_predraw = false;

    sf::Sprite m_statusWindowSprite;

    const sf::Vector2f m_slotSize = sf::Vector2f(32.0f, 32.0f);

    const sf::Vector2f m_hitPointsSlotPosition = sf::Vector2f(20.0f, 2.0f);
    const sf::FloatRect m_hitPointsSlotRect = sf::FloatRect
    (
        m_hitPointsSlotPosition.x, m_hitPointsSlotPosition.y,
        m_slotSize.x, m_slotSize.y
    );

    const sf::Vector2f m_capSlotPosition = sf::Vector2f(56.0f, 2.0f);
    const sf::FloatRect m_capSlotRect = sf::FloatRect
    (
        m_capSlotPosition.x, m_capSlotPosition.y,
        m_slotSize.x, m_slotSize.y
    );

    const sf::Vector2f m_experiencePointsSlotPosition = sf::Vector2f(2.0f, 37.0f);
    const sf::FloatRect m_experiencePointsSlotRect = sf::FloatRect
    (
        m_experiencePointsSlotPosition.x, m_experiencePointsSlotPosition.y,
        m_slotSize.x, m_slotSize.y
    );

    const sf::Vector2f m_manaPointsSlotPosition = sf::Vector2f(74.0f, 37.0f);
    const sf::FloatRect m_manaPointsSlotRect = sf::FloatRect
    (
        m_manaPointsSlotPosition.x, m_manaPointsSlotPosition.y,
        m_slotSize.x, m_slotSize.y
    );

    const sf::Vector2f m_levelSlotPosition = sf::Vector2f(20.0f, 72.0f);
    const sf::FloatRect m_levelSlotRect = sf::FloatRect
    (
        m_levelSlotPosition.x, m_levelSlotPosition.y,
        m_slotSize.x, m_slotSize.y
    );

    const sf::Vector2f m_magicLevelSlotPosition = sf::Vector2f(56.0f, 72.0f);
    const sf::FloatRect m_magicLevelSlotRect = sf::FloatRect
    (
        m_magicLevelSlotPosition.x, m_magicLevelSlotPosition.y,
        m_slotSize.x, m_slotSize.y
    );

    const sf::Vector2f m_viewSize = sf::Vector2f(tb::Constants::GuiRightLayoutWidthAsFloat, 108.0f);

    const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(tb::Constants::GuiRightLayoutWidthAsInt, tb::Constants::GuiRightLayoutWidthAsInt);

};

}

namespace
{
    inline tb::StatusWindow& g_StatusWindow = tb::StatusWindow::getInstance();
}
