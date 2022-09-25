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
        m_spriteIDList_List.clear();
        m_spriteIDList_List.reserve(tb::Constants::NumWaterAnimationFrames);

        m_data = toml::parse_file(m_fileName);
        if (m_data.size() == 0)
        {
            g_Log.write("ERROR: Failed to parse data from file: {}\n", m_fileName);
            return false;
        }

        g_Log.write("Loaded data from file: {}\n", m_fileName);

        for (unsigned int i = 0; i < tb::Constants::NumWaterAnimationFrames; i++)
        {
            std::string waterIndex = std::to_string(i);

            if (!m_data[waterIndex])
            {
                g_Log.write("ERROR: {} is missing data at index {}\n", m_fileName, i);
                return false;
            }

            g_Log.write("Index: {}\n", i);

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(tb::Constants::NumWaterSpritesPerAnimationFrame);

            auto sprites = m_data[waterIndex]["Sprites"].as_array();

            if (sprites == nullptr)
            {
                g_Log.write("ERROR: nullptr\n");
                return false;
            }

            for (auto& sprite : *sprites)
            {
                uint32_t spriteID = sprite.value_or(0);
                if (spriteID == 0)
                {
                    g_Log.write("ERROR: Sprite ID cannot be zero\n");
                    return false;
                }

                g_Log.write("Sprite ID: {}\n", spriteID);

                spriteIDList.push_back(spriteID);
            }

            if (spriteIDList.size() == 0)
            {
                g_Log.write("Sprite ID list is empty at index {}\n", i);
                return false;
            }

            if (spriteIDList.size() != tb::Constants::NumWaterSpritesPerAnimationFrame)
            {
                g_Log.write("Sprite ID list has the wrong size\n");
                return false;
            }

            m_spriteIDList_List.push_back(spriteIDList);
        }

        g_Log.write("Loaded data size: {}\n", m_spriteIDList_List.size());

        if (m_spriteIDList_List.size() != tb::Constants::NumWaterAnimationFrames)
        {
            g_Log.write("ERROR: Loaded data has the wrong size\n");
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
