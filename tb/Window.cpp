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

void Window::centerAndResizeOnFirstUseEver()
{
    auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetCenter(), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
}

}
