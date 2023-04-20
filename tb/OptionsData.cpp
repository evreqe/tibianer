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
        g_Log.write("{}\n{}\n", parseError.description(), parseError.source().begin);
        return false;
    }

    g_Log.write("Loaded data from file: {}\n", m_fileName);

    m_data.PlayerName = m_table["Player"]["Name"].value_or("");

    g_Log.write("Player Name: {}\n", m_data.PlayerName);

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

    file << "[Player]\n";

    if (m_data.PlayerName.size() != 0)
    {
        file << std::format("Name=\"{}\"\n", m_data.PlayerName);
    }

    file.close();

    g_Log.write("Saved data to file: {}\n", m_fileName);

    return true;
}

tb::OptionsData::Data* OptionsData::getData()
{
    return &m_data;
}

}
