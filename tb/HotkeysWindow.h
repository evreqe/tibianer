#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

namespace tb
{

    class HotkeysWindow : public Window
    {

    public:

        HotkeysWindow();
        ~HotkeysWindow();

        static HotkeysWindow& getInstance()
        {
            static HotkeysWindow instance;
            return instance;
        }

    private:

        HotkeysWindow(const HotkeysWindow&) = delete;
        HotkeysWindow(HotkeysWindow&&) = delete;
        HotkeysWindow& operator=(const HotkeysWindow&) = delete;
        HotkeysWindow& operator=(HotkeysWindow&&) = delete;

    public:

        void draw();

    private:

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::HotkeysWindow& g_HotkeysWindow = tb::HotkeysWindow::getInstance();
}
