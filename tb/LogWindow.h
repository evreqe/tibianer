#pragma once

#include "common.h"

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

    const ImVec2 m_windowSize = ImVec2(320.0f, 240.0f);

};

}

namespace
{
    inline tb::LogWindow& g_LogWindow = tb::LogWindow::getInstance();
}
