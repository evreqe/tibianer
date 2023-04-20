#include "tb/OptionsWindow.h"

namespace tb
{

OptionsWindow::OptionsWindow()
{
    //
}

OptionsWindow::~OptionsWindow()
{
    //
}

void OptionsWindow::load()
{
    m_inputPlayerName = g_OptionsData.getData()->PlayerName;
}

void OptionsWindow::save()
{
    //
}

void OptionsWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Options##OptionsWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    if (ImGui::BeginTable("##OptionsWindowTable", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        ImGui::TextUnformatted("Player Data:");

        ImGui::TextUnformatted("Name:");

        ImGui::TableSetColumnIndex(1);

        ImGui::TextUnformatted(" ");

        ImGui::InputText("##OptionsWindowPlayerName", &m_inputPlayerName);

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::TextUnformatted("Options:");

        ImGui::TableSetColumnIndex(1);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        static bool isChecked = false;

        ImGui::Checkbox("No stretching", &isChecked);

        ImGui::Checkbox("Text console", &isChecked);

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("OK##OptionsWindowButtonOK", m_buttonSize))
        {
            // TODO: save

            setIsVisible(false);
        }

        ImGui::TableSetColumnIndex(1);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Cancel##OptionsWindowButtonCancel", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

}
