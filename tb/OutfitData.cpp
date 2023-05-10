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

    m_table.clear();

    try
    {
        m_table = toml::parse_file(m_fileName);
    }
    catch (const toml::parse_error& parseError)
    {
        g_Log.write("ERROR: Failed to load data from file: {}\n", m_fileName);
        g_Log.write("Description: {}\nLine: {}\nColumn: {}\n", parseError.description(), parseError.source().begin.line, parseError.source().begin.column);
        return false;
    }

    g_Log.write("Loaded data from file: {}\n", m_fileName);

    m_dataList.clear();
    m_dataList.reserve(m_numToLoad);

    for (unsigned int i = 0; i < m_numToLoad; i++)
    {
        std::string index = std::to_string(i);

        if (!m_table[index])
        {
            g_Log.write("ERROR: {} is missing data at index: [{}]\n", m_fileName, i);
            return false;
        }

        g_Log.write("Index: {}\n", index);

        tb::OutfitData::Data data;
        data.SpriteIDList_List.reserve(m_numSpriteIDListToLoadPerIndex);

        data.Index = i;

        data.Name = m_table[index]["Name"].value_or("");

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        g_Log.write("Name: {}\n", data.Name);

        for (unsigned int j = 0; j < m_numSpriteIDListToLoadPerIndex; j++)
        {
            std::string spritesIndex = std::format("Sprites{}", j);

            if (!m_table[index][spritesIndex])
            {
                break;
            }

            //g_Log.write("Sprites# index: {}\n", j);

            auto spritesArray = m_table[index][spritesIndex].as_array();

            if (spritesArray == nullptr)
            {
                g_Log.write("ERROR: spritesArray == nullptr\n");
                return false;
            }

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(tb::Constants::NumOutfitSpriteDirections);

            for (unsigned int k = 0; auto& spritesNode : *spritesArray)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(spritesNode.value_or(0));
                if (spriteID == 0)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: [{}] Sprites{}=[#{}]\n", i, j, k);
                    return false;
                }

                spriteIDList.push_back(spriteID);
            }

            if (spriteIDList.size() == 0)
            {
                g_Log.write("ERROR: 'Sprites#' is empty at index: [{}] Sprites{}\n", i, j);
                return false;
            }

            if (spriteIDList.size() != tb::Constants::NumOutfitSpriteDirections)
            {
                g_Log.write("ERROR: 'Sprites#' has the wrong size at index: [{}] Sprites{}\n", i, j);
                g_Log.write("----> {} instead of {}\n", spriteIDList.size(), tb::Constants::NumOutfitSpriteDirections);
                return false;
            }

            std::string spriteIDListStr = fmt::format("{}", spriteIDList);

            g_Log.write("{}: {}\n", spritesIndex, spriteIDListStr);

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
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::OutfitData::DataList* OutfitData::getDataList()
{
    return &m_dataList;
}

}
