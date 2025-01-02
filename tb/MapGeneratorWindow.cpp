#include "tb/MapGeneratorWindow.h"

namespace tb
{

MapGeneratorWindow::MapGeneratorWindow()
{
    //
}

MapGeneratorWindow::~MapGeneratorWindow()
{
    //
}

void MapGeneratorWindow::onLoad()
{
   // TODO

    m_isLoaded = true;
}

void MapGeneratorWindow::draw()
{
    if (m_isLoaded == false)
    {
        onLoad();
    }

    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Map Generator##MapGeneratorWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted("Image:");
    if (ImGui::BeginListBox("##MapGeneratorWindowListBoxData", ImVec2(m_listBoxWidth, 10.0f * ImGui::GetTextLineHeightWithSpacing())))
    {
        std::uint32_t fileIndex = 0;

        for (const auto& directoryEntry : std::filesystem::directory_iterator(m_imageFolder))
        {
            if (directoryEntry.is_regular_file() == true)
            {
                if (directoryEntry.path().extension().string() == m_imageFileNameExtension)
                {
                    std::string fileName = directoryEntry.path().filename().string();

                    const bool isSelected = (m_selectedListBoxIndex == fileIndex);

                    std::string listText = std::format("{}##MapGeneratorWindowSelectable{}", fileName, fileIndex);

                    if (ImGui::Selectable(listText.c_str(), isSelected))
                    {
                        m_selectedListBoxIndex = fileIndex;
                    }

                    if (isSelected == true)
                    {
                        ImGui::SetItemDefaultFocus();

                        m_selectedImageFileName = fileName;
                    }

                    fileIndex++;
                }
            }
        }

        ImGui::EndListBox();
    }

    ImGui::TextUnformatted("Name:");
    ImGui::SetNextItemWidth(m_inputTextWidth);
    ImGui::InputText("##MapGeneratorWindowInputMapName", &m_map.Name);

    ImGui::TextUnformatted("Description:");
    ImGui::SetNextItemWidth(m_inputTextWidth);
    ImGui::InputText("##MapGeneratorWindowInputMapDescription", &m_map.Description);

    ImGui::TextUnformatted("Author:");
    ImGui::SetNextItemWidth(m_inputTextWidth);
    ImGui::InputText("##MapGeneratorWindowInputMapAuthor", &m_map.Author);

    ImGui::TextUnformatted("Player Start X:");
    ImGui::InputInt("##MapGeneratorWindowInputMapPlayerStartX", (int*)&m_map.PlayerStartX, 1, tb::Constants::TileSize);

    ImGui::TextUnformatted("Player Start Y:");
    ImGui::InputInt("##MapGeneratorWindowInputMapPlayerStartY", (int*)&m_map.PlayerStartY, 1, tb::Constants::TileSize);

    ImGui::TextUnformatted("Player Start Z:");
    ImGui::SliderInt("##MapGeneratorWindowInputMapPlayerStartZ", (int*)&m_map.PlayerStartZ, tb::ZAxis::Min, tb::ZAxis::Max);

    if (ImGui::Button("Generate##MapGeneratorWindowButtonGenerate", m_buttonSize))
    {
        if (m_map.Name.size() != 0)
        {
            std::string outputFileName = m_selectedImageFileName;
            outputFileName = tb::Utility::String::replaceAll(outputFileName, ".png", ".tmx");

            g_MapGenerator.generateMapFromImageFile(m_map, m_selectedImageFileName, outputFileName);
        }
    }

    float windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth / 2.0f) - (m_buttonSize.x / 2.0f));

    if (ImGui::Button("OK##MapGeneratorWindowButtonOK", m_buttonSize))
    {
        setIsVisible(false);
    }

    ImGui::End();
}

}
