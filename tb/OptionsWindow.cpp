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

    ImGui::Begin("Options##OptionsWindow", isVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

    if (ImGui::BeginTabBar("##OptionsWindowTabBar", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton))
    {
        if (ImGui::BeginTabItem("Player##OptionsWindowTabItemPlayer"))
        {
            ImGui::BeginChild("##OptionsWindowTabChildPlayer", m_tabChildSize);

            ImGui::TextUnformatted("Name:");
            ImGui::InputText("##OptionsWindowInputPlayerName", &m_optionsData.PlayerName);

            std::string outfitText = std::format("Outfit: {}, {}, {}, {}", m_optionsData.PlayerOutfitHead, m_optionsData.PlayerOutfitBody, m_optionsData.PlayerOutfitLegs, m_optionsData.PlayerOutfitFeet);

            ImGui::TextUnformatted(outfitText.c_str());

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Window##OptionsWindowTabItemWindow"))
        {
            ImGui::BeginChild("##OptionsWindowTabChildWindow", m_tabChildSize);

            ImGui::Checkbox("Start Maximized##OptionsWindowCheckboxWindowStartMaximized", &m_optionsData.WindowStartMaximized);
            ImGui::Checkbox("Vertical Sync##OptionsWindowCheckboxWindowVerticalSync", &m_optionsData.WindowVerticalSync);

            ImGui::TextUnformatted("Frame Rate Limit:");
            ImGui::InputScalar("##OptionsWindowInputWindowFrameRateLimit", ImGuiDataType_U32, &m_optionsData.WindowFrameRateLimit, &tb::Constants::MyImGui::InputScalarU32StepOne);

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Map##OptionsWindowTabItemMap"))
        {
            ImGui::BeginChild("##OptionsWindowTabChildMap", m_tabChildSize);

            ImGui::Checkbox("Skip Map Select##OptionsWindowCheckboxMapSkipSelect", &m_optionsData.MapSkipSelect);  

            ImGui::TextUnformatted("Skip Map Select File:");
            ImGui::InputText("##OptionsWindowInputMapSkipSelectFileName", &m_optionsData.MapSkipSelectFileName);

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Game##OptionsWindowTabItemGame"))
        {
            ImGui::BeginChild("##OptionsWindowTabChildGame", m_tabChildSize);

            ImGui::Checkbox("Developer Mode##OptionsWindowCheckboxGameDeveloperMode", &m_optionsData.GameDeveloperMode);
            ImGui::Checkbox("Debug Mode##OptionsWindowCheckboxGameDebugMode", &m_optionsData.GameDebugMode);

            ImGui::Separator();

            ImGui::Checkbox("Show Floating Text##OptionsWindowCheckboxGameShowFloatingText", &m_optionsData.GameShowFloatingText);
            ImGui::Checkbox("Show Player Names##OptionsWindowCheckboxGameShowPlayerNames", &m_optionsData.GameShowPlayerNames);
            ImGui::Checkbox("Show Player Health Bar##OptionsWindowCheckboxGameShowPlayerHealthBar", &m_optionsData.GameShowPlayerHealthBar);
            ImGui::Checkbox("Show Player Mana Bar##OptionsWindowCheckboxGameShowPlayerManaBar", &m_optionsData.GameShowPlayerManaBar);
            ImGui::Checkbox("Show NPC Names##OptionsWindowCheckboxGameShowNPCNames", &m_optionsData.GameShowNPCNames);
            ImGui::Checkbox("Show NPC Health Bar##OptionsWindowCheckboxGameShowNPCHealthBar", &m_optionsData.GameShowNPCHealthBar);
            ImGui::Checkbox("Show NPC Mana Bar##OptionsWindowCheckboxGameShowNPCManaBar", &m_optionsData.GameShowNPCManaBar);
            ImGui::Checkbox("Show Monster Names##OptionsWindowCheckboxGameShowMonsterNames", &m_optionsData.GameShowMonsterNames);
            ImGui::Checkbox("Show Monster Health Bar##OptionsWindowCheckboxGameShowMonsterHealthBar", &m_optionsData.GameShowMonsterHealthBar);
            ImGui::Checkbox("Show Monster Mana Bar##OptionsWindowCheckboxGameShowMonsterManaBar", &m_optionsData.GameShowMonsterManaBar);

            ImGui::Separator();

            ImGui::Checkbox("Friendly Fire##OptionsWindowCheckboxGameFriendlyFire", &m_optionsData.GameFriendlyFire);

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Audio##OptionsWindowTabItemAudio"))
        {
            ImGui::BeginChild("##OptionsWindowTabChildAudio", m_tabChildSize);

            ImGui::Checkbox("Sound##OptionsWindowCheckboxAudioSound", &m_optionsData.AudioSound);
            ImGui::Checkbox("Music##OptionsWindowCheckboxAudioMusic", &m_optionsData.AudioMusic);

            ImGui::TextUnformatted("Sound Volume:");
            ImGui::InputScalar("##OptionsWindowInputAudioSoundVolume", ImGuiDataType_U8, &m_optionsData.AudioSoundVolume, &tb::Constants::MyImGui::InputScalarU8StepOne);

            ImGui::TextUnformatted("Music Volume:");
            ImGui::InputScalar("##OptionsWindowInputAudioMusicVolume", ImGuiDataType_U8, &m_optionsData.AudioMusicVolume, &tb::Constants::MyImGui::InputScalarU8StepOne);

            ImGui::Separator();

            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Cheats##OptionsWindowTabItemCheats"))
        {
            ImGui::BeginChild("##OptionsWindowTabChildCheats", m_tabChildSize);

            ImGui::Checkbox("Infinite Health##OptionsWindowCheckboxCheatsInfiniteHealth", &m_optionsData.CheatsInfiniteHealth);
            ImGui::Checkbox("Infinite Mana##OptionsWindowCheckboxCheatsInfiniteMana", &m_optionsData.CheatsInfiniteMana);
            ImGui::Checkbox("Infinite Cap##OptionsWindowCheckboxCheatsInfiniteCap", &m_optionsData.CheatsInfiniteCap);

            ImGui::Separator();

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
