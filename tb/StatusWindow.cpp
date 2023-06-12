#include "tb/StatusWindow.h"

namespace tb
{

StatusWindow::StatusWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    m_statusWindowSprite.setTexture(tb::Textures::GUI);
}

StatusWindow::~StatusWindow()
{
    //
}

void StatusWindow::handleMouseWheelMovedEvent(sf::Event event)
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

void StatusWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void StatusWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void StatusWindow::setPositionInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    setPosition(sf::Vector2f(guiRightLayoutRect.left, guiRightLayoutRect.top));
}

void StatusWindow::predraw()
{
    m_statusWindowSprite.setTextureRect(tb::GuiRects::StatusWindow);
}

void StatusWindow::draw()
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

    windowRenderTexture->draw(m_statusWindowSprite);

    windowRenderTexture->display();

    drawToRenderWindow();
}

sf::FloatRect StatusWindow::getHitPointsSlotRect()
{
    return m_hitPointsSlotRect;
}

sf::FloatRect StatusWindow::getCapSlotRect()
{
    return m_capSlotRect;
}

sf::FloatRect StatusWindow::getExperiencePointsSlotRect()
{
    return m_experiencePointsSlotRect;
}

sf::FloatRect StatusWindow::getManaPointsSlotRect()
{
    return m_manaPointsSlotRect;
}

sf::FloatRect StatusWindow::getLevelSlotRect()
{
    return m_levelSlotRect;
}

sf::FloatRect StatusWindow::getMagicLevelSlotRect()
{
    return m_magicLevelSlotRect;
}

}
