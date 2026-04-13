#include "common.h"

#include "tb/TabButtonsWindow.h"

namespace tb
{

TabButtonsWindow::TabButtonsWindow() :
    m_inventoryButtonSprite(tb::Resources::Textures::GUI),
    m_statusButtonSprite(tb::Resources::Textures::GUI),
    m_battleButtonSprite(tb::Resources::Textures::GUI),
    m_miniMapButtonSprite(tb::Resources::Textures::GUI)
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    //m_inventoryButtonSprite.setTexture(tb::Textures::GUI);
    //m_statusButtonSprite.setTexture(tb::Textures::GUI);
    //m_battleButtonSprite.setTexture(tb::Textures::GUI);
    //m_miniMapButtonSprite.setTexture(tb::Textures::GUI);

    m_inventoryButtonSprite.setPosition(m_inventoryButtonPosition);
    m_statusButtonSprite.setPosition(m_statusButtonPosition);
    m_battleButtonSprite.setPosition(m_battleButtonPosition);
    m_miniMapButtonSprite.setPosition(m_miniMapButtonPosition);
}

TabButtonsWindow::~TabButtonsWindow()
{
    //
}

void TabButtonsWindow::handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled)
{
    // scrolled up
    if (eventMouseWheelScrolled->delta > 0)
    {
        //
    }
    // scrolled down
    else if (eventMouseWheelScrolled->delta < 0)
    {
        //
    }
}

void TabButtonsWindow::handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed)
{
    sf::Vector2f mousePosition = getMousePixelPosition();

    tb::GUI::Properties* GUIProperties = g_GUI.getProperties();

    if (eventMouseButtonPressed->button == sf::Mouse::Button::Left)
    {
        sf::FloatRect inventoryButtonRect = getInventoryButtonRect();
        sf::FloatRect statusButtonRect = getStatusButtonRect();
        sf::FloatRect battleButtonRect = getBattleButtonRect();
        sf::FloatRect miniMapButtonRect = getMiniMapButtonRect();

        if (inventoryButtonRect.contains(mousePosition) == true)
        {
            GUIProperties->TabButtonsWindowInventoryButtonIsPressed = true;
            GUIProperties->TabButtonsWindowStatusButtonIsPressed = false;
            GUIProperties->TabButtonsWindowBattleButtonIsPressed = false;
            GUIProperties->TabButtonsWindowMiniMapButtonIsPressed = false;

            //GUIProperties->ShowEquipmentWindow = x;
            //GUIProperties->ShowStatusWindow = x;
            //GUIProperties->ShowMiniMapWindow = x;

            GUIProperties->ShowInventoryWindow = true;
            GUIProperties->ShowSkillsWindow = false;
            GUIProperties->ShowBattleWindow = false;

            m_inventoryButtonSprite.setTextureRect(tb::Resources::TextureRects::GUI::TabButtonsWindowInventoryButtonPressed);
        }

        if (statusButtonRect.contains(mousePosition) == true)
        {
            GUIProperties->TabButtonsWindowInventoryButtonIsPressed = false;
            GUIProperties->TabButtonsWindowStatusButtonIsPressed = true;
            GUIProperties->TabButtonsWindowBattleButtonIsPressed = false;
            GUIProperties->TabButtonsWindowMiniMapButtonIsPressed = false;

            GUIProperties->ShowEquipmentWindow = false;
            GUIProperties->ShowStatusWindow = true;
            GUIProperties->ShowMiniMapWindow = false;

            GUIProperties->ShowInventoryWindow = false;
            GUIProperties->ShowSkillsWindow = true;
            GUIProperties->ShowBattleWindow = false;

            m_statusButtonSprite.setTextureRect(tb::Resources::TextureRects::GUI::TabButtonsWindowStatusButtonPressed);
        }

        if (battleButtonRect.contains(mousePosition) == true)
        {
            GUIProperties->TabButtonsWindowInventoryButtonIsPressed = false;
            GUIProperties->TabButtonsWindowStatusButtonIsPressed = false;
            GUIProperties->TabButtonsWindowBattleButtonIsPressed = true;
            GUIProperties->TabButtonsWindowMiniMapButtonIsPressed = false;

            GUIProperties->ShowEquipmentWindow = true;
            GUIProperties->ShowStatusWindow = false;
            GUIProperties->ShowMiniMapWindow = false;

            GUIProperties->ShowInventoryWindow = false;
            GUIProperties->ShowSkillsWindow = false;
            GUIProperties->ShowBattleWindow = true;

            m_battleButtonSprite.setTextureRect(tb::Resources::TextureRects::GUI::TabButtonsWindowBattleButtonPressed);
        }

        if (miniMapButtonRect.contains(mousePosition) == true)
        {
            GUIProperties->TabButtonsWindowInventoryButtonIsPressed = false;
            GUIProperties->TabButtonsWindowStatusButtonIsPressed = false;
            GUIProperties->TabButtonsWindowBattleButtonIsPressed = false;
            GUIProperties->TabButtonsWindowMiniMapButtonIsPressed = true;

            GUIProperties->ShowEquipmentWindow = false;
            GUIProperties->ShowStatusWindow = false;
            GUIProperties->ShowMiniMapWindow = true;

            //GUIProperties->ShowInventoryWindow = x;
            //GUIProperties->ShowSkillsWindow = x;
            //GUIProperties->ShowBattleWindow = x;

            m_miniMapButtonSprite.setTextureRect(tb::Resources::TextureRects::GUI::TabButtonsWindowMiniMapButtonPressed);
        }

        updateButtons();
    }
}

