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
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: Sprite data is not loaded");
        return;
    }

    centerOnFirstUseEver();

    ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);

    bool* isVisible = getIsVisible();

    ImGui::Begin("Sprite Data##SpriteDataWindow", isVisible, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (ImGui::BeginChild("##SpriteDataWindowChild1", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        tb::SpriteData::DataList* spriteDataList = g_SpriteData.getDataList();
        if (spriteDataList != nullptr)
        {
            ImGuiListClipper clipper;
            clipper.Begin(spriteDataList->size());

            while (clipper.Step())
            {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                {
                    tb::Sprite sprite;
                    sprite.setID(static_cast<tb::SpriteID_t>(i));

                    ImGui::ImageButton(sprite);

                    tb::SpriteData::Data* spriteData = &spriteDataList->at(i);

                    ImGui::TextUnformatted(std::format("ID: {}", spriteData->SpriteID).c_str());

                    ImGui::TextUnformatted(std::format("Name: {}", spriteData->Name).c_str());
                    ImGui::TextUnformatted(std::format("Article: {}", spriteData->Article).c_str());
                    ImGui::TextUnformatted(std::format("Description: {}", spriteData->Description).c_str());

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
        }

        ImGui::EndChild();
    }

    ImGui::End();
}

}
