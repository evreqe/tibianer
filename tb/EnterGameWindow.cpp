#include "tb/EnterGameWindow.h"

namespace tb
{

EnterGameWindow::EnterGameWindow()
{
    //
}

EnterGameWindow::~EnterGameWindow()
{
    //
}

void EnterGameWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Enter Game##EnterGameWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    if (ImGui::BeginTable("##EnterGameWindowTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        ImGui::TextUnformatted("Player Data:");

        ImGui::TextUnformatted(" ");

        ImGui::TextUnformatted("Character Name:");

        ImGui::SameLine();

        ImGui::SetNextItemWidth(m_inputTextWidth);

        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && ImGui::IsAnyItemActive() == false && ImGui::IsMouseClicked(ImGuiMouseButton_Left) == false)
        {
            ImGui::SetKeyboardFocusHere(0);
        }

        ImGui::InputText("##EnterGameWindowInputTextCharacterName", &m_characterName);

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("Let's Go##EnterGameWindowButtonLetsGo", m_buttonSize))
        {
            if (m_characterName.size() != 0)
            {
                setIsVisible(false);

                g_Game.setGameState(tb::GameState::MapSelect);

                g_MapSelectWindow.setIsVisible(true);
            }
        }

        if (ImGui::Button("Cancel##EnterGameWindowButtonCancel", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

std::string EnterGameWindow::getCharacterName()
{
    return m_characterName;
}

}
