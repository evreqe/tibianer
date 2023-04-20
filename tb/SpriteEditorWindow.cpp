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
    m_inputName = "";
    m_inputArticle = "";
    m_inputDescription = "";

    m_inputTileWidth = 1;
    m_inputTileHeight = 1;

    m_inputWeight = 0.0f;
    m_inputLightRadius = 0.0f;
}

void SpriteEditorWindow::updateInputsFromSpriteData(tb::SpriteID_t spriteID)
{
    tb::SpriteData::Data* spriteData = &g_SpriteData.getDataList()->at(spriteID);

    resetInputs();

    m_inputName = spriteData->Name;
    m_inputArticle = spriteData->Article;
    m_inputDescription = spriteData->Description;

    m_inputTileWidth = spriteData->TileWidth;
    m_inputTileHeight = spriteData->TileHeight;

    m_inputWeight = spriteData->Weight;
    m_inputLightRadius = spriteData->LightRadius;
}

void SpriteEditorWindow::updateSpriteDataFromInputs(tb::SpriteID_t spriteID)
{
    tb::SpriteData::Data* spriteData = &g_SpriteData.getDataList()->at(spriteID);

    spriteData->Name = m_inputName;
    spriteData->Article = m_inputArticle;
    spriteData->Description = m_inputDescription;

    spriteData->TileWidth = static_cast<uint8_t>(m_inputTileWidth);
    spriteData->TileHeight = static_cast<uint8_t>(m_inputTileHeight);

    spriteData->Weight = m_inputWeight;
    spriteData->LightRadius = m_inputLightRadius;
}

void SpriteEditorWindow::draw()
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: Sprite data is not loaded");
        return;
    }

    tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float menuBarHeight = g_MenuBar.getHeight();
    const float statusBarHeight = g_StatusBar.getHeight();

    ImVec2 windowPosition = viewport->Pos;
    windowPosition.y += menuBarHeight;

    ImVec2 windowSize = viewport->Size;
    windowSize.y -= statusBarHeight + menuBarHeight;

    ImGui::SetNextWindowPos(windowPosition);
    ImGui::SetNextWindowSize(windowSize);

    bool* isVisible = getIsVisible();

    ImGui::Begin("Sprite Editor##SpriteEditorWindow", isVisible, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (ImGui::BeginTable("##SpriteEditorWindowTable", 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        if (ImGui::BeginChild("##SpriteEditorWindowChild1", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar))
        {
            for (tb::SpriteID_t i = 1; i < tb::Constants::NumSprites + 1; i++)
            {
                tb::Sprite sprite;
                sprite.setID(i);

                ImGui::PushID(std::format("##SpriteEditorWindowChild1Button{}", i).c_str());

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

                tb::SpriteFlags* spriteFlags = &spriteDataList->at(i).SpriteFlags;

                if (spriteFlags->hasFlag(m_highlightComboSpriteFlag) == true)
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

        ImGui::TextUnformatted(std::format("Sprite: {}", m_selectedSpriteID).c_str());

        tb::Sprite sprite;
        sprite.setID(static_cast<tb::SpriteID_t>(m_selectedSpriteID));

        ImGui::ImageButton(sprite);

        ImGui::TextUnformatted("Highlight Flag:");

        ImGui::SameLine();

        std::string_view highlightComboPreviewText = magic_enum::enum_name(m_highlightComboSpriteFlag);

        if (ImGui::BeginCombo("##SpriteEditorWindowComboHighlight", highlightComboPreviewText.data()))
        {
            for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
            {
                bool isSelected = (m_highlightComboSpriteFlag == spriteFlag);

                if (ImGui::Selectable(std::format("{0}##SpriteEditorWindowComboHighlight{0}", spriteFlagName).c_str(), &isSelected))
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

        ImGui::Separator();

        ImGui::TextUnformatted("Flags:");

        if (ImGui::BeginChild("##SpriteEditorWindowChild2", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize))
        {
            tb::SpriteFlags* spriteFlags = &spriteDataList->at(m_selectedSpriteID).SpriteFlags;

            for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
            {
                bool isChecked = spriteFlags->hasFlag(spriteFlag);

                if (ImGui::Checkbox(std::format("{0}##SpriteEditorWindowChild2Checkbox{1}{0}", spriteFlagName, m_selectedSpriteID).c_str(), &isChecked))
                {
                    spriteFlags->flipFlag(spriteFlag);
                }
            }

            ImGui::EndChild();
        }

        ImGui::TableSetColumnIndex(2);

        if (ImGui::Button("Save##SpriteEditorWindowButtonSave", m_buttonSize))
        {
            g_SpriteData.save();
        }

        ImGui::Separator();

        ImGui::TextUnformatted("Properties:");

        if (ImGui::BeginChild("##SpriteEditorWindowChild3", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize))
        {
            if (ImGui::InputText("Name:##SpriteEditorWindowInputName", &m_inputName))
            {
                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            if (ImGui::InputText("Article:##SpriteEditorWindowInputArticle", &m_inputArticle))
            {
                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            if (ImGui::InputText("Description:##SpriteEditorWindowInputDescription", &m_inputDescription))
            {
                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            if (ImGui::InputInt("Tile Width:##SpriteEditorWindowInputTileWidth", &m_inputTileWidth))
            {
                if (m_inputTileWidth < 1)
                {
                    m_inputTileWidth = 1;
                }

                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            if (ImGui::InputInt("Tile Height:##SpriteEditorWindowInputTileHeight", &m_inputTileHeight))
            {
                if (m_inputTileHeight < 1)
                {
                    m_inputTileHeight = 1;
                }

                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            if (ImGui::InputFloat("Weight:##SpriteEditorWindowInputWeight", &m_inputWeight, 0.0f, 0.0f, "%.2f"))
            {
                if (m_inputWeight < 0.0f)
                {
                    m_inputWeight = 0.0f;
                }

                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            if (ImGui::InputFloat("Light Radius:##SpriteEditorWindowInputLightRadius", &m_inputLightRadius, 0.0f, 0.0f, "%.2f"))
            {
                if (m_inputLightRadius < 0.0f)
                {
                    m_inputLightRadius = 0.0f;
                }

                updateSpriteDataFromInputs(m_selectedSpriteID);
            }

            ImGui::EndChild();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

tb::SpriteID_t SpriteEditorWindow::getSelectedSpriteID()
{
    return m_selectedSpriteID;
}

void SpriteEditorWindow::setSelectedSpriteID(tb::SpriteID_t spriteID)
{
    m_selectedSpriteID = spriteID;
}

}
