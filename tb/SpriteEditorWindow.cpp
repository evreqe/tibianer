#include "common.h"

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

void SpriteEditorWindow::onOpen()
{
    loadData();

    m_isOpen = true;
}

void SpriteEditorWindow::onClose()
{
    m_isOpen = false;
}

void SpriteEditorWindow::loadData()
{
    m_spriteDataList = g_SpriteData.getDataList();

    m_spriteData = &m_spriteDataList->at(m_selectedSpriteID);
}

void SpriteEditorWindow::saveData()
{
    g_SpriteData.save();
}

void SpriteEditorWindow::draw()
{
    if (m_isOpen == false)
    {
        onOpen();
    }

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float menuBarHeight = g_MenuBar.getHeight();
    const float statusBarHeight = g_StatusBar.getHeight();

    ImVec2 windowPosition = viewport->Pos;
    windowPosition.y += menuBarHeight;

    ImVec2 windowSize = viewport->Size;
    windowSize.y -= statusBarHeight + menuBarHeight;

    ImGui::SetNextWindowPos(windowPosition);
    ImGui::SetNextWindowSize(windowSize);

    bool* pIsVisible = isVisible();

    ImGui::Begin("Sprite Editor##SpriteEditorWindow", pIsVisible, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

    if (ImGui::BeginTable("##SpriteEditorWindowTable", 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        if (ImGui::BeginChild("##SpriteEditorWindowChildSpritesheet", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar))
        {
            auto numSprites = g_SpriteData.getDataList()->size();

            for (tb::SpriteID i = 1; i < numSprites; i++)
            {
                tb::Sprite sprite(tb::Resources::Textures::SpriteSheet);
                sprite.setID(i);

                std::string imageButtonID = std::format("##SpriteEditorWindowChildSpritesheetButton{}", i);

                // clicked on sprite
                if (ImGui::ImageButton(imageButtonID.c_str(), sprite, sf::Vector2f(tb::Constants::SpriteSizeAsFloat, tb::Constants::SpriteSizeAsFloat)))
                {
                    m_selectedSpriteID = i;

                    loadData();
                }

                // draw tooltip
                if (ImGui::BeginItemTooltip())
                {
                    std::stringstream toolTipWindowText;
                    toolTipWindowText << i;

                    std::string spriteName = g_SpriteData.getDataList()->at(i).Name;
                    if (spriteName.size() != 0)
                    {
                        toolTipWindowText << ": " << spriteName;
                    }

                    ImGui::TextUnformatted(toolTipWindowText.str().c_str());

                    ImGui::EndTooltip();
                }

                if (i == m_selectedSpriteID)
                {
                    tb::LibIMGUI::drawRectangleAtCurrentItem(ImColor(255, 0, 255));
                }

                tb::SpriteFlags* spriteFlags = &m_spriteDataList->at(i).SpriteFlags;

                if (spriteFlags->hasFlag(m_highlightSpriteFlag) == true)
                {
                    tb::LibIMGUI::drawRectangleAtCurrentItem(ImColor(255, 0, 0));
                }

                if (i % 64 != 0)
                {
                    ImGui::SameLine();
                }
            }

            tb::LibIMGUI::scrollWindowWithMiddleMouseButton();

            ImGui::EndChild();
        }

        ImGui::TableSetColumnIndex(1);

        ImGui::TextUnformatted(std::format("Sprite: {}", m_selectedSpriteID).c_str());

        tb::Sprite sprite(tb::Resources::Textures::SpriteSheet);
        sprite.setID(static_cast<tb::SpriteID>(m_selectedSpriteID));

        std::string imageButtonID = std::format("##SpriteEditorWindowSelectedSpriteButton{}", m_selectedSpriteID);

        ImGui::ImageButton(imageButtonID.c_str(), sprite, sf::Vector2f(tb::Constants::SpriteSizeAsFloat, tb::Constants::SpriteSizeAsFloat));

        ImGui::TextUnformatted("Highlight Flag:");

        ImGui::SameLine();

        std::string_view comboPreviewText = magic_enum::enum_name(m_highlightSpriteFlag);

        if (ImGui::BeginCombo("##SpriteEditorWindowComboHighlight", comboPreviewText.data()))
        {
            for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
            {
                bool isSelected = (m_highlightSpriteFlag == spriteFlag);

                if (ImGui::Selectable(std::format("{0}##SpriteEditorWindowComboHighlight{0}", spriteFlagName).c_str(), &isSelected))
                {
                    m_highlightSpriteFlag = spriteFlag;
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

        if (ImGui::BeginChild("##SpriteEditorWindowChildFlags", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_AlwaysAutoResize))
        {
            tb::SpriteFlags* spriteFlags = &m_spriteDataList->at(m_selectedSpriteID).SpriteFlags;

            for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
            {
                bool isChecked = spriteFlags->hasFlag(spriteFlag);

                if (ImGui::Checkbox(std::format("{0}##SpriteEditorWindowChildFlagsCheckbox{1}{0}", spriteFlagName, m_selectedSpriteID).c_str(), &isChecked))
                {
                    spriteFlags->flipFlag(spriteFlag);
                }
            }

            ImGui::EndChild();
        }

        ImGui::TableSetColumnIndex(2);

        if (ImGui::Button("Save##SpriteEditorWindowButtonSave", m_buttonSize))
        {
            saveData();
        }

        ImGui::Separator();

        ImGui::TextUnformatted("Properties:");

        if (ImGui::BeginChild("##SpriteEditorWindowChildProperties", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Name##SpriteEditorWindowInputName", &m_spriteData->Name);
            ImGui::InputText("Article##SpriteEditorWindowInputArticle", &m_spriteData->Article);
            ImGui::InputText("Description##SpriteEditorWindowInputDescription", &m_spriteData->Description);

            ImGui::InputText("Animation Name##SpriteEditorWindowInputAnimationName", &m_spriteData->AnimationName);

            ImGui::InputScalar("Tile Width##SpriteEditorWindowInputTileWidth", ImGuiDataType_U8, &m_spriteData->TileWidth, &tb::LibIMGUI::InputScalarU8Step1);
            ImGui::InputScalar("Tile Height##SpriteEditorWindowInputTileHeight", ImGuiDataType_U8, &m_spriteData->TileHeight, &tb::LibIMGUI::InputScalarU8Step1);

            ImGui::InputFloat("Weight##SpriteEditorWindowInputWeight", &m_spriteData->Weight, 1.0f, 10.0f, "%.2f");
            ImGui::InputFloat("Light Radius##SpriteEditorWindowInputLightRadius", &m_spriteData->LightRadius, 1.0f, 10.0f, "%.2f");

            ImGui::EndChild();
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

tb::SpriteID SpriteEditorWindow::getSelectedSpriteID()
{
    return m_selectedSpriteID;
}

void SpriteEditorWindow::setSelectedSpriteID(tb::SpriteID spriteID)
{
    m_selectedSpriteID = spriteID;
}

}
