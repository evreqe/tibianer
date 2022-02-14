#include "tb/SpriteDataWindow.h"

namespace tb
{

SpriteDataWindow::SpriteDataWindow()
{
    //
}

void SpriteDataWindow::draw()
{
    ImGui::Begin("Sprite Data##SpriteDataWindow", &m_isVisible, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (m_spriteData == nullptr)
    {
        ImGui::Text("ERROR: m_spriteData == nullptr");
        ImGui::End();

        return;
    }

    if (ImGui::BeginChild("##SpriteDataChild1", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        auto spriteDataList = m_spriteData->getDataList();
        if (spriteDataList != nullptr)
        {
            ImGuiListClipper clipper;
            clipper.Begin(spriteDataList->size());

            while (clipper.Step())
            {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                {
                    tb::Sprite spr;
                    spr.setUseWidthAndHeight(false);
                    spr.setID(i);

                    ImGui::ImageButton(spr);

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

void SpriteDataWindow::setSpriteData(tb::SpriteData& spriteData)
{
    m_spriteData = &spriteData;
}

bool SpriteDataWindow::getIsVisible()
{
    return m_isVisible;
}

void SpriteDataWindow::setIsVisible(bool b)
{
    m_isVisible = b;
}

void SpriteDataWindow::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

}
