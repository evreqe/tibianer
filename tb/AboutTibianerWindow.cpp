#include "tb/AboutTibianerWindow.h"

namespace tb
{

    AboutTibianerWindow::AboutTibianerWindow()
    {
        //
    }

    AboutTibianerWindow::~AboutTibianerWindow()
    {
        //
    }

    void AboutTibianerWindow::draw()
    {
        center();

        bool* isVisible = getIsVisible();

        ImGui::Begin("About Tibianer...##AboutTibianerWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

        if (ImGui::BeginTable("##AboutTibianerWindowTable", 3, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            tb::Sprite sprite;
            sprite.setID(tb::Sprites::Evremonde);

            ImGui::Image(sprite);

            ImGui::TableSetColumnIndex(1);

            ImGui::TextUnformatted(m_displayText);

            ImGui::TableSetColumnIndex(2);

            ImGui::Image(sprite);

            ImGui::EndTable();
        }

        auto windowWidth = ImGui::GetWindowSize().x;

        ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth * 0.5f) - (m_buttonSize.x * 0.5f));

        if (ImGui::Button("OK##AboutTibianerWindowButtonOK", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::End();
    }

}
