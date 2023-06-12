#include "tb/TabButtonsWindow.h"

namespace tb
{

TabButtonsWindow::TabButtonsWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    m_inventoryButtonSprite.setTexture(tb::Textures::GUI);
    m_statusButtonSprite.setTexture(tb::Textures::GUI);
    m_battleButtonSprite.setTexture(tb::Textures::GUI);
    m_miniMapButtonSprite.setTexture(tb::Textures::GUI);

    m_inventoryButtonSprite.setPosition(m_inventoryButtonPosition);
    m_statusButtonSprite.setPosition(m_statusButtonPosition);
    m_battleButtonSprite.setPosition(m_battleButtonPosition);
    m_miniMapButtonSprite.setPosition(m_miniMapButtonPosition);
}

TabButtonsWindow::~TabButtonsWindow()
{
    //
}

void TabButtonsWindow::handleMouseWheelMovedEvent(sf::Event event)
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

void TabButtonsWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    sf::Vector2f mousePosition = getMousePixelPosition();

    if (event.mouseButton.button == sf::Mouse::Left)
    {
        tb::Game::GuiProperties_t* gameGuiProperties = g_Game.getGuiProperties();

        sf::FloatRect inventoryButtonRect = getInventoryButtonRect();
        sf::FloatRect statusButtonRect = getStatusButtonRect();
        sf::FloatRect battleButtonRect = getBattleButtonRect();
        sf::FloatRect miniMapButtonRect = getMiniMapButtonRect();

        if (inventoryButtonRect.contains(mousePosition))
        {
            gameGuiProperties->TabButtonsWindowInventoryButtonIsPressed = true;
            gameGuiProperties->TabButtonsWindowStatusButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowBattleButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowMiniMapButtonIsPressed = false;

            //gameGuiProperties->ShowEquipmentWindow = x;
            //gameGuiProperties->ShowStatusWindow = x;
            //gameGuiProperties->ShowMiniMapWindow = x;

            gameGuiProperties->ShowInventoryWindow = true;
            gameGuiProperties->ShowSkillsWindow = false;
            gameGuiProperties->ShowBattleWindow = false;

            m_inventoryButtonSprite.setTextureRect(tb::GuiRects::TabButtonsWindowInventoryButtonPressed);
        }

        if (statusButtonRect.contains(mousePosition))
        {
            gameGuiProperties->TabButtonsWindowInventoryButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowStatusButtonIsPressed = true;
            gameGuiProperties->TabButtonsWindowBattleButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowMiniMapButtonIsPressed = false;

            gameGuiProperties->ShowEquipmentWindow = false;
            gameGuiProperties->ShowStatusWindow = true;
            gameGuiProperties->ShowMiniMapWindow = false;

            gameGuiProperties->ShowInventoryWindow = false;
            gameGuiProperties->ShowSkillsWindow = true;
            gameGuiProperties->ShowBattleWindow = false;

            m_statusButtonSprite.setTextureRect(tb::GuiRects::TabButtonsWindowStatusButtonPressed);
        }

        if (battleButtonRect.contains(mousePosition))
        {
            gameGuiProperties->TabButtonsWindowInventoryButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowStatusButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowBattleButtonIsPressed = true;
            gameGuiProperties->TabButtonsWindowMiniMapButtonIsPressed = false;

            gameGuiProperties->ShowEquipmentWindow = true;
            gameGuiProperties->ShowStatusWindow = false;
            gameGuiProperties->ShowMiniMapWindow = false;

            gameGuiProperties->ShowInventoryWindow = false;
            gameGuiProperties->ShowSkillsWindow = false;
            gameGuiProperties->ShowBattleWindow = true;

            m_battleButtonSprite.setTextureRect(tb::GuiRects::TabButtonsWindowBattleButtonPressed);
        }

        if (miniMapButtonRect.contains(mousePosition))
        {
            gameGuiProperties->TabButtonsWindowInventoryButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowStatusButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowBattleButtonIsPressed = false;
            gameGuiProperties->TabButtonsWindowMiniMapButtonIsPressed = true;

            gameGuiProperties->ShowEquipmentWindow = false;
            gameGuiProperties->ShowStatusWindow = false;
            gameGuiProperties->ShowMiniMapWindow = true;

            //gameGuiProperties->ShowInventoryWindow = x;
            //gameGuiProperties->ShowSkillsWindow = x;
            //gameGuiProperties->ShowBattleWindow = x;

            m_miniMapButtonSprite.setTextureRect(tb::GuiRects::TabButtonsWindowMiniMapButtonPressed);
        }

        updateButtons();
    }
}

void TabButtonsWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void TabButtonsWindow::updateButtons()
{
    tb::Game::GuiProperties_t* guiProperties = g_Game.getGuiProperties();

    // inventory
    if (guiProperties->TabButtonsWindowInventoryButtonIsPressed == true)
    {
        m_inventoryButtonTextureRect = tb::GuiRects::TabButtonsWindowInventoryButtonPressed;
    }
    else
    {
        m_inventoryButtonTextureRect = tb::GuiRects::TabButtonsWindowInventoryButtonReleased;
    }

    m_inventoryButtonSprite.setTextureRect(m_inventoryButtonTextureRect);

    // status
    if (guiProperties->TabButtonsWindowStatusButtonIsPressed == true)
    {
        m_statusButtonTextureRect = tb::GuiRects::TabButtonsWindowStatusButtonPressed;
    }
    else
    {
        m_statusButtonTextureRect = tb::GuiRects::TabButtonsWindowStatusButtonReleased;
    }

    m_statusButtonSprite.setTextureRect(m_statusButtonTextureRect);

    // battle
    if (guiProperties->TabButtonsWindowBattleButtonIsPressed == true)
    {
        m_battleButtonTextureRect = tb::GuiRects::TabButtonsWindowBattleButtonPressed;
    }
    else
    {
        m_battleButtonTextureRect = tb::GuiRects::TabButtonsWindowBattleButtonReleased;
    }

    m_battleButtonSprite.setTextureRect(m_battleButtonTextureRect);


    // minimap
    if (guiProperties->TabButtonsWindowMiniMapButtonIsPressed == true)
    {
        m_miniMapButtonTextureRect = tb::GuiRects::TabButtonsWindowMiniMapButtonPressed;
    }
    else
    {
        m_miniMapButtonTextureRect = tb::GuiRects::TabButtonsWindowMiniMapButtonReleased;
    }

    m_miniMapButtonSprite.setTextureRect(m_miniMapButtonTextureRect);
}

void TabButtonsWindow::setPositionInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    sf::FloatRect miniMapWindowRect = g_MiniMapWindow.getRect();

    float padding = tb::Constants::PaddingRenderWindow;

    sf::Vector2f windowPosition;
    windowPosition.x = guiRightLayoutRect.left;
    windowPosition.y = miniMapWindowRect.top + miniMapWindowRect.height + padding;

    setPosition(windowPosition);
}

void TabButtonsWindow::predraw()
{
    updateButtons();
}

void TabButtonsWindow::draw()
{
    if (m_predraw == false)
    {
        predraw();

        m_predraw = true;
    }

    sf::View* view = getView();

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    windowRenderTexture->clear(sf::Color::Transparent);

    windowRenderTexture->draw(m_inventoryButtonSprite);
    windowRenderTexture->draw(m_statusButtonSprite);
    windowRenderTexture->draw(m_battleButtonSprite);
    windowRenderTexture->draw(m_miniMapButtonSprite);

    windowRenderTexture->display();

    drawToRenderWindow();
}

sf::FloatRect TabButtonsWindow::getInventoryButtonRect()
{
    return m_inventoryButtonRect;
}

sf::FloatRect TabButtonsWindow::getStatusButtonRect()
{
    return m_statusButtonRect;
}

sf::FloatRect TabButtonsWindow::getBattleButtonRect()
{
    return m_battleButtonRect;
}

sf::FloatRect TabButtonsWindow::getMiniMapButtonRect()
{
    return m_miniMapButtonRect;
}

}
