#include "tb/MenuBar.h"

namespace tb
{

MenuBar::MenuBar()
{
    //
}

MenuBar::~MenuBar()
{
    //
}

void MenuBar::draw()
{
    if (m_isVisible == false)
    {
        return;
    }

    tb::GameState gameState = g_Game.getGameState();

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    float renderWinndowWidth = static_cast<float>(renderWindow->getSize().x);

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(renderWinndowWidth, m_height));

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
            if (ImGui::MenuItem("Hotkeys...##MenuItemFileHotkeys", 0)) {}

            ImGui::Separator();

            if (ImGui::MenuItem("Exit (Bye bye)##MenuItemFileExit", 0))
            {
                renderWindow->close();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game##MenuItemGame"))
        {
            if (ImGui::MenuItem("Enter Game...##MenuItemGameEnterGame", 0, false, gameState == tb::GameState::EnterGame))
            {
                g_EnterGameWindow.setIsVisible(true);
            }

            if (ImGui::MenuItem("End Game##MenuItemGameEndGame", 0, false, gameState == tb::GameState::InGame))
            {
                g_Game.endGame();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Info##MenuItemInfo"))
        {
            if (ImGui::MenuItem("Set Outfit...##MenuItemInfoSetOutfit", 0, false, gameState == tb::GameState::InGame)) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window##MenuItemWindow"))
        {
            if (ImGui::MenuItem("4:3 640x480##MenuItemWindowResolution1", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(640, 480));
            }

            if (ImGui::MenuItem("4:3 800x600##MenuItemWindowResolution2", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(800, 600));
            }

            if (ImGui::MenuItem("4:3 1024x768##MenuItemWindowResolution3", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(1024, 768));
            }

            ImGui::Separator();

            if (ImGui::MenuItem("16:9 720p##MenuItemWindowResolution4", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(1280, 720));
            }

            if (ImGui::MenuItem("16:9 1080p##MenuItemWindowResolution5", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(1920, 1080));
            }

            if (ImGui::MenuItem("16:9 1440p##MenuItemWindowResolution6", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(2560, 1440));
            }

            if (ImGui::MenuItem("16:9 4k##MenuItemWindowResolution7", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(2160, 3840));
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Developer##MenuItemDeveloper"))
        {
            if (ImGui::MenuItem("Sprite Editor...##MenuItemDeveloperSpriteEditor", 0))
            {
                g_SpriteEditorWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Sprite Data...##MenuItemDeveloperSpriteData", 0))
            {
                g_SpriteDataWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Overlay...##MenuItemDeveloperOverlayWindow", 0, false, gameState == tb::GameState::InGame))
            {
                g_OverlayWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Log...##MenuItemDeveloperLogWindow", 0))
            {
                g_LogWindow.toggleIsVisible();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Demo Window...##MenuItemDeveloperDemoWindow", 0))
            {
                g_Game.toggleDemoWindow();
            }

            if (ImGui::MenuItem("Stack Tool Window...##MenuItemDeveloperStackToolWindow", 0))
            {
                g_Game.toggleStackToolWindow();
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
