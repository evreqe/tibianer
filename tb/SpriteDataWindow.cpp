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
    bool* isVisible = getIsVisible();

    ImGui::Begin("Sprite Data##SpriteDataWindow", isVisible, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (g_SpriteData.isLoaded() == false)
    {
        ImGui::Text("ERROR: g_SpriteData.isLoaded() == false");
        ImGui::End();

        return;
    }

    if (ImGui::BeginChild("##SpriteDataChild1", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        auto spriteDataList = g_SpriteData.getDataList();
        if (spriteDataList != nullptr)
        {
            ImGuiListClipper clipper;
            clipper.Begin(spriteDataList->size());

            while (clipper.Step())
            {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                {
                    tb::Sprite sprite;
                    sprite.setUseWidthAndHeight(false);
                    sprite.setID(i);

                    ImGui::ImageButton(sprite);

                    ImGui::Text(std::format("ID: {}", spriteDataList->at(i).SpriteID).c_str());

                    ImGui::Text(std::format("Sprite Flags: {}", spriteDataList->at(i).SpriteFlags.to_string()).c_str());

                    ImGui::Separator();
                }
            }
        }

        ImGui::EndChild();
    }

    ImGui::End();
}

}
