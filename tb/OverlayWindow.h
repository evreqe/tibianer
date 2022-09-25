#pragma once

#include "common.h"

#include "tb/Window.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace tb
{

    class OverlayWindow : public Window
    {

    public:

        OverlayWindow();
        ~OverlayWindow();
        OverlayWindow(const OverlayWindow&) = delete;
        OverlayWindow(OverlayWindow&&) = delete;
        OverlayWindow& operator=(const OverlayWindow&) = delete;
        OverlayWindow& operator=(OverlayWindow&&) = delete;

        static OverlayWindow& getInstance()
        {
            static OverlayWindow overlayWindow;
            return overlayWindow;
        }

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
    tb::OverlayWindow& g_OverlayWindow = tb::OverlayWindow::getInstance();
}
