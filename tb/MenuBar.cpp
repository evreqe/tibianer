#include "common.h"

#include "tb/MenuBar.h"

namespace tb
{

MenuBar::MenuBar()
{
    setVisible(true);
}

MenuBar::~MenuBar()
{
    //
}

void MenuBar::draw()
{
    bool isDebugModeEnabled = g_Game.isDebugModeEnabled();

    tb::GameState gameState = g_Game.getGameState();

    tb::GUI::Properties* GUIProperties = g_GUI.getProperties();

    sf::RenderWindow* renderWindow = g_RenderWindow.getWindow();

    float renderWindowWidth = static_cast<float>(renderWindow->getSize().x);

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(renderWindowWidth, m_height));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    bool* pIsVisible = isVisible();

    ImGui::Begin("##MenuBarWindow", pIsVisible, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::PopStyleVar(2);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File##MenuItemFile"))
        {
            if (ImGui::MenuItem("Options...##MenuItemFileOptions", 0))
            {
                g_OptionsWindow.setVisible(true);
            }

            if (ImGui::MenuItem("Hotkeys...##MenuItemFileHotkeys", 0))
            {
                g_HotkeysWindow.setVisible(true);
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
                g_EnterGameWindow.setVisible(true);
            }

            if (ImGui::MenuItem("End Game##MenuItemGameEndGame", 0, nullptr, gameState == tb::GameState::InGame))
            {
                GUIProperties->ShowEndGamePopup = true;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Info##MenuItemInfo"))
        {
            if (ImGui::MenuItem("Set Outfit...##MenuItemInfoSetOutfit", 0, nullptr, gameState == tb::GameState::InGame))
            {
                g_SetOutfitWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Comments...##MenuItemInfoComments", 0, nullptr, isDebugModeEnabled == true))
            {
                g_CommentsWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Message of the Day...##MenuItemInfoMessageOfTheDay", 0))
            {
                g_MessageOfTheDayWindow.toggleVisible();
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

            static int lightBrightness = tb::Constants::LightBrightnessMax;
            if (ImGui::DragInt("##MenuItemGameWindowDragIntLightBrightness", &lightBrightness, 1.0f, tb::Constants::LightBrightnessMin, tb::Constants::LightBrightnessMax))
            {
                g_GameWindow.setLightBrightness(lightBrightness);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Render Window##MenuItemRenderWindow"))
        {
            ImGui::SeparatorText("Frames Per Second##MenuItemRenderWindowFramesPerSecondSeparator");

            if (ImGui::MenuItem("10 FPS##MenuItemRenderWindowFramesPerSecond1", 0))
            {
                g_RenderWindow.getWindow()->setFramerateLimit(10);
            }

            if (ImGui::MenuItem("30 FPS##MenuItemRenderWindowFramesPerSecond2", 0))
            {
                g_RenderWindow.getWindow()->setFramerateLimit(30);
            }

            if (ImGui::MenuItem("60 FPS##MenuItemRenderWindowFramesPerSecond3", 0))
            {
                g_RenderWindow.getWindow()->setFramerateLimit(60);
            }

            if (ImGui::MenuItem("120 FPS##MenuItemRenderWindowFramesPerSecond4", 0))
            {
                g_RenderWindow.getWindow()->setFramerateLimit(120);
            }

            if (ImGui::MenuItem("240 FPS##MenuItemRenderWindowFramesPerSecond5", 0))
            {
                g_RenderWindow.getWindow()->setFramerateLimit(240);
            }

            ImGui::SeparatorText("Resolution 4:3##MenuItemRenderWindowResolutionSeparator4by3");

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

            ImGui::SeparatorText("Resolution 16:9##MenuItemRenderWindowResolutionSeparator16by9");

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
                g_GUI.SFMLWindows_setSizeScale(1.0f);
            }

            if (ImGui::MenuItem("2x##MenuItemUserInterfaceScale2", 0))
            {
                g_GUI.SFMLWindows_setSizeScale(2.0f);
            }

            if (ImGui::MenuItem("4x##MenuItemUserInterfaceScale3", 0))
            {
                g_GUI.SFMLWindows_setSizeScale(4.0f);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Gamepad Controller##MenuItemGamepadController"))
        {
            for (unsigned int i = 0; i < sf::Joystick::Count; i++)
            {
                if (sf::Joystick::isConnected(i) == true)
                {
                    tb::JoystickList* joystickList = g_JoystickManager.getJoystickList();

                    tb::Joystick::Properties* joystickProperties = joystickList->at(i).getProperties();

                    std::string joystickMenuItemText = std::format("{}: {}##MenuItemGamepadControllerIndex{}", i, joystickProperties->Name, i);

                    bool isChecked = i == g_JoystickManager.getJoystickIndex();

                    if (ImGui::MenuItem(joystickMenuItemText.c_str(), 0, isChecked))
                    {
                        g_JoystickManager.setJoystickIndex(i);
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
                g_SpriteEditorWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Sprite Data...##MenuItemDeveloperSpriteData", 0))
            {
                g_SpriteDataWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Map Generator...##MenuItemDeveloperMapGeneratorWindow", 0))
            {
                g_MapGeneratorWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Overlay...##MenuItemDeveloperOverlayWindow", 0, nullptr, gameState == tb::GameState::InGame))
            {
                g_OverlayWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Log...##MenuItemDeveloperLogWindow", 0))
            {
                g_LogWindow.toggleVisible();
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
                g_GUI.toggleDemoWindow();
            }

            if (ImGui::MenuItem("Stack Tool Window...##MenuItemDeveloperStackToolWindow", 0))
            {
                g_GUI.toggleStackToolWindow();
            }

            ImGui::EndMenu();
        }

        // apply right-justify alignment
        ImGui::SetCursorPosX(renderWindow->getSize().x - m_helpMenuAlignmentOffset);

        if (ImGui::BeginMenu("Help##MenuItemHelp"))
        {
            if (ImGui::MenuItem("Connection...##MenuItemHelpConnection", 0, nullptr, isDebugModeEnabled == true))
            {
                g_ConnectionWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Controls...##MenuItemHelpControls", 0))
            {
                g_ControlsWindow.toggleVisible();
            }

            if (ImGui::MenuItem("Tips & Tricks...##MenuItemHelpTipsAndTricks", 0))
            {
                g_TipsAndTricksWindow.toggleVisible();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("About Tibia...##MenuItemHelpAboutTibia", 0))
            {
                g_AboutTibiaWindow.toggleVisible();
            }

            if (ImGui::MenuItem("About Tibianer...##MenuItemHelpAboutTibianer", 0))
            {
                g_AboutTibianerWindow.toggleVisible();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

float MenuBar::getHeight()
{
    bool* pIsVisible = isVisible();

    if (*pIsVisible == false)
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
