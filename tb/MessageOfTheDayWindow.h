#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/MessageOfTheDayData.h"

namespace tb
{

class MessageOfTheDayWindow : public tb::ImGuiWindow
{

public:

    MessageOfTheDayWindow();
    ~MessageOfTheDayWindow();

    static MessageOfTheDayWindow& getInstance()
    {
        static MessageOfTheDayWindow instance;
        return instance;
    }

private:

    MessageOfTheDayWindow(const MessageOfTheDayWindow&) = delete;
    MessageOfTheDayWindow(MessageOfTheDayWindow&&) = delete;
    MessageOfTheDayWindow& operator=(const MessageOfTheDayWindow&) = delete;
    MessageOfTheDayWindow& operator=(MessageOfTheDayWindow&&) = delete;

public:

    void onLoad();

    void draw();

private:

    bool m_isLoaded = false;

    std::string m_messageOfTheDayText;

    const ImVec2 m_buttonSize = ImVec2(88.0f, 23.0f);

};

}

namespace
{
    inline tb::MessageOfTheDayWindow& g_MessageOfTheDayWindow = tb::MessageOfTheDayWindow::getInstance();
}
