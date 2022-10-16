#include "tb/WaterData.h"

namespace tb
{

    WaterData::WaterData()
    {
        //
    }

    WaterData::~WaterData()
    {
        //
    }

    bool WaterData::load()
    {
        if (std::filesystem::exists(m_fileName) == false)
        {
            g_Log.write("ERROR: File does not exist: {}\n", m_fileName);
            return false;
        }

        m_data.clear();
        m_data = toml::parse_file(m_fileName);
        if (m_data.size() == 0)
        {
            g_Log.write("ERROR: Failed to load data from file: {}\n", m_fileName);
            return false;
        }

        g_Log.write("Loaded data from file: {}\n", m_fileName);

        m_spriteIDList_List.clear();
        m_spriteIDList_List.reserve(m_numToLoad);

        for (unsigned int i = 0; i < m_numToLoad; i++)
        {
            std::string index = std::to_string(i);

            if (!m_data[index])
            {
                g_Log.write("ERROR: {} is missing data at index: [{}]\n", m_fileName, i);
                return false;
            }

            g_Log.write("Index: {}\n", index);

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(tb::Constants::NumWaterSpritesPerAnimationFrame);

            auto sprites = m_data[index]["Sprites"].as_array();

            if (sprites == nullptr)
            {
                g_Log.write("ERROR: nullptr\n");
                return false;
            }

            for (unsigned int j = 0; auto& sprite : *sprites)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(sprite.value_or(0));
                if (spriteID == 0)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: [{}] Sprites=[#{}]\n", j);
                    return false;
                }

                g_Log.write("Sprite ID: {}\n", spriteID);

                spriteIDList.push_back(spriteID);
            }

            if (spriteIDList.size() == 0)
            {
                g_Log.write("ERROR: 'Sprites' is empty\n");
                return false;
            }

            if (spriteIDList.size() != tb::Constants::NumWaterSpritesPerAnimationFrame)
            {
                g_Log.write("ERROR: 'Sprites' has the wrong size, {} instead of {}\n", spriteIDList.size(), tb::Constants::NumWaterSpritesPerAnimationFrame);
                return false;
            }

            m_spriteIDList_List.push_back(spriteIDList);
        }

        g_Log.write("Loaded data size: {}\n", m_spriteIDList_List.size());

        if (m_spriteIDList_List.size() != tb::Constants::NumWaterAnimationFrames)
        {
            g_Log.write("ERROR: Loaded data has the wrong size, {} instead of {}\n", m_spriteIDList_List.size(), tb::Constants::NumWaterAnimationFrames);
            return false;
        }

        g_Log.write("Sprite ID list list:\n");

        for (auto& spriteIDListEx : m_spriteIDList_List)
        {
            g_Log.write("--> Sprite ID list:\n");

            for (auto& spriteID : spriteIDListEx)
            {
                g_Log.write("----> Sprite ID: {}\n", spriteID);
            }
        }

        return true;
    }

    bool WaterData::isLoaded()
    {
        if (m_data.size() == 0) return false;
        if (m_spriteIDList_List.size() == 0) return false;

        return true;
    }

    std::vector<tb::SpriteIDList>* WaterData::getSpriteIDList_List()
    {
        return &m_spriteIDList_List;
    }

}
