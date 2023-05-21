#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/Log.h"

#include "tb/OptionsData.h"
#include "tb/Game.h"
#include "tb/MapSelectWindow.h"

namespace tb
{

    class EnterGameWindow : public tb::ImGuiWindow
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

        void onOpen();
        void onClose();

        void draw();

    private:

        bool m_isOpen = false;

        tb::OptionsData::Data* m_optionsData = nullptr;

        const float m_inputTextWidth = 131.0f;

        const ImVec2 m_buttonSize = ImVec2(105.0f, 29.0f);

    };

}

namespace
{
    inline tb::EnterGameWindow& g_EnterGameWindow = tb::EnterGameWindow::getInstance();
}
