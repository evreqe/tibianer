#include "tb/Window.h"

namespace tb
{

Window::Window()
{
    //
}

Window::~Window()
{
    //
}

bool* Window::getIsVisible()
{
    return &m_isVisible;
}

void Window::setIsVisible(bool b)
{
    m_isVisible = b;
}

void Window::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

void Window::center()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_None, ImVec2(0.5f, 0.5f));
}

void Window::centerOnAppearing()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void Window::centerOnFirstUseEver()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
}

}
