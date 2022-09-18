#include "tb/LogWindow.h"

namespace tb
{

LogWindow::LogWindow()
{
    //
}

LogWindow::~LogWindow()
{
    //
}

void LogWindow::draw()
{
    bool* isVisible = getIsVisible();

    ImGui::Begin(m_titleText.c_str(), isVisible);

    ImGui::BeginChild("##LogWindowScrollableArea", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    std::string logText = g_Log.getText();

    ImGui::TextUnformatted(logText.c_str());

    ImGui::EndChild();

    ImGui::End();
}

}
