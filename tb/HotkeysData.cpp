#include "tb/HotkeysData.h"

namespace tb
{

HotkeysData::HotkeysData()
{
    //
}

HotkeysData::~HotkeysData()
{
    //
}

bool HotkeysData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    std::string sectionName = "Hotkeys";

    m_data.F1 = m_table[sectionName]["F1"].value_or("");
    g_Log.write("F1: {}\n", m_data.F1);

    m_data.F2 = m_table[sectionName]["F2"].value_or("");
    g_Log.write("F2: {}\n", m_data.F2);

    m_data.F3 = m_table[sectionName]["F3"].value_or("");
    g_Log.write("F3: {}\n", m_data.F3);

    m_data.F4 = m_table[sectionName]["F4"].value_or("");
    g_Log.write("F4: {}\n", m_data.F4);

    m_data.F5 = m_table[sectionName]["F5"].value_or("");
    g_Log.write("F5: {}\n", m_data.F5);

    m_data.F6 = m_table[sectionName]["F6"].value_or("");
    g_Log.write("F6: {}\n", m_data.F6);

    m_data.F7 = m_table[sectionName]["F7"].value_or("");
    g_Log.write("F7: {}\n", m_data.F7);

    m_data.F8 = m_table[sectionName]["F8"].value_or("");
    g_Log.write("F8: {}\n", m_data.F8);

    m_data.F9 = m_table[sectionName]["F9"].value_or("");
    g_Log.write("F9: {}\n", m_data.F9);

    m_data.F10 = m_table[sectionName]["F10"].value_or("");
    g_Log.write("F10: {}\n", m_data.F10);

    m_data.F11 = m_table[sectionName]["F11"].value_or("");
    g_Log.write("F11: {}\n", m_data.F11);

    m_data.F12 = m_table[sectionName]["F12"].value_or("");
    g_Log.write("F12: {}\n", m_data.F12);

    return true;
}

bool HotkeysData::isLoaded()
{
    if (m_table.size() == 0)
    {
        return false;
    }

    return true;
}

bool HotkeysData::save()
{
    std::fstream file;
    file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("ERROR: Cannot open file: {}\n", m_fileName);
        return false;
    }

    file << "[Hotkeys]\n";

    file << std::format("F1=\"{}\"\n", m_data.F1);
    file << std::format("F2=\"{}\"\n", m_data.F2);
    file << std::format("F3=\"{}\"\n", m_data.F3);
    file << std::format("F4=\"{}\"\n", m_data.F4);
    file << std::format("F5=\"{}\"\n", m_data.F5);
    file << std::format("F6=\"{}\"\n", m_data.F6);
    file << std::format("F7=\"{}\"\n", m_data.F7);
    file << std::format("F8=\"{}\"\n", m_data.F8);
    file << std::format("F9=\"{}\"\n", m_data.F9);
    file << std::format("F10=\"{}\"\n", m_data.F10);
    file << std::format("F11=\"{}\"\n", m_data.F11);
    file << std::format("F12=\"{}\"\n", m_data.F12);

    file.close();

    g_Log.write("Saved data to file: {}\n", m_fileName);

    return true;
}

tb::HotkeysData::Data* HotkeysData::getData()
{
    return &m_data;
}

void HotkeysData::setData(const tb::HotkeysData::Data& data)
{
    m_data = data;
}

}
