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

    auto windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth * 0.5f) - (m_buttonSize.x * 0.5f));

    if (ImGui::Button("OK##ControlsWindowButtonOK", m_buttonSize))
    {
        setIsVisible(false);
    }

    ImGui::End();
}

}
