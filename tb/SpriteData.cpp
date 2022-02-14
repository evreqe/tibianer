#include "tb/SpriteData.h"

namespace tb
{

SpriteData::SpriteData()
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
        tb::print("ERROR: Sprite data failed to parse from file: {}\n", m_fileName);

        return false;
    }

    tb::print("Sprite data loaded from file: {}\n", m_fileName);

    tb::SpriteData::Data firstSpriteData;
    firstSpriteData.SpriteID = 0;

    m_dataList.push_back(firstSpriteData);

    for (tb::SpriteID_t i = 1; i < tb::Constants::NumSprites + 1; i++)
    {
        tb::SpriteData::Data spriteData;

        spriteData.SpriteID = i;

        tb::SpriteFlags_t spriteFlags;

        for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
        {
            bool spriteFlagValue = m_data[std::to_string(i)][spriteFlagName].value_or(false);

            if (spriteFlagValue == true)
            {
                //tb::print("[DEBUG]: [{}] {} = {}\n", i, spriteFlagName, spriteFlagValue);

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

    tb::print("Sprite data list size: {}\n", m_dataList.size());

    return true;
}

bool SpriteData::save()
{
    if (m_dataList.size() == 0)
    {
        tb::printError("m_dataList.size() == 0\n");
        return false;
    }

    std::fstream file;
    file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        tb::printError("file.is_open() == false\n");
        return false;
    }

    for (auto& spriteData : m_dataList)
    {
        file << std::format("[{}]\n", spriteData.SpriteID);

        for (auto& [spriteFlagName, spriteFlag] : tb::KeyValues::SpriteFlags)
        {
            bool isFlagEnabled = spriteData.SpriteFlags.test(spriteFlag);

            if (isFlagEnabled == true)
            {
                file << std::format("{}=1\n", spriteFlagName);
            }
        }
    }

    file.close();

    tb::print("Sprite data saved to file: {}\n", m_fileName);

    return true;
}

tb::SpriteData::DataList* SpriteData::getDataList()
{
    return &m_dataList;
}

}
