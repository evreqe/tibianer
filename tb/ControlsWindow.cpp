#include "tb/ControlsWindow.h"

namespace tb
{

ControlsWindow::ControlsWindow()
{
    //
}

ControlsWindow::~ControlsWindow()
{
    //
}

void ControlsWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("How to control your character##ControlsWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted(m_displayText);

    float windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth / 2.0f) - (m_buttonSize.x / 2.0f));

    if (ImGui::Button("OK##ControlsWindowButtonOK", m_buttonSize))
    {
        setIsVisible(false);
    }

    ImGui::End();
}

}
