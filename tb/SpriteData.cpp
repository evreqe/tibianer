#include "tb/SpriteData.h"

namespace tb
{

SpriteData::SpriteData()
{
    //
}

SpriteData::~SpriteData()
{
    //
}

bool SpriteData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToLoad);

    tb::SpriteData::Data firstData;
    firstData.SpriteID = 0;
    firstData.Name = "NULL";

    m_dataList.push_back(firstData);

    for (std::uint32_t i = 1; i < m_numToLoad + 1; i++)
    {
        std::string index = std::to_string(i);

        if (!m_table[index])
        {
            g_Log.write("ERROR: '{}' is missing data at index: [{}]\n", m_fileName, i);
            return false;
        }

        tb::SpriteData::Data data;

        data.SpriteID = static_cast<tb::SpriteID_t>(i);

        data.Name = m_table[index]["Name"].value_or("");
        data.Article = m_table[index]["Article"].value_or("");
        data.Description = m_table[index]["Description"].value_or("");

        data.AnimationName = m_table[index]["AnimationName"].value_or("");

        data.TileWidth = static_cast<std::uint8_t>(m_table[index]["TileWidth"].value_or(1));
        data.TileHeight = static_cast<std::uint8_t>(m_table[index]["TileHeight"].value_or(1));

        data.Weight = m_table[index]["Weight"].value_or(0.0f);
        data.LightRadius = m_table[index]["LightRadius"].value_or(0.0f);

        tb::SpriteFlags spriteFlags;

        for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
        {
            std::string spriteFlagKey = std::format("Flag{}", spriteFlagName);

            bool spriteFlagValue = m_table[index][spriteFlagKey].value_or(false);

            if (spriteFlagValue == true)
            {
                spriteFlags.setFlag(spriteFlag, true);
            }
        }

        data.SpriteFlags = spriteFlags;

        m_dataList.push_back(data);
    }

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    if (m_dataList.size() != m_numToLoad + 1)
    {
        g_Log.write("ERROR: Loaded data has the wrong size, {} instead of {}\n", m_dataList.size(), m_numToLoad + 1);
        return false;
    }

    return true;
}

bool SpriteData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

bool SpriteData::save()
{
    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: Cannot save data because it is empty\n");
        return false;
    }

    std::fstream file;
    file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("Cannot open file: {}\n", m_fileName);
        return false;
    }

    for (auto& data : m_dataList)
    {
        file << std::format("[{}]\n", data.SpriteID);

        file << std::format("Name=\"{}\"\n", data.Name);
        file << std::format("Article=\"{}\"\n", data.Article);
        file << std::format("Description=\"{}\"\n", data.Description);

        file << std::format("AnimationName=\"{}\"\n", data.AnimationName);

        file << std::format("TileWidth={}\n", data.TileWidth);
        file << std::format("TileHeight={}\n", data.TileHeight);

        file << std::format("Weight={:.2f}\n", data.Weight);
        file << std::format("LightRadius={:.2f}\n", data.LightRadius);

        for (auto& [spriteFlag, spriteFlagName] : tb::SpriteFlagEntries)
        {
            if (data.SpriteFlags.hasFlag(spriteFlag) == true)
            {
                file << std::format("Flag{}=1\n", spriteFlagName);
            }
        }
    }

    file.close();

    g_Log.write("Saved data to file: {}\n", m_fileName);

    return true;
}

tb::SpriteData::DataList* SpriteData::getDataList()
{
    return &m_dataList;
}

tb::SpriteData::Data* SpriteData::getDataBySpriteID(const tb::SpriteID_t& spriteID)
{
    return &m_dataList.at(spriteID);
}

tb::SpriteData::Data* SpriteData::getDataByName(const std::string& name)
{
    for (auto& data : m_dataList)
    {
        if (data.Name == name)
        {
            return &data;
        }
    }

    return nullptr;
}

tb::SpriteData::Data* SpriteData::getDataByNameSV(std::string_view name)
{
    for (auto& data : m_dataList)
    {
        if (data.Name == name)
        {
            return &data;
        }
    }

    return nullptr;
}

}
