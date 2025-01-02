#include "tb/AboutTibiaWindow.h"

namespace tb
{

AboutTibiaWindow::AboutTibiaWindow()
{
    //
}

AboutTibiaWindow::~AboutTibiaWindow()
{
    //
}

void AboutTibiaWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("About Tibia...##AboutTibiaWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    if (ImGui::BeginTable("##AboutTibiaWindowTable", 3, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        tb::Sprite sprite(tb::Textures::Sprites);
        sprite.setID(tb::Sprites::TbIconLarge);

        ImGui::Image(sprite);

        ImGui::TableSetColumnIndex(1);

        ImGui::TextUnformatted(m_displayText);

        ImGui::Spacing();

        std::string textLinkLabel = std::format("{}##AboutTibiaWindowTextLink", m_textLinkURL);

        ImGui::TextLinkOpenURL(textLinkLabel.c_str(), m_textLinkURL);
        if (ImGui::IsMouseHoveringRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()) == true)
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        }

        ImGui::Spacing();

        ImGui::TableSetColumnIndex(2);

        ImGui::Image(sprite);

        ImGui::EndTable();
    }

    float windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth / 2.0f) - (m_buttonSize.x / 2.0f));

    if (ImGui::Button("OK##AboutTibiaWindowButtonOK", m_buttonSize))
    {
        setIsVisible(false);
    }

    ImGui::End();
}

}
