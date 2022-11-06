#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/Log.h"

#include "tb/Game.h"

#include "tb/MapSelectWindow.h"

namespace tb
{

    class EnterGameWindow : public Window
    {

    public:

        EnterGameWindow();
        ~EnterGameWindow();

        static EnterGameWindow& getInstance()
        {
            static EnterGameWindow instance;
            return instance;
        }

    private:

        EnterGameWindow(const EnterGameWindow&) = delete;
        EnterGameWindow(EnterGameWindow&&) = delete;
        EnterGameWindow& operator=(const EnterGameWindow&) = delete;
        EnterGameWindow& operator=(EnterGameWindow&&) = delete;

    public:

        void draw();

        std::string getCharacterName();

    private:

        std::string m_characterName;

        const float m_inputTextWidth = 131.0f;

        const ImVec2 m_buttonSize = ImVec2(105.0f, 29.0f);

    };

}

namespace
{
    inline tb::EnterGameWindow& g_EnterGameWindow = tb::EnterGameWindow::getInstance();
}
