#include "tb/ErrorWindow.h"

namespace tb
{

ErrorWindow::ErrorWindow()
{
    //
}

void ErrorWindow::draw()
{
    ImGui::Begin(m_titleText.c_str(), &m_isVisible, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text(m_errorText.c_str());

    ImGui::End();
}

void ErrorWindow::setTitleText(const std::string& text)
{
    m_titleText = text;
}

void ErrorWindow::setErrorText(const std::string& text)
{
    m_errorText = text;
}

bool ErrorWindow::getIsVisible()
{
    return m_isVisible;
}

void ErrorWindow::setIsVisible(bool b)
{
    m_isVisible = b;
}

void ErrorWindow::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

}
