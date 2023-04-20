#include "tb/HotkeysWindow.h"

namespace tb
{

    HotkeysWindow::HotkeysWindow()
    {
        //
    }

    HotkeysWindow::~HotkeysWindow()
    {
        //
    }

    void HotkeysWindow::draw()
    {
        center();

        bool* isVisible = getIsVisible();

        ImGui::Begin("Hotkeys##HotkeysWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

        ImGui::TextUnformatted("TODO: make hotkeys window");

        auto windowWidth = ImGui::GetWindowSize().x;

        ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth * 0.5f) - (m_buttonSize.x * 0.5f));

        if (ImGui::Button("OK##HotkeysWindowButtonOK", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::End();
    }

}
