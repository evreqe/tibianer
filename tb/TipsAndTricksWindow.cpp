#include "tb/TipsAndTricksWindow.h"

namespace tb
{

TipsAndTricksWindow::TipsAndTricksWindow()
{
    //
}

TipsAndTricksWindow::~TipsAndTricksWindow()
{
    //
}

void TipsAndTricksWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Tips & Tricks##TipsAndTricksWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted(m_displayText);

    auto windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth * 0.5f) - (m_buttonSize.x * 0.5f));

    if (ImGui::Button("OK##TipsAndTricksWindowButtonOK", m_buttonSize))
    {
        setIsVisible(false);
    }

    ImGui::End();
}

}
