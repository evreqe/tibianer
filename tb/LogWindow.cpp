#include "common.h"

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

    bool* pIsVisible = isVisible();

    ImGui::Begin("Log##LogWindow", pIsVisible, ImGuiWindowFlags_NoScrollbar);

    ImGui::BeginChild("##LogWindowChildText", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);

    const std::string logText = g_Log.getText();

    ImGui::TextUnformatted(logText.c_str());

    tb::LibIMGUI::scrollWindowWithMiddleMouseButton();

    ImGui::EndChild();

    ImGui::End();
}

}
