#include "common.h"

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

    bool* pIsVisible = isVisible();

    ImGui::Begin("Comments##CommentsWindow", pIsVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted(m_displayText);

    ImGui::InputTextMultiline("##CommentsWindowInputText", &m_inputText, m_inputTextSize, ImGuiInputTextFlags_NoHorizontalScroll);

    if (ImGui::BeginTable("##CommentsWindowTable", 3, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        if (ImGui::Button("Send##CommentsWindowButtonSend", m_buttonSize))
        {
            setVisible(false);
        }

        ImGui::TableSetColumnIndex(1);

        ImGui::TextUnformatted("Thank you !");

        ImGui::TableSetColumnIndex(2);

        if (ImGui::Button("Cancel##CommentsWindowButtonCancel", m_buttonSize))
        {
            setVisible(false);
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

}
