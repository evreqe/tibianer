#include "tb/SpriteEditorWindow.h"

namespace tb
{

SpriteEditorWindow::SpriteEditorWindow()
{
    //
}

SpriteEditorWindow::~SpriteEditorWindow()
{
    //
}

void SpriteEditorWindow::resetInputs()
{
    memset(m_inputName, 0, sizeof(m_inputName));

    memset(m_inputArticle, 0, sizeof(m_inputArticle));

    m_inputWeight = 0.0f;

    m_inputTileWidth = 1;
    m_inputTileHeight = 1;
}

void SpriteEditorWindow::updateInputsFromSpriteData(tb::SpriteID_t spriteID)
{
    tb::SpriteData::Data* spriteData = &g_SpriteData.getDataList()->at(spriteID);

    if (spriteData == nullptr)
    {
        ImGui::Text("ERROR: spriteData == nullptr");
        ImGui::End();

        return;
    }

    resetInputs();

    spriteData->Name.copy(m_inputName, sizeof(m_inputName));

    spriteData->Article.copy(m_inputArticle, sizeof(m_inputArticle));

    m_inputWeight = spriteData->Weight;

    m_inputTileWidth = spriteData->TileWidth;
    m_inputTileHeight = spriteData->TileHeight;
}

void SpriteEditorWindow::updateSpriteDataFromInputs(tb::SpriteID_t spriteID)
{
    tb::SpriteData::Data* spriteData = &g_SpriteData.getDataList()->at(spriteID);

    if (spriteData == nullptr)
    {
        ImGui::Text("ERROR: spriteData == nullptr");
        ImGui::End();

        return;
    }

    spriteData->Name = m_inputName;

    spriteData->Article = m_inputArticle;

    spriteData->Weight = m_inputWeight;

    spriteData->TileWidth = m_inputTileWidth;
    spriteData->TileHeight = m_inputTileHeight;
}

void SpriteEditorWindow::draw()
{
    bool* isVisible = getIsVisible();

    ImGui::Begin("Sprite Editor##SpriteEditorWindow", isVisible, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (g_SpriteData.isLoaded() == false)
    {
        ImGui::Text("ERROR: g_SpriteData.isLoaded() == false");
        ImGui::End();

        return;
    }

    tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

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
                tb::Sprite sprite;
                sprite.setUseWidthAndHeight(false);
                sprite.setID(i);

                ImGui::PushID(std::format("##SpriteEditorChild1Button{}", i).c_str());

                // clicked on sprite
                if (ImGui::ImageButton(sprite))
                {
                    m_selectedSpriteID = i;

                    updateInputsFromSpriteData(i);
                }

                if (i == m_selectedSpriteID)
                {
                    auto min = ImGui::GetItemRectMin();
                    auto max = ImGui::GetItemRectMax();

                    ImGui::GetWindowDrawList()->AddRect(min, max, ImColor(255, 0, 255));
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

        tb::Sprite sprite;
        sprite.setUseWidthAndHeight(false);
        sprite.setID(m_selectedSpriteID);

        ImGui::ImageButton(sprite);

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

        if (ImGui::BeginCombo("##SpriteEditorComboHighlight", highlightComboPreviewText.c_str()))
        {
            for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
            {
                bool isSelected = (m_highlightComboSpriteFlag == spriteFlag);

                if (ImGui::Selectable(std::format("{0}##SpriteEditorComboHighlight{0}", spriteFlagName).c_str(), &isSelected))
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

        if (ImGui::InputText("Name:##SpriteEditorInputName", m_inputName, IM_ARRAYSIZE(m_inputName)))
        {
            updateSpriteDataFromInputs(m_selectedSpriteID);
        }

        if (ImGui::InputText("Article:##SpriteEditorInputArticle", m_inputArticle, IM_ARRAYSIZE(m_inputArticle)))
        {
            updateSpriteDataFromInputs(m_selectedSpriteID);
        }

        if (ImGui::InputFloat("Weight:##SpriteEditorInputWeight", &m_inputWeight, 0.0f, 0.0f, "%.2f"))
        {
            if (m_inputWeight < 0.0f) m_inputWeight = 0.0f;

            updateSpriteDataFromInputs(m_selectedSpriteID);
        }

        if (ImGui::InputInt("Tile Width:##SpriteEditorInputTileWidth", &m_inputTileWidth))
        {
            if (m_inputTileWidth < 1) m_inputTileWidth = 1;

            updateSpriteDataFromInputs(m_selectedSpriteID);
        }

        if (ImGui::InputInt("Tile Height:##SpriteEditorInputTileHeight", &m_inputTileHeight))
        {
            if (m_inputTileHeight < 1) m_inputTileHeight = 1;

            updateSpriteDataFromInputs(m_selectedSpriteID);
        }

        ImGui::Separator();

        if (ImGui::Button("Save##SpriteEditorButtonSave"))
        {
            g_SpriteData.save();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

tb::SpriteID_t SpriteEditorWindow::getSelectedSpriteID()
{
    return m_selectedSpriteID;
}

void SpriteEditorWindow::setSelectedSpriteID(tb::SpriteID_t id)
{
    m_selectedSpriteID = id;
}

}
