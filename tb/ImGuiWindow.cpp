#include "tb/ImGuiWindow.h"

namespace tb
{

ImGuiWindow::ImGuiWindow()
{
    //
}

ImGuiWindow::~ImGuiWindow()
{
    //
}

bool* ImGuiWindow::getIsVisible()
{
    return &m_isVisible;
}

void ImGuiWindow::setIsVisible(bool b)
{
    m_isVisible = b;
}

void ImGuiWindow::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

void ImGuiWindow::center()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_None, ImVec2(0.5f, 0.5f));
}

void ImGuiWindow::centerOnAppearing()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void ImGuiWindow::centerOnFirstUseEver()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
}

}
