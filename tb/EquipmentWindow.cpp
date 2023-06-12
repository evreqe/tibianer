#include "tb/EquipmentWindow.h"

namespace tb
{

EquipmentWindow::EquipmentWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    m_equipmentWindowSprite.setTexture(tb::Textures::GUI);
}

EquipmentWindow::~EquipmentWindow()
{
    //
}

void EquipmentWindow::handleMouseWheelMovedEvent(sf::Event event)
{
    // scroll up
    if (event.mouseWheel.delta > 0)
    {
        //
    }
    // scroll down
    else if (event.mouseWheel.delta < 0)
    {
        //
    }
}

void EquipmentWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void EquipmentWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void EquipmentWindow::setPositionInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    setPosition(sf::Vector2f(guiRightLayoutRect.left, guiRightLayoutRect.top));
}

void EquipmentWindow::predraw()
{
    m_equipmentWindowSprite.setTextureRect(tb::GuiRects::EquipmentWindow);
}

void EquipmentWindow::draw()
{
    if (m_predraw == false)
    {
        predraw();

        m_predraw = true;
    }

    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    sf::View* view = getView();

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    windowRenderTexture->clear(sf::Color::White);

    windowRenderTexture->draw(m_equipmentWindowSprite);

    windowRenderTexture->display();

    drawToRenderWindow();
}

tb::Sprite* EquipmentWindow::getNeckSlotSprite()
{
    return &m_neckSlotSprite;
}

tb::Sprite* EquipmentWindow::getHeadSlotSprite()
{
    return &m_neckSlotSprite;
}

tb::Sprite* EquipmentWindow::getBagSlotSprite()
{
    return &m_bagSlotSprite;
}

tb::Sprite* EquipmentWindow::getLeftHandSlotSprite()
{
    return &m_leftHandSlotSprite;
}

tb::Sprite* EquipmentWindow::getRightHandSlotSprite()
{
    return &m_rightHandSlotSprite;
}

tb::Sprite* EquipmentWindow::getLegsSlotSprite()
{
    return &m_legsSlotSprite;
}

tb::Sprite* EquipmentWindow::getChestSlotSprite()
{
    return &m_chestSlotSprite;
}

tb::Sprite* EquipmentWindow::getFeetSlotSprite()
{
    return &m_feetSlotSprite;
}

sf::FloatRect EquipmentWindow::getNeckSlotRect()
{
    return m_neckSlotRect;
}

sf::FloatRect EquipmentWindow::getHeadSlotRect()
{
    return m_neckSlotRect;
}

sf::FloatRect EquipmentWindow::getBagSlotRect()
{
    return m_bagSlotRect;
}

sf::FloatRect EquipmentWindow::getLeftHandSlotRect()
{
    return m_leftHandSlotRect;
}

sf::FloatRect EquipmentWindow::getRightHandSlotRect()
{
    return m_rightHandSlotRect;
}

sf::FloatRect EquipmentWindow::getLegsSlotRect()
{
    return m_legsSlotRect;
}

sf::FloatRect EquipmentWindow::getChestSlotRect()
{
    return m_chestSlotRect;
}

sf::FloatRect EquipmentWindow::getFeetSlotRect()
{
    return m_feetSlotRect;
}

}
