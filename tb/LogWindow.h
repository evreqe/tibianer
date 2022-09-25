#pragma once

#include "common.h"

#include "tb/Log.h"

#include "tb/Window.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class LogWindow : public Window
    {

    public:

        LogWindow();
        ~LogWindow();
        LogWindow(const LogWindow&) = delete;
        LogWindow(LogWindow&&) = delete;
        LogWindow& operator=(const LogWindow&) = delete;
        LogWindow& operator=(LogWindow&&) = delete;

        static LogWindow& getInstance()
        {
            static LogWindow logWindow;
            return logWindow;
        }

        void draw();

    private:

        //
    };

}

namespace
{
    tb::LogWindow& g_LogWindow = tb::LogWindow::getInstance();
}
