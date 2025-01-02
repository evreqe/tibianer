#include "tb/StatusWindow.h"

namespace tb
{

StatusWindow::StatusWindow() :
    m_statusWindowSprite(tb::Textures::GUI)
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();

    //m_statusWindowSprite.setTexture(tb::Textures::GUI);
}

StatusWindow::~StatusWindow()
{
    //
}

void StatusWindow::handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled)
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

void StatusWindow::handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed)
{
    //
}

void StatusWindow::handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased)
{
    //
}

void StatusWindow::setPositionInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    setPosition(guiRightLayoutRect.position);
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
