#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

namespace tb
{

class AboutTibiaWindow : public tb::ImGuiWindow
{

public:

    AboutTibiaWindow();
    ~AboutTibiaWindow();

    static AboutTibiaWindow& getInstance()
    {
        static AboutTibiaWindow instance;
        return instance;
    }

private:

    AboutTibiaWindow(const AboutTibiaWindow&) = delete;
    AboutTibiaWindow(AboutTibiaWindow&&) = delete;
    AboutTibiaWindow& operator=(const AboutTibiaWindow&) = delete;
    AboutTibiaWindow& operator=(AboutTibiaWindow&&) = delete;

public:

    void draw();

private:

    const char* m_displayText = "Tibia\nby CipSoft\n\nwww.tibia.com";

    const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

};

}

namespace
{
    inline tb::AboutTibiaWindow& g_AboutTibiaWindow = tb::AboutTibiaWindow::getInstance();
}
