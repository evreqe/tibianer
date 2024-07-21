#include "tb/ConnectionWindow.h"

namespace tb
{

    ConnectionWindow::ConnectionWindow()
    {
        //
    }

    ConnectionWindow::~ConnectionWindow()
    {
        //
    }

    void ConnectionWindow::draw()
    {
        center();

        bool* isVisible = getIsVisible();

        ImGui::Begin("How to get a connection##ConnectionWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

        ImGui::TextUnformatted(m_displayText);

        float windowWidth = ImGui::GetWindowSize().x;

        ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth / 2.0f) - (m_buttonSize.x / 2.0f));

        if (ImGui::Button("OK##ConnectionWindowButtonOK", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::End();
    }

}
