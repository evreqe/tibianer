#include "common.h"

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

    bool* pIsVisible = isVisible();

    ImGui::Begin("Tips & Tricks##TipsAndTricksWindow", pIsVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted(m_displayText);

    float windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth / 2.0f) - (m_buttonSize.x / 2.0f));

    if (ImGui::Button("OK##TipsAndTricksWindowButtonOK", m_buttonSize))
    {
        setVisible(false);
    }

    ImGui::End();
}

}
