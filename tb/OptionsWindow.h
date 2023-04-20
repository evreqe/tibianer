#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/OptionsData.h"

namespace tb
{

    class OptionsWindow : public Window
    {

    public:

        OptionsWindow();
        ~OptionsWindow();

        static OptionsWindow& getInstance()
        {
            static OptionsWindow instance;
            return instance;
        }

    private:

        OptionsWindow(const OptionsWindow&) = delete;
        OptionsWindow(OptionsWindow&&) = delete;
        OptionsWindow& operator=(const OptionsWindow&) = delete;
        OptionsWindow& operator=(OptionsWindow&&) = delete;

    public:

        void load();
        void save();

        void draw();

    private:

        std::string m_inputPlayerName;

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::OptionsWindow& g_OptionsWindow = tb::OptionsWindow::getInstance();
}
