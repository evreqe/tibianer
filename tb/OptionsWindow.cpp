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

void OptionsWindow::onOpen()
{
    loadData();

    m_isOpen = true;
}

void OptionsWindow::onClose()
{
    m_isOpen = false;
}

void OptionsWindow::loadData()
{
    m_optionsData = *g_OptionsData.getData();
}

void OptionsWindow::saveData()
{
    g_OptionsData.setData(m_optionsData);

    g_OptionsData.save();
}

void OptionsWindow::draw()
{
    if (m_isOpen == false)
    {
        onOpen();
    }

    center();

    bool* isVisible = getIsVisible();

    //ImGui::SetNextWindowSizeConstraints(m_windowSize, ImVec2(FLT_MAX, FLT_MAX));

    ImGui::Begin("Options##OptionsWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    if (ImGui::BeginTabBar("##OptionsWindowTabBar", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton))
    {
        if (ImGui::BeginTabItem("Player##OptionsWindowTabItemPlayer"))
        {
            ImGui::BeginChild("child", m_tabChildSize, false, ImGuiWindowFlags_HorizontalScrollbar);

            ImGui::TextUnformatted("Name:");
            ImGui::SameLine();
            ImGui::InputText("##OptionsWindowInputPlayerName", &m_optionsData.PlayerName);

            std::string outfitText = std::format("{}, {}, {}, {}", m_optionsData.PlayerOutfitHead, m_optionsData.PlayerOutfitBody, m_optionsData.PlayerOutfitLegs, m_optionsData.PlayerOutfitFeet);

            ImGui::TextUnformatted("Outfit:");
            ImGui::SameLine();
            ImGui::TextUnformatted(outfitText.c_str());

            //ImGui::InputInt("##OptionsWindowInputPlayerOutfitHead", (int*)&m_optionsData.PlayerOutfitHead);

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Window##OptionsWindowTabItemWindow"))
        {
            ImGui::BeginChild("child", m_tabChildSize, false, ImGuiWindowFlags_HorizontalScrollbar);

            ImGui::TextUnformatted("Start Maximized:");
            ImGui::SameLine();
            //ImGui::Checkbox("##OptionsWindowCheckboxWindowStartMaximized", 0);
            ImGui::TextUnformatted("TODO");

            ImGui::TextUnformatted("Frame Rate Limit:");
            ImGui::SameLine();
            //ImGui::InputInt("##OptionsWindowInputIntWindowFrameRateLimit", 0);
            ImGui::TextUnformatted("TODO");

            ImGui::TextUnformatted("Vertical Sync:");
            ImGui::SameLine();
            //ImGui::Checkbox("##OptionsWindowCheckboxWindowVerticalSync", 0);
            ImGui::TextUnformatted("TODO");

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::Separator();

    if (ImGui::Button("OK##OptionsWindowButtonOK", m_buttonSize))
    {
        saveData();

        onClose();

        setIsVisible(false);
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel##OptionsWindowButtonCancel", m_buttonSize))
    {
        onClose();

        setIsVisible(false);
    }

    ImGui::End();
}

}
