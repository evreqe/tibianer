#include "tb/MenuBar.h"

namespace tb
{

MenuBar::MenuBar()
{
    setIsVisible(true);
}

MenuBar::~MenuBar()
{
    //
}

void MenuBar::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    tb::GameState gameState = g_Game.getGameState();

    tb::Game::Properties_t* gameProperties = g_Game.getProperties();

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    float renderWindowWidth = static_cast<float>(renderWindow->getSize().x);

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(renderWindowWidth, m_height));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    bool* isVisible = getIsVisible();

    ImGui::Begin("##MenuBarWindow", isVisible, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::PopStyleVar(2);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File##MenuItemFile"))
        {
            if (ImGui::MenuItem("Options...##MenuItemFileOptions", 0))
            {
                g_OptionsWindow.setIsVisible(true);
            }

            if (ImGui::MenuItem("Hotkeys...##MenuItemFileHotkeys", 0))
            {
                g_HotkeysWindow.setIsVisible(true);
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit (Bye bye)##MenuItemFileExit", 0))
            {
                renderWindow->close();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game##MenuItemGame"))
        {
            if (ImGui::MenuItem("Enter Game...##MenuItemGameEnterGame", 0, nullptr, gameState == tb::GameState::EnterGame))
            {
                g_EnterGameWindow.setIsVisible(true);
            }

            if (ImGui::MenuItem("End Game##MenuItemGameEndGame", 0, nullptr, gameState == tb::GameState::InGame))
            {
                gameProperties->ShowEndGamePopup = true;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Info##MenuItemInfo"))
        {
            if (ImGui::MenuItem("Set Outfit...##MenuItemInfoSetOutfit", 0, nullptr, gameState == tb::GameState::InGame))
            {
                g_SetOutfitWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Comments...##MenuItemInfoComments", 0, nullptr, isDebugModeEnabled == true))
            {
                g_CommentsWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Message of the Day...##MenuItemInfoMessageOfTheDay", 0))
            {
                g_MessageOfTheDayWindow.toggleIsVisible();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game Window##MenuItemGameWindow"))
        {
            ImGui::SeparatorText("Scale##MenuItemGameWindowSeparatorScale");

            if (ImGui::MenuItem("1x##MenuItemGameWindowScale1", 0))
            {
                g_GameWindow.setSizeScale(1.0f);
            }

            if (ImGui::MenuItem("2x##MenuItemGameWindowScale2", 0))
            {
                g_GameWindow.setSizeScale(2.0f);
            }

            if (ImGui::MenuItem("4x##MenuItemGameWindowScale3", 0))
            {
                g_GameWindow.setSizeScale(4.0f);
            }

            ImGui::SeparatorText("Light Brightness##MenuItemGameWindowSeparatorLightBrightness");

            static int lightBrightness = tb::LightBrightness::Max;
            if (ImGui::DragInt("##MenuItemGameWindowDragIntLightBrightness", &lightBrightness, 1.0f, tb::LightBrightness::Min, tb::LightBrightness::Max))
            {
                g_GameWindow.setLightBrightness(lightBrightness);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Render Window##MenuItemRenderWindow"))
        {
            ImGui::SeparatorText("4:3##MenuItemRenderWindowResolutionSeparator4by3");

            if (ImGui::MenuItem("640x480##MenuItemRenderWindowResolution1", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(640, 480));
            }

            if (ImGui::MenuItem("800x600##MenuItemRenderWindowResolution2", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(800, 600));
            }

            if (ImGui::MenuItem("1024x768##MenuItemRenderWindowResolution3", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(1024, 768));
            }

            ImGui::SeparatorText("16:9##MenuItemRenderWindowResolutionSeparator16by9");

            if (ImGui::MenuItem("720p##MenuItemRenderWindowResolution4", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(1280, 720));
            }

            if (ImGui::MenuItem("1080p##MenuItemRenderWindowResolution5", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(1920, 1080));
            }

            if (ImGui::MenuItem("1440p##MenuItemRenderWindowResolution6", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(2560, 1440));
            }

            if (ImGui::MenuItem("4k##MenuItemRenderWindowResolution7", 0))
            {
                g_RenderWindow.setSizeAndCenter(sf::Vector2u(2160, 3840));
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("User Interface##MenuItemUserInterface"))
        {
            ImGui::SeparatorText("Scale##MenuItemUserInterfaceSeparatorScale");

            if (ImGui::MenuItem("1x##MenuItemUserInterfaceScale1", 0))
            {
                g_Game.setSizeScaleForSfmlWindows(1.0f);
            }

            if (ImGui::MenuItem("2x##MenuItemUserInterfaceScale2", 0))
            {
                g_Game.setSizeScaleForSfmlWindows(2.0f);
            }

            if (ImGui::MenuItem("4x##MenuItemUserInterfaceScale3", 0))
            {
                g_Game.setSizeScaleForSfmlWindows(4.0f);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Gamepad Controller##MenuItemGamepadController"))
        {
            for (unsigned int i = 0; i < sf::Joystick::Count; i++)
            {
                if (sf::Joystick::isConnected(i) == true)
                {
                    tb::JoystickList* joystickList = g_Game.getJoystickList();

                    tb::Joystick::Properties_t* joystickProperties = joystickList->at(i).getProperties();

                    std::string joystickMenuItemText = std::format("{}: {}##MenuItemGamepadControllerIndex{}", i, joystickProperties->Name, i);

                    bool isChecked = i == g_Game.getJoystickIndex();

                    if (ImGui::MenuItem(joystickMenuItemText.c_str(), 0, isChecked))
                    {
                        g_Game.setJoystickIndex(i);
                    }
                }
                else
                {
                    std::string joystickMenuItemText = std::format("{}: (Disconnected)##MenuItemGamepadControllerIndex{}", i, i);

                    ImGui::MenuItem(joystickMenuItemText.c_str(), 0, false, false);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Developer##MenuItemDeveloper"))
        {
            if (ImGui::MenuItem("Debug Mode##MenuItemDeveloperDebugMode", 0, isDebugModeEnabled == true))
            {
                g_Game.toggleDebugMode();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Sprite Editor...##MenuItemDeveloperSpriteEditor", 0))
            {
                g_SpriteEditorWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Sprite Data...##MenuItemDeveloperSpriteData", 0))
            {
                g_SpriteDataWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Map Generator...##MenuItemDeveloperMapGeneratorWindow", 0))
            {
                g_MapGeneratorWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Overlay...##MenuItemDeveloperOverlayWindow", 0, nullptr, gameState == tb::GameState::InGame))
            {
                g_OverlayWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Log...##MenuItemDeveloperLogWindow", 0))
            {
                g_LogWindow.toggleIsVisible();
            }

            ImGui::SeparatorText("Game State##MenuItemDeveloperSeparatorGameState");

            if (ImGui::MenuItem("InGame##MenuItemDeveloperGameStateInGame", 0))
            {
                g_Game.setGameState(tb::GameState::InGame);
            }

            if (ImGui::MenuItem("Testing##MenuItemDeveloperGameStateTesting", 0))
            {
                g_Game.setGameState(tb::GameState::Testing);
            }

            ImGui::SeparatorText("ImGui##MenuItemDeveloperSeparatorImGui");

            if (ImGui::MenuItem("Light Mode##MenuItemDeveloperGUILightMode", 0))
            {
                ImGui::StyleColorsLight();
            }

            if (ImGui::MenuItem("Dark Mode##MenuItemDeveloperGUIDarkMode", 0))
            {
                ImGui::StyleColorsDark();
            }

            if (ImGui::MenuItem("Classic Mode##MenuItemDeveloperGUIClassicMode", 0))
            {
                ImGui::StyleColorsClassic();
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
            if (ImGui::MenuItem("Connection...##MenuItemHelpConnection", 0, nullptr, isDebugModeEnabled == true))
            {
                g_ConnectionWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Controls...##MenuItemHelpControls", 0))
            {
                g_ControlsWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("Tips & Tricks...##MenuItemHelpTipsAndTricks", 0))
            {
                g_TipsAndTricksWindow.toggleIsVisible();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("About Tibia...##MenuItemHelpAboutTibia", 0))
            {
                g_AboutTibiaWindow.toggleIsVisible();
            }

            if (ImGui::MenuItem("About Tibianer...##MenuItemHelpAboutTibianer", 0))
            {
                g_AboutTibianerWindow.toggleIsVisible();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

float MenuBar::getHeight()
{
    if (*getIsVisible() == false)
    {
        return 0.0f;
    }

    return m_height;
}

void MenuBar::setHeight(float height)
{
    m_height = height;
}

}
