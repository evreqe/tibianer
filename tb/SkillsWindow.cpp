#include "tb/SkillsWindow.h"

namespace tb
{

SkillsWindow::SkillsWindow()
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();
}

SkillsWindow::~SkillsWindow()
{
    //
}

void SkillsWindow::handleMouseWheelMovedEvent(sf::Event event)
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

void SkillsWindow::handleMouseButtonPressedEvent(sf::Event event)
{
    //
}

void SkillsWindow::handleMouseButtonReleasedEvent(sf::Event event)
{
    //
}

void SkillsWindow::handleResizedEvent(sf::Event event)
{
    setPositionInLayout();
    setSizeInLayout();
}

void SkillsWindow::setSizeInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    float guiRightLayoutRectBottomLeftY = guiRightLayoutRect.top + guiRightLayoutRect.height;

    sf::Vector2f windowPosition = getPosition();

    float windowSizeScale = getSizeScale();

    // this is width and height
    m_viewSize.x = tb::Constants::GuiRightLayoutWidthAsFloat;
    m_viewSize.y = guiRightLayoutRectBottomLeftY - windowPosition.y;

    sf::View* view = getView();

    view->reset(sf::FloatRect(0.0f, 0.0f, m_viewSize.x, m_viewSize.y / windowSizeScale));

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->create(static_cast<unsigned int>(m_viewSize.x), static_cast<unsigned int>(m_viewSize.y / windowSizeScale));
}

void SkillsWindow::setPositionInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    sf::FloatRect tabButtonsWindowRect = g_TabButtonsWindow.getRect();

    float padding = tb::Constants::PaddingRenderWindow;

    sf::Vector2f windowPosition;
    windowPosition.x = guiRightLayoutRect.left - 1.0f;
    windowPosition.y = tabButtonsWindowRect.top + tabButtonsWindowRect.height + padding;

    setPosition(windowPosition);
}

void SkillsWindow::updateSkillsText()
{
    tb::BitmapFont* tinyBitmapFont = g_Game.getTinyBitmapFont();

    m_skillsBitmapFontTextBatch.setBitmapFont(tinyBitmapFont);
    m_skillsBitmapFontTextBatch.setPosition(3.0f, 3.0f);

    sf::Color textColor = sf::Color::White;

    m_skillNamesBitmapFontText.setPaddingY(3);
    m_skillNamesBitmapFontText.setTextJustifyType(tb::TextJustifyType::Left);
    m_skillNamesBitmapFontText.setText(tinyBitmapFont, m_skillNamesText, textColor);

    m_skillsBitmapFontTextBatch.addBitmapFontText(&m_skillNamesBitmapFontText);
}

void SkillsWindow::predraw()
{
    updateSkillsText();
}

void SkillsWindow::draw()
{
    if (m_predraw == false)
    {
        predraw();

        m_predraw = true;
    }

    sf::View* view = getView();

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->setView(*view);

    windowRenderTexture->clear(sf::Color::White);

    sf::Vector2f windowSize = getSize();

    float windowSizeScale = getSizeScale();

    m_woodSprite.setTexture(tb::Textures::Wood, true);
    m_woodSprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)));

    windowRenderTexture->draw(m_woodSprite);

    drawSkillsText();

    windowRenderTexture->display();

    drawToRenderWindow();
}

void SkillsWindow::drawSkillsText()
{
    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    windowRenderTexture->draw(m_skillsBitmapFontTextBatch);
}

}
