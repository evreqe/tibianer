#include "tb/OverlayWindow.h"

namespace tb
{

    OverlayWindow::OverlayWindow()
    {
        //
    }

    OverlayWindow::~OverlayWindow()
    {
        //
    }

    std::vector<std::string>* OverlayWindow::getTextList()
    {
        return &m_textList;
    }

    void OverlayWindow::clearTextList()
    {
        m_textList.clear();
    }

    void OverlayWindow::addTextToList(const std::string& text)
    {
        m_textList.push_back(text);
    }

    void OverlayWindow::draw()
    {
        ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(m_windowBackgroundAlpha);

        bool* isVisible = getIsVisible();

        ImGui::Begin("##OverlayWindow", isVisible, m_windowFlags);

        for (auto& text : m_textList)
        {
            ImGui::TextUnformatted(text.c_str());
        }

        ImGui::End();
    }

}
