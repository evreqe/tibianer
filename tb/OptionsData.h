#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class OptionsData
{

public:

    OptionsData();
    ~OptionsData();

    static OptionsData& getInstance()
    {
        static OptionsData instance;
        return instance;
    }

private:

    OptionsData(const OptionsData&) = delete;
    OptionsData(OptionsData&&) = delete;
    OptionsData& operator=(const OptionsData&) = delete;
    OptionsData& operator=(OptionsData&&) = delete;

public:

    struct Data
    {
        bool LogIsEnabled = true;
        bool LogPrintToConsole = true;
        bool LogWriteToFile = true;

        std::string PlayerName;
        std::uint8_t PlayerOutfitHead = 0;
        std::uint8_t PlayerOutfitBody = 0;
        std::uint8_t PlayerOutfitLegs = 0;
        std::uint8_t PlayerOutfitFeet = 0;

        bool WindowStartMaximized = true;
        std::uint32_t WindowFrameRateLimit = 60;
        bool WindowVerticalSync = true;

        bool MapSkipSelect = false;
        std::string MapSkipSelectFileName;

        bool GameDeveloperMode = true;
        bool GameDebugMode = true;
        bool GameShowFloatingText = false;
        bool GameShowPlayerNames = false;
        bool GameShowPlayerHealthBar = false;
        bool GameShowPlayerManaBar = false;
        bool GameShowNPCNames = false;
        bool GameShowNPCHealthBar = false;
        bool GameShowNPCManaBar = false;
        bool GameShowMonsterNames = false;
        bool GameShowMonsterHealthBar = false;
        bool GameShowMonsterManaBar = false;
        bool GameFriendlyFire = false;

        bool AudioSound = false;
        std::uint8_t AudioSoundVolume = 100;
        bool AudioMusic = false;
        std::uint8_t AudioMusicVolume = 100;

        bool CheatsInfiniteHealth = false;
        bool CheatsInfiniteMana = false;
        bool CheatsInfiniteCap = false;
    };

    bool load();
    bool isLoaded();

    bool save();

    tb::OptionsData::Data* getData();
    void setData(const tb::OptionsData::Data& data);

private:

    const std::string m_fileName = "config/options.txt";

    toml::table m_table;

    tb::OptionsData::Data m_data;

};

}

namespace
{
    inline tb::OptionsData& g_OptionsData = tb::OptionsData::getInstance();
}
