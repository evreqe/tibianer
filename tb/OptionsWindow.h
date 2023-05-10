#pragma once

#include "common.h"

#include "tb/Window.h"

#include "tb/OptionsData.h"
#include "tb/Game.h"

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

        void onOpen();
        void onClose();

        void loadData();
        void saveData();

        void draw();

    private:

        bool m_isOpen = false;

        tb::OptionsData::Data m_optionsData;

        const ImVec2 m_tabChildSize = ImVec2(640.0f, 480.0f);

        const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

    };

}

namespace
{
    inline tb::OptionsWindow& g_OptionsWindow = tb::OptionsWindow::getInstance();
}
