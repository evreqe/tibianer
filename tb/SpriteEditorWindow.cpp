#include "tb/SpriteEditorWindow.h"

namespace tb
{

SpriteEditorWindow::SpriteEditorWindow()
{
    //
}

void SpriteEditorWindow::draw()
{
    ImGui::Begin("Sprite Editor##SpriteEditorWindow", &m_isVisible, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (m_spriteData == nullptr)
    {
        ImGui::Text("ERROR: m_spriteData == nullptr");
        ImGui::End();

        return;
    }

    auto spriteDataList = m_spriteData->getDataList();

    if (spriteDataList == nullptr)
    {
        ImGui::Text("ERROR: spriteDataList == nullptr");
        ImGui::End();

        return;
    }

    if (ImGui::BeginTable("##SpriteEditorTable", 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        if (ImGui::BeginChild("##SpriteEditorChild1", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar))
        {
            for (unsigned int i = 1; i < tb::Constants::NumSprites + 1; i++)
            {
                tb::Sprite spr;
                spr.setUseWidthAndHeight(false);
                spr.setID(i);

                ImGui::PushID(std::format("##SpriteEditorChild1Button{}", i).c_str());

                if (ImGui::ImageButton(spr))
                {
                    m_selectedSpriteID = i;
                }

                tb::SpriteFlags_t* spriteFlags = &spriteDataList->at(i).SpriteFlags;

                bool isHighlighted = spriteFlags->test(m_highlightComboSpriteFlag);

                if (isHighlighted == true)
                {
                    auto min = ImGui::GetItemRectMin();
                    auto max = ImGui::GetItemRectMax();

                    ImGui::GetWindowDrawList()->AddRect(min, max, ImColor(255, 0, 0));
                }

                ImGui::PopID();

                if (i % 64 != 0)
                {
                    ImGui::SameLine();
                }
            }

            ImGui::EndChild();
        }

        ImGui::TableSetColumnIndex(1);

        ImGui::Text(std::format("Sprite: {}", m_selectedSpriteID).c_str());

        tb::Sprite spr;
        spr.setUseWidthAndHeight(false);
        spr.setID(m_selectedSpriteID);

        ImGui::ImageButton(spr);

        ImGui::Text("Flags:");

        if (ImGui::BeginChild("##SpriteEditorChild2", ImVec2(0, 480), true))
        {
            for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
            {
                tb::SpriteFlags_t* spriteFlags = &spriteDataList->at(m_selectedSpriteID).SpriteFlags;

                bool isChecked = spriteFlags->test(spriteFlag);

                if (ImGui::Checkbox(std::format("{0}##SpriteEditorChild2Checkbox{1}{0}", spriteFlagName, m_selectedSpriteID).c_str(), &isChecked))
                {
                    spriteFlags->flip(spriteFlag);
                }
            }

            ImGui::EndChild();
        }

        ImGui::Text("Highlight Flag:");

        std::string highlightComboPreviewText = "Null";

        for (auto it = tb::KeyValues::SpriteFlags.begin(); it != tb::KeyValues::SpriteFlags.end(); ++it)
        {
            if (it->second == m_highlightComboSpriteFlag)
            {
                highlightComboPreviewText = it->first;
            }
        }

        if (ImGui::BeginCombo("##SpriteEditorHighlightCombo", highlightComboPreviewText.c_str()))
        {
            for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
            {
                bool isSelected = (m_highlightComboSpriteFlag == spriteFlag);

                if (ImGui::Selectable(std::format("{0}##SpriteEditorHighlightCombo{0}", spriteFlagName).c_str(), &isSelected))
                {
                    m_highlightComboSpriteFlag = spriteFlag;
                }

                if (isSelected == true)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::TableSetColumnIndex(2);

        ImGui::Text("Name:");

        ImGui::Text("Article:");

        ImGui::Text("Weight:");

        ImGui::Text("Width:");

        ImGui::Text("Height:");

        ImGui::Separator();

        if (ImGui::Button("Save##SpriteEditorSaveButton"))
        {
            m_spriteData->save();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void SpriteEditorWindow::setSpriteData(tb::SpriteData& spriteData)
{
    m_spriteData = &spriteData;
}

tb::SpriteID_t SpriteEditorWindow::getSelectedSpriteID()
{
    return m_selectedSpriteID;
}

void SpriteEditorWindow::setSelectedSpriteID(tb::SpriteID_t id)
{
    m_selectedSpriteID = id;
}

bool SpriteEditorWindow::getIsVisible()
{
    return m_isVisible;
}

void SpriteEditorWindow::setIsVisible(bool b)
{
    m_isVisible = b;
}

void SpriteEditorWindow::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

}
