#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/SpriteData.h"

#include "tb/Sprite.h"

namespace tb
{

    class AboutTibianerWindow : public tb::ImGuiWindow
    {

    public:

        AboutTibianerWindow();
        ~AboutTibianerWindow();

        static AboutTibianerWindow& getInstance()
        {
            static AboutTibianerWindow instance;
            return instance;
        }

    private:

        AboutTibianerWindow(const AboutTibianerWindow&) = delete;
        AboutTibianerWindow(AboutTibianerWindow&&) = delete;
        AboutTibianerWindow& operator=(const AboutTibianerWindow&) = delete;
        AboutTibianerWindow& operator=(AboutTibianerWindow&&) = delete;

    public:

        void draw();

    private:

        const char* m_displayText = "Tibianer\nby Evremonde\n\nhttps://evretibia.itch.io/tibianer";

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::AboutTibianerWindow& g_AboutTibianerWindow = tb::AboutTibianerWindow::getInstance();
}
