#include "tb/SkillsWindow.h"

namespace tb
{

SkillsWindow::SkillsWindow() :
    m_woodSprite(tb::Textures::Wood)
{
    setWindowRenderTextureInitialSize(m_windowRenderTextureSize);

    setViewInitialSize(m_viewSize);

    initalize();
}

SkillsWindow::~SkillsWindow()
{
    //
}

void SkillsWindow::handleEventMouseWheelScrolled(const sf::Event::MouseWheelScrolled* eventMouseWheelScrolled)
{
    // scroll up
    if (eventMouseWheelScrolled->delta > 0)
    {
        //
    }
    // scroll down
    else if (eventMouseWheelScrolled->delta < 0)
    {
        //
    }
}

void SkillsWindow::handleEventMouseButtonPressed(const sf::Event::MouseButtonPressed* eventMouseButtonPressed)
{
    //
}

void SkillsWindow::handleEventMouseButtonReleased(const sf::Event::MouseButtonReleased* eventMouseButtonReleased)
{
    //
}

void SkillsWindow::handleEventResized(const sf::Event::Resized* eventResized)
{
    setPositionInLayout();
    setSizeInLayout();
}

void SkillsWindow::setSizeInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    float guiRightLayoutRectBottomLeftY = guiRightLayoutRect.position.y + guiRightLayoutRect.size.y;

    sf::Vector2f windowPosition = getPosition();

    float windowSizeScale = getSizeScale();

    // this is width and height
    m_viewSize.x = tb::Constants::GuiRightLayoutWidthAsFloat;
    m_viewSize.y = guiRightLayoutRectBottomLeftY - windowPosition.y;

    sf::View resetView = sf::View(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_viewSize.x, m_viewSize.y / windowSizeScale)));
    setView(resetView);

    sf::RenderTexture* windowRenderTexture = getWindowRenderTexture();

    bool resizeResult = windowRenderTexture->resize
    (
        sf::Vector2u
        (
            static_cast<std::uint32_t>(m_viewSize.x),
            static_cast<std::uint32_t>(m_viewSize.y / windowSizeScale)
        )
    );

    if (resizeResult == false)
    {
        g_Log.write("ERROR: Failed to resize RenderTexture\n");
    }
}

void SkillsWindow::setPositionInLayout()
{
    sf::FloatRect guiRightLayoutRect = g_Game.getGuiRightLayoutRect();

    sf::FloatRect tabButtonsWindowRect = g_TabButtonsWindow.getRect();

    float padding = tb::Constants::PaddingRenderWindow;

    sf::Vector2f windowPosition;
    windowPosition.x = guiRightLayoutRect.position.x - 1.0f;
    windowPosition.y = tabButtonsWindowRect.position.y + tabButtonsWindowRect.size.y + padding;

    setPosition(windowPosition);
}

void SkillsWindow::updateSkillsText()
{
    tb::BitmapFont* tinyBitmapFont = g_Game.getTinyBitmapFont();

    m_skillsBitmapFontTextBatch.setBitmapFont(tinyBitmapFont);
    m_skillsBitmapFontTextBatch.setPosition(sf::Vector2f(3.0f, 3.0f));

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
    m_woodSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y))));

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
