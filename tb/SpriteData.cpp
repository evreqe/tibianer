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
    m_dataList.clear();
    m_dataList.reserve(tb::Constants::NumSprites);

    m_data = toml::parse_file(m_fileName);
    if (m_data.size() == 0)
    {
        g_Log.write("ERROR: Sprite data failed to parse from file: {}\n", m_fileName);
        return false;
    }

    g_Log.write("Sprite data loaded from file: {}\n", m_fileName);

    tb::SpriteData::Data firstSpriteData;
    firstSpriteData.SpriteID = 0;

    m_dataList.push_back(firstSpriteData);

    for (tb::SpriteID_t i = 1; i < tb::Constants::NumSprites + 1; i++)
    {
        std::string spriteIndex = std::to_string(i);

        tb::SpriteData::Data spriteData;

        spriteData.SpriteID = i;

        spriteData.Name = m_data[spriteIndex]["Name"].value_or("");

        spriteData.Article = m_data[spriteIndex]["Article"].value_or("");

        spriteData.Weight = m_data[spriteIndex]["Weight"].value_or(0.0f);

        spriteData.TileWidth = m_data[spriteIndex]["TileWidth"].value_or(1);
        spriteData.TileHeight = m_data[spriteIndex]["TileHeight"].value_or(1);

        tb::SpriteFlags_t spriteFlags;

        for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
        {
            std::string spriteFlagKey = "Flag" + spriteFlagName;

            bool spriteFlagValue = m_data[spriteIndex][spriteFlagKey].value_or(false);

            if (spriteFlagValue == true)
            {
                //tb::print("[DEBUG]: [{}] {} = {}\n", i, spriteFlagKey, spriteFlagValue);

                spriteFlags.set(spriteFlag, 1);
            }
        }

        //if (spriteFlags != 0)
        //{
            //tb::print("[DEBUG]: spriteFlags = {}\n", spriteFlags.to_string<char, std::string::traits_type, std::string::allocator_type>());
        //}

        spriteData.SpriteFlags = spriteFlags;

        m_dataList.push_back(spriteData);
    }

    g_Log.write("Sprite data list size: {}\n", m_dataList.size());

    return true;
}

bool SpriteData::isLoaded()
{
    if (m_data.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

bool SpriteData::save()
{
    if (m_dataList.size() == 0)
    {
        g_Log.write("m_dataList.size() == 0\n");
        return false;
    }

    std::fstream file;
    file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("file.is_open() == false\n");
        return false;
    }

    for (auto& spriteData : m_dataList)
    {
        file << std::format("[{}]\n", spriteData.SpriteID);

        file << std::format("Name=\"{}\"\n", spriteData.Name);

        file << std::format("Article=\"{}\"\n", spriteData.Article);

        file << std::format("Weight={:.2f}\n", spriteData.Weight);

        file << std::format("TileWidth={}\n", spriteData.TileWidth);
        file << std::format("TileHeight={}\n", spriteData.TileHeight);

        for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
        {
            bool isFlagEnabled = spriteData.SpriteFlags.test(spriteFlag);

            if (isFlagEnabled == true)
            {
                file << std::format("Flag{}=1\n", spriteFlagName);
            }
        }
    }

    file.close();

    g_Log.write("Sprite data saved to file: {}\n", m_fileName);

    return true;
}

tb::SpriteData::DataList* SpriteData::getDataList()
{
    return &m_dataList;
}

}
