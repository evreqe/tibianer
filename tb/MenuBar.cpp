#include "tb/MenuBar.h"

namespace tb
{

MenuBar::MenuBar()
{
    //
}

void MenuBar::draw(tb::Game* game)
{
    if (m_isVisible == false)
    {
        return;
    }

    auto renderWindow = game->getRenderWindow();

    bool isInGame = (game->getGameState() == tb::GameState::InGame);

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(renderWindow->getSize().x, m_height));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    bool isVisible = true;
    ImGui::Begin("##MenuBar", &isVisible, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::PopStyleVar(2);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File##MenuItemFile"))
        {
            if (ImGui::MenuItem("Options...##MenuItemFileOptions", 0)) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Exit##MenuItemFileExit", 0))
            {
                renderWindow->close();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game##MenuItemGame"))
        {
            if (ImGui::MenuItem("Enter Game...##MenuItemGameEnterGame", 0, false, isInGame == false))
            {
                //
            }

            if (ImGui::MenuItem("End Game##MenuItemGameEndGame", 0, false, isInGame))
            {
                //
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Info##MenuItemInfo"))
        {
            if (ImGui::MenuItem("Set Outfit...##MenuItemInfoSetOutfit", 0, false, isInGame)) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Developer##MenuItemDeveloper"))
        {
            if (ImGui::MenuItem("Sprite Editor...##MenuItemDeveloperSpriteEditor", 0))
            {
                game->toggleSpriteEditorWindow();
            }

            if (ImGui::MenuItem("Sprite Data...##MenuItemDeveloperSpriteData", 0))
            {
                game->toggleSpriteDataWindow();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Demo Window...##MenuItemDeveloperDemoWindow", 0))
            {
                game->toggleDemoWindow();
            }

            if (ImGui::MenuItem("Stack Tool Window...##MenuItemDeveloperStackToolWindow", 0))
            {
                game->toggleStackToolWindow();
            }

            ImGui::EndMenu();
        }

        // apply right-justify alignment
        ImGui::SetCursorPosX(renderWindow->getSize().x - m_helpMenuAlignmentOffset);

        if (ImGui::BeginMenu("Help##MenuItemHelp"))
        {
            if (ImGui::MenuItem("Controls...##MenuItemHelpControls", 0)) {}
            ImGui::Separator();
            if (ImGui::MenuItem("About Tibianer...##MenuItemHelpAboutTibianer", 0)) {}
            if (ImGui::MenuItem("About Tibia...##MenuItemHelpAboutTibia", 0)) {}
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

float MenuBar::getHeight()
{
    if (m_isVisible == false)
    {
        return 0.0f;
    }

    return m_height;
}

void MenuBar::setHeight(float height)
{
    m_height = height;
}

bool MenuBar::getIsVisible()
{
    return m_isVisible;
}

void MenuBar::setIsVisible(bool b)
{
    m_isVisible = b;
}

void MenuBar::toggleIsVisible()
{
    m_isVisible = !m_isVisible;
}

}
