#include "tb/OptionsData.h"

namespace tb
{

OptionsData::OptionsData()
{
    //
}

OptionsData::~OptionsData()
{
    //
}

bool OptionsData::load()
{
    if (std::filesystem::exists(m_fileName) == false)
    {
        g_Log.write("ERROR: File does not exist: {}\n", m_fileName);
        return false;
    }

    m_table.clear();

    try
    {
        m_table = toml::parse_file(m_fileName);
    }
    catch (const toml::parse_error& parseError)
    {
        g_Log.write("ERROR: Failed to load data from file: {}\n", m_fileName);
        g_Log.write("Description: {}\nLine: {}\nColumn: {}\n", parseError.description(), parseError.source().begin.line, parseError.source().begin.column);
        return false;
    }

    g_Log.write("Loaded data from file: {}\n", m_fileName);

    m_data.LogIsEnabled = m_table["Log"]["IsEnabled"].value_or(true);
    m_data.LogPrintToConsole = m_table["Log"]["PrintToConsole"].value_or(true);
    m_data.LogWriteToFile = m_table["Log"]["WriteToFile"].value_or(true);

    m_data.PlayerName = m_table["Player"]["Name"].value_or("");
    m_data.PlayerOutfitHead = m_table["Player"]["OutfitHead"].value_or(0);
    m_data.PlayerOutfitBody = m_table["Player"]["OutfitBody"].value_or(0);
    m_data.PlayerOutfitLegs = m_table["Player"]["OutfitLegs"].value_or(0);
    m_data.PlayerOutfitFeet = m_table["Player"]["OutfitFeet"].value_or(0);

    m_data.WindowStartMaximized = m_table["Window"]["StartMaximized"].value_or(true);
    m_data.WindowFrameRateLimit = m_table["Window"]["FrameRateLimit"].value_or(60);
    m_data.WindowVerticalSync = m_table["Window"]["VerticalSync"].value_or(true);

    m_data.MapSkipSelect = m_table["Map"]["SkipSelect"].value_or(false);
    m_data.MapSkipSelectFileName = m_table["Map"]["SkipSelectFileName"].value_or("");

    m_data.GameDeveloperMode = m_table["Game"]["DeveloperMode"].value_or(true);
    m_data.GameDebugMode = m_table["Game"]["DebugMode"].value_or(true);
    m_data.GameShowFloatingText = m_table["Game"]["ShowFloatingText"].value_or(false);
    m_data.GameShowPlayerNames = m_table["Game"]["ShowPlayerNames"].value_or(false);
    m_data.GameShowPlayerHealthBar = m_table["Game"]["ShowPlayerHealthBar"].value_or(false);
    m_data.GameShowPlayerManaBar = m_table["Game"]["ShowPlayerManaBar"].value_or(false);
    m_data.GameShowNPCNames = m_table["Game"]["ShowNPCNames"].value_or(false);
    m_data.GameShowNPCHealthBar = m_table["Game"]["ShowNPCHealthBar"].value_or(false);
    m_data.GameShowNPCManaBar = m_table["Game"]["ShowNPCManaBar"].value_or(false);
    m_data.GameShowMonsterNames = m_table["Game"]["ShowMonsterNames"].value_or(false);
    m_data.GameShowMonsterHealthBar = m_table["Game"]["ShowMonsterHealthBar"].value_or(false);
    m_data.GameShowMonsterManaBar = m_table["Game"]["ShowMonsterManaBar"].value_or(false);
    m_data.GameFriendlyFire = m_table["Game"]["FriendlyFire"].value_or(false);

    m_data.AudioSound = m_table["Audio"]["Sound"].value_or(false);
    m_data.AudioSoundVolume = m_table["Audio"]["SoundVolume"].value_or(100);
    m_data.AudioMusic = m_table["Audio"]["Music"].value_or(false);
    m_data.AudioMusicVolume = m_table["Audio"]["MusicVolume"].value_or(100);

    m_data.CheatsInfiniteHealth = m_table["Cheats"]["InfiniteHealth"].value_or(false);
    m_data.CheatsInfiniteMana = m_table["Cheats"]["InfiniteMana"].value_or(false);
    m_data.CheatsInfiniteCap = m_table["Cheats"]["InfiniteCap"].value_or(false);

    g_Log.write("LogIsEnabled: {}\n", m_data.LogIsEnabled);

    g_Log.write("PlayerName: {}\n", m_data.PlayerName);
    g_Log.write("PlayerOutfitHead: {}\n", m_data.PlayerOutfitHead);
    g_Log.write("PlayerOutfitBody: {}\n", m_data.PlayerOutfitBody);
    g_Log.write("PlayerOutfitLegs: {}\n", m_data.PlayerOutfitLegs);
    g_Log.write("PlayerOutfitFeet: {}\n", m_data.PlayerOutfitFeet);

    g_Log.write("WindowStartMaximized: {}\n", m_data.WindowStartMaximized);
    g_Log.write("WindowFrameRateLimit: {}\n", m_data.WindowFrameRateLimit);
    g_Log.write("WindowVerticalSync: {}\n", m_data.WindowVerticalSync);

    g_Log.write("MapSkipSelect: {}\n", m_data.MapSkipSelect);
    g_Log.write("MapSkipSelectFileName: {}\n", m_data.MapSkipSelectFileName);

    g_Log.write("GameShowFloatingText: {}\n", m_data.GameShowFloatingText);
    g_Log.write("GameShowPlayerNames: {}\n", m_data.GameShowPlayerNames);
    g_Log.write("GameShowPlayerHealthBar: {}\n", m_data.GameShowPlayerHealthBar);
    g_Log.write("GameShowPlayerManaBar: {}\n", m_data.GameShowPlayerManaBar);
    g_Log.write("GameShowNPCNames: {}\n", m_data.GameShowNPCNames);
    g_Log.write("GameShowNPCHealthBar: {}\n", m_data.GameShowNPCHealthBar);
    g_Log.write("GameShowNPCManaBar: {}\n", m_data.GameShowNPCManaBar);
    g_Log.write("GameShowMonsterNames: {}\n", m_data.GameShowMonsterNames);
    g_Log.write("GameShowMonsterHealthBar: {}\n", m_data.GameShowMonsterHealthBar);
    g_Log.write("GameShowMonsterManaBar: {}\n", m_data.GameShowMonsterManaBar);
    g_Log.write("GameFriendlyFire: {}\n", m_data.GameFriendlyFire);

    g_Log.write("AudioSound: {}\n", m_data.AudioSound);
    g_Log.write("AudioSoundVolume: {}\n", m_data.AudioSoundVolume);
    g_Log.write("AudioMusic: {}\n", m_data.AudioMusic);
    g_Log.write("AudioMusicVolume: {}\n", m_data.AudioMusicVolume);

    g_Log.write("CheatsInfiniteHealth: {}\n", m_data.CheatsInfiniteHealth);
    g_Log.write("CheatsInfiniteMana: {}\n", m_data.CheatsInfiniteMana);
    g_Log.write("CheatsInfiniteCap: {}\n", m_data.CheatsInfiniteCap);

    return true;
}

bool OptionsData::isLoaded()
{
    if (m_table.size() == 0)
    {
        return false;
    }

    return true;
}

bool OptionsData::save()
{
    std::fstream file;
    file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("ERROR: Cannot open file: {}\n", m_fileName);
        return false;
    }

