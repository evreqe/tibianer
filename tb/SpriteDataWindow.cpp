#include "tb/SpriteDataWindow.h"

namespace tb
{

SpriteDataWindow::SpriteDataWindow()
{
    //
}

SpriteDataWindow::~SpriteDataWindow()
{
    //
}

void SpriteDataWindow::draw()
{
    centerOnFirstUseEver();

    ImGui::SetNextWindowSize(m_windowSize, ImGuiCond_FirstUseEver);

    bool* isVisible = getIsVisible();

    ImGui::Begin("Sprite Data##SpriteDataWindow", isVisible, ImGuiWindowFlags_NoScrollbar);

    if (ImGui::BeginChild("##SpriteDataWindowChildData", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();

        ImGuiListClipper clipper;
        clipper.Begin(static_cast<int>(spriteDataList->size()));

        while (clipper.Step())
        {
            for (std::int32_t i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            {
                tb::Sprite sprite(tb::Textures::Sprites);
                sprite.setID(static_cast<tb::SpriteID_t>(i));

                std::string imageButtonID = std::format("##SpriteDataWindowChildDataButton{}", i);

                ImGui::ImageButton(imageButtonID.c_str(), sprite, sf::Vector2f(tb::Constants::SpriteSizeAsFloat, tb::Constants::SpriteSizeAsFloat));

                tb::SpriteData::Data* spriteData = &spriteDataList->at(i);

                ImGui::TextUnformatted(std::format("ID: {}", spriteData->SpriteID).c_str());

                ImGui::TextUnformatted(std::format("Name: {}", spriteData->Name).c_str());
                ImGui::TextUnformatted(std::format("Article: {}", spriteData->Article).c_str());
                ImGui::TextUnformatted(std::format("Description: {}", spriteData->Description).c_str());

                ImGui::TextUnformatted(std::format("Animation Name: {}", spriteData->AnimationName).c_str());

                ImGui::TextUnformatted(std::format("Tile Size: {}x{}", spriteData->TileWidth, spriteData->TileHeight).c_str());

                tb::SpriteFlags* spriteFlags = &spriteData->SpriteFlags;

                ImGui::TextUnformatted(std::format("Sprite Flags: {}", spriteFlags->getCount()).c_str());

                for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
                {
                    if (spriteFlags->hasFlag(spriteFlag) == true)
                    {
                        ImGui::TextUnformatted(std::format("----> {}", spriteFlagName).c_str());
                    }
                }

                ImGui::Separator();
            }
        }

        ImGui::EndChild();
    }

    ImGui::End();
}

}
