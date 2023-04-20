#include "tb/StatusBar.h"

namespace tb
{

StatusBar::StatusBar()
{
    //
}

StatusBar::~StatusBar()
{
    //
}

void StatusBar::draw()
{
    if (m_isVisible == false)
    {
        return;
    }

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2u renderWindowSize2u = renderWindow->getSize();

    sf::Vector2f renderWindowSize2f = static_cast<sf::Vector2f>(renderWindowSize2u);

    ImGui::SetNextWindowPos(ImVec2(0.0f, renderWindowSize2f.y - m_height));
    ImGui::SetNextWindowSize(ImVec2(renderWindowSize2f.x, m_height));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 2.0f));

    bool isVisible = true;
    ImGui::Begin("##StatusBar", &isVisible, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::PopStyleVar(2);

    ImGui::SetCursorPosX(8.0f);

    ImGui::TextUnformatted(m_text.c_str());

    if (g_Game.getGameState() == tb::GameState::InGame)
    {
        ImGui::SameLine();

        std::string bottomRightText = "H 0, M 0, C 0, A 0";

        ImVec2 bottomRightTextSize = ImGui::CalcTextSize(bottomRightText.c_str());

        // apply right-justify alignment
        ImGui::SetCursorPosX(renderWindowSize2f.x - bottomRightTextSize.x - m_bottomRightTextPadding);

        ImGui::TextUnformatted(bottomRightText.c_str());
    }

    ImGui::End();
}

float StatusBar::getHeight()
{
    if (m_isVisible == false)
    {
        return 0.0f;
    }

    return m_height;
}

void StatusBar::setHeight(float height)
{
    m_height = height;
}

std::string_view StatusBar::getText()
{
    return m_text;
}

void StatusBar::setText(const std::string& text)
{
    m_text = text;
}

bool StatusBar::getIsVisible()
{
    return m_isVisible;
}

void StatusBar::setIsVisible(bool b)
{
    m_isVisible = b;
}

void StatusBar::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

}
