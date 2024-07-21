#include "tb/StatusBar.h"

namespace tb
{

StatusBar::StatusBar()
{
    setIsVisible(true);
}

StatusBar::~StatusBar()
{
    //
}

void StatusBar::draw()
{
    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    sf::Vector2u renderWindowSize2u = renderWindow->getSize();

    sf::Vector2f renderWindowSize2f = static_cast<sf::Vector2f>(renderWindowSize2u);

    ImGui::SetNextWindowPos(ImVec2(0.0f, renderWindowSize2f.y - m_height));
    ImGui::SetNextWindowSize(ImVec2(renderWindowSize2f.x, m_height));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 2.0f));

    bool* isVisible = getIsVisible();

    ImGui::Begin("##StatusBarWindow", isVisible, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::PopStyleVar(2);

    ImGui::SetCursorPosX(m_textPadding);

    ImGui::TextUnformatted(m_text.c_str());

    if (g_Game.getGameState() == tb::GameState::InGame)
    {
        ImGui::SameLine();

        std::string rightText = "H 0, M 0, C 0, A 0";

        ImVec2 rightTextSize = ImGui::CalcTextSize(rightText.c_str());

        // apply right-justify alignment
        ImGui::SetCursorPosX(renderWindowSize2f.x - rightTextSize.x - m_textPadding);

        ImGui::TextUnformatted(rightText.c_str());
    }

    ImGui::End();
}

float StatusBar::getHeight()
{
    if (*getIsVisible() == false)
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

}