void TabButtonsWindow::handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased)
{
    //
}

void TabButtonsWindow::updateButtons()
{
    tb::GUI::Properties* GUIProperties = g_GUI.getProperties();

    // inventory buttons

    if (GUIProperties->TabButtonsWindowInventoryButtonIsPressed == true)
    {
        m_inventoryButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowInventoryButtonPressed;
    }
    else
    {
        m_inventoryButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowInventoryButtonReleased;
    }

    m_inventoryButtonSprite.setTextureRect(m_inventoryButtonTextureRect);

    // status buttons

    if (GUIProperties->TabButtonsWindowStatusButtonIsPressed == true)
    {
        m_statusButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowStatusButtonPressed;
    }
    else
    {
        m_statusButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowStatusButtonReleased;
    }

    m_statusButtonSprite.setTextureRect(m_statusButtonTextureRect);

    // battle buttons

    if (GUIProperties->TabButtonsWindowBattleButtonIsPressed == true)
    {
        m_battleButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowBattleButtonPressed;
    }
    else
    {
        m_battleButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowBattleButtonReleased;
    }

    m_battleButtonSprite.setTextureRect(m_battleButtonTextureRect);


    // minimap buttons

    if (GUIProperties->TabButtonsWindowMiniMapButtonIsPressed == true)
    {
        m_miniMapButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowMiniMapButtonPressed;
    }
    else
    {
        m_miniMapButtonTextureRect = tb::Resources::TextureRects::GUI::TabButtonsWindowMiniMapButtonReleased;
    }

    m_miniMapButtonSprite.setTextureRect(m_miniMapButtonTextureRect);
}

void TabButtonsWindow::setPositionInLayout()
{
    sf::FloatRect GUIRightLayoutRect = g_GUI.getRightLayoutRect();

    sf::FloatRect miniMapWindowRect = g_MiniMapWindow.getRect();

    float paddinRenderWindow = tb::Constants::GUIPaddingRenderWindow;

    sf::Vector2f windowPosition;
    windowPosition.x = GUIRightLayoutRect.position.x;
    windowPosition.y = miniMapWindowRect.position.y + miniMapWindowRect.size.y + paddinRenderWindow;

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
