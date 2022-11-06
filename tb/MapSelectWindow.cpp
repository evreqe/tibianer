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

        static unsigned int selectedListBoxIndex = 0;

        static tb::MapData::Data* selectedMapData;

        if (ImGui::BeginListBox("##MapSelectWindowListBox", ImVec2(240.0f, 10.0f * ImGui::GetTextLineHeightWithSpacing())))
        {
            tb::MapData::DataList* mapDataList = g_MapData.getDataList();

            for (unsigned int i = 0; auto& data : *mapDataList)
            {
                const bool isSelected = (selectedListBoxIndex == i);

                if (ImGui::Selectable(data.FileName.c_str(), isSelected))
                {
                    selectedListBoxIndex = i;
                }

                if (isSelected == true)
                {
                    ImGui::SetItemDefaultFocus();

                    selectedMapData = &data;
                }

                i++;
            }

            ImGui::EndListBox();
        }

        ImGui::TableSetColumnIndex(1);

        if (ImGui::Button("OK##MapSelectWindowButtonOK", m_buttonSize))
        {
            if (selectedMapData != nullptr)
            {
                setIsVisible(false);

                g_Game.setGameState(tb::GameState::Loading);

                g_Game.setLoadMapFileName(selectedMapData->FileName);
            }
        }

        if (ImGui::Button("Cancel##MapSelectWindowButtonCancel", m_buttonSize))
        {
            setIsVisible(false);

            g_Game.setGameState(tb::GameState::EnterGame);
        }

        if (selectedMapData != nullptr)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            ImGui::TextUnformatted(std::format("Name: {}", selectedMapData->Name).c_str());
            ImGui::TextUnformatted(std::format("Author: {}", selectedMapData->Author).c_str());
            ImGui::TextUnformatted("Description:");
            if (ImGui::BeginChild("##MapSelectWindowChildDescription", ImVec2(0.0f, 100.0f), true))
            {
                ImGui::TextUnformatted(std::format("{}", selectedMapData->Description).c_str());

                ImGui::EndChild();
            }
            ImGui::TextUnformatted(std::format("Size: {}x{}", selectedMapData->TileWidth, selectedMapData->TileHeight).c_str());
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

}
