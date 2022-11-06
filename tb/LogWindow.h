#pragma once

#include "common.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"

#include "tb/Window.h"

#include "tb/Log.h"

namespace tb
{

class LogWindow : public Window
{

public:

    LogWindow();
    ~LogWindow();

    static LogWindow& getInstance()
    {
        static LogWindow instance;
        return instance;
    }

private:

    LogWindow(const LogWindow&) = delete;
    LogWindow(LogWindow&&) = delete;
    LogWindow& operator=(const LogWindow&) = delete;
    LogWindow& operator=(LogWindow&&) = delete;

public:

    void draw();

private:

    //

};

}

namespace
{
    inline tb::LogWindow& g_LogWindow = tb::LogWindow::getInstance();
}
