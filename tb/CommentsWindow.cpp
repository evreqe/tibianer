#include "tb/CommentsWindow.h"

namespace tb
{

CommentsWindow::CommentsWindow()
{
    //
}

CommentsWindow::~CommentsWindow()
{
    //
}

void CommentsWindow::draw()
{
    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Comments##CommentsWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted(m_displayText);

    ImGui::InputTextMultiline("##CommentsWindowInputText", &m_inputText, m_inputTextSize, ImGuiInputTextFlags_NoHorizontalScroll);

    if (ImGui::BeginTable("##CommentsWindowTable", 3, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("Send##CommentsWindowButtonSend", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::TableSetColumnIndex(1);

        ImGui::TextUnformatted("Thank you !");

        ImGui::TableSetColumnIndex(2);

        if (ImGui::Button("Cancel##CommentsWindowButtonCancel", m_buttonSize))
        {
            setIsVisible(false);
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

}