    file << "[Log]\n";

    file << std::format("IsEnabled={}\n", m_data.LogIsEnabled);
    file << std::format("PrintToConsole={}\n", m_data.LogPrintToConsole);
    file << std::format("WriteToFile={}\n", m_data.LogWriteToFile);

    file << "[Player]\n";

    file << std::format("Name=\"{}\"\n", m_data.PlayerName);
    file << std::format("OutfitHead={}\n", m_data.PlayerOutfitHead);
    file << std::format("OutfitBody={}\n", m_data.PlayerOutfitBody);
    file << std::format("OutfitLegs={}\n", m_data.PlayerOutfitLegs);
    file << std::format("OutfitFeet={}\n", m_data.PlayerOutfitFeet);

    file << "[Window]\n";

    file << std::format("StartMaximized={}\n", m_data.WindowStartMaximized);
    file << std::format("FrameRateLimit={}\n", m_data.WindowFrameRateLimit);
    file << std::format("VerticalSync={}\n", m_data.WindowVerticalSync);

    file << "[Map]\n";

    file << std::format("SkipSelect={}\n", m_data.MapSkipSelect);
    file << std::format("SkipSelectFileName=\"{}\"\n", m_data.MapSkipSelectFileName);

    file << "[Game]\n";

    file << std::format("DeveloperMode={}\n", m_data.GameDeveloperMode);
    file << std::format("DebugMode={}\n", m_data.GameDebugMode);
    file << std::format("ShowFloatingText={}\n", m_data.GameShowFloatingText);
    file << std::format("ShowPlayerNames={}\n", m_data.GameShowPlayerNames);
    file << std::format("ShowPlayerHealthBar={}\n", m_data.GameShowPlayerHealthBar);
    file << std::format("ShowPlayerManaBar={}\n", m_data.GameShowPlayerManaBar);
    file << std::format("ShowNPCNames={}\n", m_data.GameShowNPCNames);
    file << std::format("ShowNPCHealthBar={}\n", m_data.GameShowNPCHealthBar);
    file << std::format("ShowNPCManaBar={}\n", m_data.GameShowNPCManaBar);
    file << std::format("ShowMonsterNames={}\n", m_data.GameShowMonsterNames);
    file << std::format("ShowMonsterHealthBar={}\n", m_data.GameShowMonsterHealthBar);
    file << std::format("ShowMonsterManaBar={}\n", m_data.GameShowMonsterManaBar);
    file << std::format("FriendlyFire={}\n", m_data.GameFriendlyFire);

    file << "[Audio]\n";

    file << std::format("Sound={}\n", m_data.AudioSound);
    file << std::format("SoundVolume={}\n", m_data.AudioSoundVolume);
    file << std::format("Music={}\n", m_data.AudioMusic);
    file << std::format("MusicVolume={}\n", m_data.AudioMusicVolume);

    file << "[Cheats]\n";

    file << std::format("InfiniteHealth={}\n", m_data.CheatsInfiniteHealth);
    file << std::format("InfiniteMana={}\n", m_data.CheatsInfiniteMana);
    file << std::format("InfiniteCap={}\n", m_data.CheatsInfiniteCap);

    file.close();

    g_Log.write("Saved data to file: {}\n", m_fileName);

    return true;
}

tb::OptionsData::Data* OptionsData::getData()
{
    return &m_data;
}

void OptionsData::setData(const tb::OptionsData::Data& data)
{
    m_data = data;
}

}
