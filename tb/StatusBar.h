#pragma once

#include "common.h"

#include "tb/Constants.h"

#include "tb/Window.h"

#include "tb/RenderWindow.h"
#include "tb/Game.h"

namespace tb
{

class StatusBar : public Window
{

public:

    StatusBar();
    ~StatusBar();

    static StatusBar& getInstance()
    {
        static StatusBar instance;
        return instance;
    }

private:

    StatusBar(const StatusBar&) = delete;
    StatusBar(StatusBar&&) = delete;
    StatusBar& operator=(const StatusBar&) = delete;
    StatusBar& operator=(StatusBar&&) = delete;

public:

    void draw();

    float getHeight();
    void setHeight(float height);

    std::string_view getText();
    void setText(const std::string& text);

private:

    const float m_heightDefault = 19.0f;

    float m_height = m_heightDefault;

    const float m_bottomRightTextPadding = 8.0f;

    const std::string m_TextDefault = "Welcome to Tibianer!";

    std::string m_text = m_TextDefault;
};

}

namespace
{
    inline tb::StatusBar& g_StatusBar = tb::StatusBar::getInstance();
}
