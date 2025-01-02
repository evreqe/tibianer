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

class EquipmentWindow : public SfmlGuiWindow
{

public:

    EquipmentWindow();
    ~EquipmentWindow();

    static EquipmentWindow& getInstance()
    {
        static EquipmentWindow instance;
        return instance;
    }

private:

    EquipmentWindow(const EquipmentWindow&) = delete;
    EquipmentWindow(EquipmentWindow&&) = delete;
    EquipmentWindow& operator=(const EquipmentWindow&) = delete;
    EquipmentWindow& operator=(EquipmentWindow&&) = delete;

public:

    void handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled);
    void handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed);
    void handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased);

    void setPositionInLayout();

    void predraw();
    void draw();

    tb::Sprite* getNeckSlotSprite();
    tb::Sprite* getHeadSlotSprite();
    tb::Sprite* getBagSlotSprite();
    tb::Sprite* getLeftHandSlotSprite();
    tb::Sprite* getRightHandSlotSprite();
    tb::Sprite* getLegsSlotSprite();
    tb::Sprite* getChestSlotSprite();
    tb::Sprite* getFeetSlotSprite();

    sf::FloatRect getNeckSlotRect();
    sf::FloatRect getHeadSlotRect();
    sf::FloatRect getBagSlotRect();
    sf::FloatRect getLeftHandSlotRect();
    sf::FloatRect getRightHandSlotRect();
    sf::FloatRect getLegsSlotRect();
    sf::FloatRect getChestSlotRect();
    sf::FloatRect getFeetSlotRect();

private:

    bool m_predraw = false;

    sf::Sprite m_equipmentWindowSprite;

    const sf::Vector2f m_slotSize = sf::Vector2f(24.0f, 24.0f);

    tb::Sprite m_neckSlotSprite;
    const sf::Vector2f m_neckSlotPosition = sf::Vector2f(3.0f, 3.0f);
    const sf::FloatRect m_neckSlotRect = sf::FloatRect
    (
        m_neckSlotPosition,
        m_slotSize
    );

    tb::Sprite m_headSlotSprite;
    const sf::Vector2f m_headSlotPosition = sf::Vector2f(42.0f, 3.0f);
    const sf::FloatRect m_headSlotRect = sf::FloatRect
    (
        m_headSlotPosition,
        m_slotSize
    );

    tb::Sprite m_bagSlotSprite;
    const sf::Vector2f m_bagSlotPosition = sf::Vector2f(81.0f, 3.0f);
    const sf::FloatRect m_bagSlotRect = sf::FloatRect
    (
        m_bagSlotPosition,
        m_slotSize
    );

    tb::Sprite m_leftHandSlotSprite;
    const sf::Vector2f m_leftHandSlotPosition = sf::Vector2f(3.0f, 42.0f);
    const sf::FloatRect m_leftHandSlotRect = sf::FloatRect
    (
        m_leftHandSlotPosition,
        m_slotSize
    );

    tb::Sprite m_rightHandSlotSprite;
    const sf::Vector2f m_rightHandSlotPosition = sf::Vector2f(81.0f, 42.0f);
    const sf::FloatRect m_rightHandSlotRect = sf::FloatRect
    (
        m_rightHandSlotPosition,
        m_slotSize
    );

    tb::Sprite m_legsSlotSprite;
    const sf::Vector2f m_legsSlotPosition = sf::Vector2f(3.0f, 81.0f);
    const sf::FloatRect m_legsSlotRect = sf::FloatRect
    (
        m_legsSlotPosition,
        m_slotSize
    );

    tb::Sprite m_chestSlotSprite;
    const sf::Vector2f m_chestSlotPosition = sf::Vector2f(42.0f, 81.0f);
    const sf::FloatRect m_chestSlotRect = sf::FloatRect
    (
        m_chestSlotPosition,
        m_slotSize
    );

    tb::Sprite m_feetSlotSprite;
    const sf::Vector2f m_feetSlotPosition = sf::Vector2f(81.0f, 81.0f);
    const sf::FloatRect m_feetSlotRect = sf::FloatRect
    (
        m_feetSlotPosition,
        m_slotSize
    );

    const sf::Vector2f m_viewSize = sf::Vector2f(tb::Constants::GuiRightLayoutWidthAsFloat, 108.0f);

    const sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(tb::Constants::GuiRightLayoutWidthAsInt, tb::Constants::GuiRightLayoutWidthAsInt);

};

}

namespace
{
    inline tb::EquipmentWindow& g_EquipmentWindow = tb::EquipmentWindow::getInstance();
}
