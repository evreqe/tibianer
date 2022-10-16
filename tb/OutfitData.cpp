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

        m_dataList.clear();
        m_dataList.reserve(m_numToLoad);

        for (unsigned int i = 0; i < m_numToLoad; i++)
        {
            std::string index = std::to_string(i);

            if (!m_data[index])
            {
                g_Log.write("ERROR: {} is missing data at index: [{}]\n", m_fileName, i);
                return false;
            }

            g_Log.write("Index: {}\n", index);

            tb::OutfitData::Data data;

            data.Index = i;

            data.Name = m_data[index]["Name"].value_or("");

            if (data.Name.size() == 0)
            {
                g_Log.write("ERROR: 'Name' is empty\n");
                return false;
            }

            g_Log.write("Name: {}\n", data.Name);

            for (unsigned int j = 0; j < m_numSpriteIDListToLoadPerIndex; j++)
            {
                std::string spritesIndex = std::format("Sprites{}", j);

                if (!m_data[index][spritesIndex])
                {
                    break;
                }

                g_Log.write("Sprites# index: {}\n", spritesIndex);

                tb::SpriteIDList spriteIDList;

                auto sprites = m_data[index][spritesIndex].as_array();

                if (sprites == nullptr)
                {
                    g_Log.write("ERROR: nullptr\n");
                    return false;
                }

                for (unsigned int k = 0; auto& sprite : *sprites)
                {
                    tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(sprite.value_or(0));
                    if (spriteID == 0)
                    {
                        g_Log.write("ERROR: Sprite ID is zero at index: [{}] Sprites{}=[#{}]\n", i, j, k);
                        return false;
                    }

                    g_Log.write("Sprite ID: {}\n", spriteID);

                    spriteIDList.push_back(spriteID);
                }

                if (spriteIDList.size() == 0)
                {
                    g_Log.write("ERROR: 'Sprites#' is empty at index: [{}] Sprites{}\n", i, j);
                    return false;
                }

                data.SpriteIDList_List.push_back(spriteIDList);
            }

            m_dataList.push_back(data);
        }

        g_Log.write("Loaded data size: {}\n", m_dataList.size());

        if (m_dataList.size() != tb::Constants::NumOutfitSpriteIndex)
        {
            g_Log.write("ERROR: Loaded data has the wrong size, {} instead of {}\n", m_dataList.size(), tb::Constants::NumOutfitSpriteIndex);
            return false;
        }

        return true;
    }

    bool OutfitData::isLoaded()
    {
        if (m_data.size() == 0) return false;
        if (m_dataList.size() == 0) return false;

        return true;
    }

    tb::OutfitData::DataList* OutfitData::getDataList()
    {
        return &m_dataList;
    }

}
