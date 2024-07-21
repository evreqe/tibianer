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
    centerOnFirstUseEver();

    ImGui::SetNextWindowSize(m_windowSize, ImGuiCond_FirstUseEver);

    bool* isVisible = getIsVisible();

    ImGui::Begin("Log##LogWindow", isVisible, ImGuiWindowFlags_NoScrollbar);

    ImGui::BeginChild("##LogWindowChildText", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);

    const std::string logText = g_Log.getText();

    ImGui::TextUnformatted(logText.c_str());

    ImGui::EndChild();

    ImGui::End();
}

}
