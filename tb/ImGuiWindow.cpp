#include "common.h"

#include "tb/IMGUIWindow.h"

namespace tb
{

IMGUIWindow::IMGUIWindow()
{
    //
}

IMGUIWindow::~IMGUIWindow()
{
    //
}

bool* IMGUIWindow::isVisible()
{
    return &m_isVisible;
}

void IMGUIWindow::setVisible(bool b)
{
    m_isVisible = b;
}

void IMGUIWindow::toggleVisible()
{
    m_isVisible = !m_isVisible;
}

void IMGUIWindow::center()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_None, ImVec2(0.5f, 0.5f));
}

void IMGUIWindow::centerOnAppearing()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void IMGUIWindow::centerOnFirstUseEver()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
}

}
