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
            g_Log.write("ERROR: Water data failed to parse from file: {}\n", m_fileName);
            return false;
        }

        g_Log.write("Water data loaded from file: {}\n", m_fileName);

        for (unsigned int i = 0; i < tb::Constants::NumWaterAnimationFrames; i++)
        {
            std::string waterIndex = std::to_string(i);

            if (!m_data[waterIndex])
            {
                continue;
            }

            g_Log.write("Water index: {}\n", waterIndex);

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(tb::Constants::NumWaterSpritesPerAnimationFrame);

            auto sprites = m_data[waterIndex]["Sprites"].as_array();

            if (sprites != nullptr)
            {
                for (auto& sprite : *sprites)
                {
                    uint32_t spriteID = sprite.value_or(0);
                    if (spriteID == 0)
                    {
                        g_Log.write("ERROR: spriteID == 0\n");
                        return false;
                    }

                    g_Log.write("Water sprite ID: {}\n", spriteID);

                    spriteIDList.push_back(spriteID);
                }
            }

            if (spriteIDList.size() == 0)
            {
                g_Log.write("ERROR: spriteIDList.size() == 0\n");
                return false;
            }

            if (spriteIDList.size() != tb::Constants::NumWaterSpritesPerAnimationFrame)
            {
                g_Log.write("ERROR: spriteIDList.size() != tb::Constants::NumWaterSpritesPerAnimationFrame\n");
                return false;
            }

            m_spriteIDList_List.push_back(spriteIDList);
        }

        g_Log.write("Water data sprite ID list list size: {}\n", m_spriteIDList_List.size());

        if (m_spriteIDList_List.size() != tb::Constants::NumWaterAnimationFrames)
        {
            g_Log.write("ERROR: m_spriteIDList_List.size() != tb::Constants::NumWaterAnimationFrames\n");
            return false;
        }

        g_Log.write("m_spriteIDList_List:\n");

        for (auto& spriteIDListEx : m_spriteIDList_List)
        {
            g_Log.write("-- spriteIDList:\n");

            for (auto& spriteID : spriteIDListEx)
            {
                g_Log.write("---- spriteID: {}\n", spriteID);
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
