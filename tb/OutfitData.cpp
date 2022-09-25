#include "tb/OutfitData.h"

namespace tb
{

    OutfitData::OutfitData()
    {
        //
    }

    OutfitData::~OutfitData()
    {
        //
    }

    bool OutfitData::load()
    {
        m_outfitList.clear();
        m_outfitList.reserve(tb::Constants::NumOutfitSpriteIndex);

        m_data = toml::parse_file(m_fileName);
        if (m_data.size() == 0)
        {
            g_Log.write("ERROR: Failed to parse data from file: {}\n", m_fileName);
            return false;
        }

        g_Log.write("Loaded data from file: {}\n", m_fileName);

        for (unsigned int i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
        {
            std::string outfitIndex = std::to_string(i);

            if (!m_data[outfitIndex])
            {
                g_Log.write("ERROR: {} is missing data at index {}\n", m_fileName, i);
                return false;
            }

            g_Log.write("Index: {}\n", i);

            tb::OutfitData::Outfit outfit;

            outfit.Index = i;

            outfit.Name = m_data[outfitIndex]["Name"].value_or("");

            if (outfit.Name.size() == 0)
            {
                g_Log.write("ERROR: Name cannot be empty\n");
                return false;
            }

            g_Log.write("Name: {}\n", outfit.Name);

            for (unsigned int j = 0; j < m_numSpriteIDListToLoadPerIndex; j++)
            {
                std::string spritesIndex = std::format("Sprites{}", j);

                if (!m_data[outfitIndex][spritesIndex])
                {
                    break;
                }

                g_Log.write("Sprites# index: {}\n", j);

                tb::SpriteIDList spriteIDList;

                auto sprites = m_data[outfitIndex][spritesIndex].as_array();

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
                        g_Log.write("ERROR: Sprite ID cannot be zero at index: [{}] Sprites{}\n", i, j);
                        return false;
                    }

                    g_Log.write("Sprite ID: {}\n", spriteID);

                    spriteIDList.push_back(spriteID);
                }

                if (spriteIDList.size() == 0)
                {
                    g_Log.write("ERROR: Sprite ID list cannot be empty\n");
                    return false;
                }

                outfit.SpriteIDList_List.push_back(spriteIDList);
            }

            m_outfitList.push_back(outfit);
        }

        g_Log.write("Loaded data size: {}\n", m_outfitList.size());

        if (m_outfitList.size() != tb::Constants::NumOutfitSpriteIndex)
        {
            g_Log.write("ERROR: Loaded data has the wrong size\n");
            return false;
        }

        return true;
    }

    bool OutfitData::isLoaded()
    {
        if (m_data.size() == 0) return false;
        if (m_outfitList.size() == 0) return false;

        return true;
    }

    tb::OutfitData::OutfitList* OutfitData::getOutfitList()
    {
        return &m_outfitList;
    }

}
