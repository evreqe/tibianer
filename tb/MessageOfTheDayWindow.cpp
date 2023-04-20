#include "tb/MessageOfTheDayWindow.h"

namespace tb
{

MessageOfTheDayWindow::MessageOfTheDayWindow()
{
    //
}

MessageOfTheDayWindow::~MessageOfTheDayWindow()
{
    //
}

void MessageOfTheDayWindow::onLoad()
{
    m_messageOfTheDayText = g_MessageOfTheDayData.getMessageOfTheDay();

    m_isLoaded = true;
}

void MessageOfTheDayWindow::draw()
{
    if (m_isLoaded == false)
    {
        onLoad();
    }

    center();

    bool* isVisible = getIsVisible();

    ImGui::Begin("Message of the Day##MessageOfTheDayWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    ImGui::TextUnformatted(m_messageOfTheDayText.c_str());

    auto windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX(ImGui::GetCursorPos().x + (windowWidth * 0.5f) - (m_buttonSize.x * 0.5f));

    if (ImGui::Button("OK##MessageOfTheDayWindowButtonOK", m_buttonSize))
    {
        setIsVisible(false);
    }

    ImGui::End();
}

}
