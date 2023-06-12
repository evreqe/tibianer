#pragma once

#include "common.h"

#include "tb/SfmlGuiWindow.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Sprite.h"
#include "tb/BitmapFontText.h"
#include "tb/BitmapFontTextBatch.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

#include "tb/RenderWindow.h"
#include "tb/TabButtonsWindow.h"
#include "tb/Game.h"

namespace tb
{

class SkillsWindow : public SfmlGuiWindow
{

public:

    SkillsWindow();
    ~SkillsWindow();

    static SkillsWindow& getInstance()
    {
        static SkillsWindow instance;
        return instance;
    }

private:

    SkillsWindow(const SkillsWindow&) = delete;
    SkillsWindow(SkillsWindow&&) = delete;
    SkillsWindow& operator=(const SkillsWindow&) = delete;
    SkillsWindow& operator=(SkillsWindow&&) = delete;

public:

    void handleMouseWheelMovedEvent(sf::Event event);
    void handleMouseButtonPressedEvent(sf::Event event);
    void handleMouseButtonReleasedEvent(sf::Event event);
    void handleResizedEvent(sf::Event event);

    void setSizeInLayout();
    void setPositionInLayout();

    void updateSkillsText();

    void predraw();
    void draw();
    void drawSkillsText();

private:

    bool m_predraw = false;

    sf::Sprite m_woodSprite;

    tb::BitmapFontTextBatch m_skillsBitmapFontTextBatch;

    tb::BitmapFontText m_skillNamesBitmapFontText;

    const std::string m_skillNamesText = "FIST FIGHTING:\nCLUB FIGHTING:\nSWORD FIGHTING:\nAXE FIGHTING:\nDISTANCE FIGHTING:\nSHIELDING:\nFISHING:";

    sf::Vector2f m_viewSize = sf::Vector2f(tb::Constants::GuiRightLayoutWidthAsFloat, tb::Constants::GuiRightLayoutWidthAsFloat);

    sf::Vector2i m_windowRenderTextureSize = sf::Vector2i(tb::Constants::GuiRightLayoutWidthAsInt, tb::Constants::GuiRightLayoutWidthAsInt);

};

}

namespace
{
    inline tb::SkillsWindow& g_SkillsWindow = tb::SkillsWindow::getInstance();
}
