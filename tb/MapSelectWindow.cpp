#include "tb/MapSelectWindow.h"

namespace tb
{

MapSelectWindow::MapSelectWindow()
{
    //
}

MapSelectWindow::~MapSelectWindow()
{
    //
}

void MapSelectWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Map Select##MapSelectWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    if (ImGui::BeginTable("##MapSelectWindowTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::BeginListBox("##MapSelectWindowListBoxData", ImVec2(320.0f, 10.0f * ImGui::GetTextLineHeightWithSpacing())))
        {
            tb::MapData::DataList* mapDataList = g_MapData.getDataList();

            for (unsigned int i = 0; auto& data : *mapDataList)
            {
                const bool isSelected = (m_selectedListBoxIndex == i);

                std::string listText = std::format("{}##MapSelectWindowSelectable{}", data.Name, i);

                if (ImGui::Selectable(listText.c_str(), isSelected))
                {
                    m_selectedListBoxIndex = i;
                }

                if (isSelected == true)
                {
                    ImGui::SetItemDefaultFocus();

                    m_selectedMapData = &data;
                }

                i++;
            }

            ImGui::EndListBox();
        }

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("OK##MapSelectWindowButtonOK", m_buttonSize))
        {
            if (m_selectedMapData != nullptr)
            {
                setIsVisible(false);

                g_Game.setGameState(tb::GameState::LoadingMap);

                g_Game.loadMapUsingThread(m_selectedMapData->FileName);
            }
        }

        if (ImGui::Button("Cancel##MapSelectWindowButtonCancel", m_buttonSize))
        {
            setIsVisible(false);

            g_Game.setGameState(tb::GameState::EnterGame);
        }

        if (m_selectedMapData != nullptr)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);

            ImGui::TextUnformatted(std::format("Name: {}", m_selectedMapData->Name).c_str());
            ImGui::TextUnformatted(std::format("Author: {}", m_selectedMapData->Author).c_str());
            ImGui::TextUnformatted("Description:");
            if (ImGui::BeginChild("##MapSelectWindowChildDescription", ImVec2(0.0f, 240.0f), true))
            {
                ImGui::TextUnformatted(std::format("{}", m_selectedMapData->Description).c_str());

                ImGui::EndChild();
            }
            ImGui::TextUnformatted(std::format("Size: {}x{}", m_selectedMapData->TileWidth, m_selectedMapData->TileHeight).c_str());
            ImGui::TextUnformatted(std::format("File: {}", m_selectedMapData->FileName).c_str());
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

}
