#pragma once

namespace tb
{

class SpriteData
{

public:

    typedef struct _Data
    {
        tb::SpriteID_t SpriteID = 0;
        tb::SpriteFlags_t SpriteFlags;
        std::string Article; // 'a' or 'an'
        std::string Name;
        float Weight = 0.0f; // cap
        uint32_t Width = 1;
        uint32_t Height = 1;

    } Data, *Data_ptr;

    typedef std::vector<tb::SpriteData::Data> DataList;

    SpriteData()
    {
        //
    }

    bool load()
    {
        m_dataList.clear();
        m_dataList.reserve(tb::Constants::NumSprites);

        m_data = toml::parse_file(m_fileName);

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

    void save()
    {
        if (m_dataList.size() == 0)
        {
            tb::printError("m_dataList.size() == 0\n");
            return;
        }

        std::fstream file;
        file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

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
    }

    tb::SpriteData::DataList* getDataList()
    {
        return &m_dataList;
    }

private:

    std::string m_fileName = "data/sprites.txt";

    toml::parse_result m_data;

    tb::SpriteData::DataList m_dataList;

};

}
