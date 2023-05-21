#pragma once

#include "common.h"

#include "tb/ImGuiWindow.h"

#include "tb/Constants.h"

#include "tb/MenuBar.h"
#include "tb/StatusBar.h"

namespace tb
{

class OverlayWindow : public tb::ImGuiWindow
{

public:

    OverlayWindow();
    ~OverlayWindow();

    static OverlayWindow& getInstance()
    {
        static OverlayWindow instance;
        return instance;
    }

private:

    OverlayWindow(const OverlayWindow&) = delete;
    OverlayWindow(OverlayWindow&&) = delete;
    OverlayWindow& operator=(const OverlayWindow&) = delete;
    OverlayWindow& operator=(OverlayWindow&&) = delete;

public:

    void clearTextList();

    std::vector<std::string>* getTextList();

    void addTextToList(const std::string& text);

    void draw();

private:

    ImGuiWindowFlags m_windowFlags =
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoNavInputs |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoMouseInputs;


    const float m_windowBackgroundAlpha = 0.25f;

    std::vector<std::string> m_textList;
};

}

namespace
{
    inline tb::OverlayWindow& g_OverlayWindow = tb::OverlayWindow::getInstance();
}
