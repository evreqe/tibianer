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

    ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);

    bool* isVisible = getIsVisible();

    ImGui::Begin("Log##LogWindow", isVisible);

    ImGui::BeginChild("##LogWindowScrollableArea", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    const std::string logText = g_Log.getText();

    ImGui::TextUnformatted(logText.c_str());

    ImGui::EndChild();

    ImGui::End();
}

}
