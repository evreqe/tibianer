#include "tb/OutfitSpritesData.h"

namespace tb
{

OutfitSpritesData::OutfitSpritesData()
{
    //
}

OutfitSpritesData::~OutfitSpritesData()
{
    //
}

bool OutfitSpritesData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToLoad);

    for (std::uint32_t i = 0; i < m_numToLoad; i++)
    {
        std::string index = std::to_string(i);

        if (!m_table[index])
        {
            g_Log.write("ERROR: {} is missing data at index: [{}]\n", m_fileName, i);
            return false;
        }

        tb::OutfitSpritesData::Data data;
        data.SpriteIDList_List.reserve(m_numSpriteIDListToLoadPerIndex);

        data.Index = i;

        g_Log.write("Index: {}\n", index);

        data.Name = m_table[index]["Name"].value_or("");

        g_Log.write("Name: {}\n", data.Name);

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        for (std::uint32_t spriteListIndex = 0; spriteListIndex < m_numSpriteIDListToLoadPerIndex; spriteListIndex++)
        {
            std::string spriteListIndexAsString = std::format("SpriteList{}", spriteListIndex);

            if (!m_table[index][spriteListIndexAsString])
            {
                break;
            }

            auto spriteArray = m_table[index][spriteListIndexAsString].as_array();

            if (spriteArray == nullptr)
            {
                g_Log.write("ERROR: 'SpriteList#' is nullptr\n");
                return false;
            }

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(tb::Constants::NumOutfitSpriteDirections);

            for (unsigned int spriteIndex = 0; auto& spriteNode : *spriteArray)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(spriteNode.value_or(tb::Constants::SpriteIDNull));
                if (spriteID == tb::Constants::SpriteIDNull)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: SpriteList{}=[Index: {}]\n", spriteListIndex, spriteIndex);
                    return false;
                }

                spriteIDList.push_back(spriteID);
            }

            if (spriteIDList.size() == 0)
            {
                g_Log.write("ERROR: 'SpriteList#' is empty at index: SpriteList{}\n", spriteListIndex);
                return false;
            }

            if (spriteIDList.size() != tb::Constants::NumOutfitSpriteDirections)
            {
                g_Log.write("ERROR: 'SpriteList#' has the wrong size at index: SpriteList{}\n", spriteListIndex);
                g_Log.write("----> size is {} instead of {}\n", spriteIDList.size(), tb::Constants::NumOutfitSpriteDirections);
                return false;
            }

            std::string spriteIDListAsString = fmt::format("{}", spriteIDList);

            g_Log.write("SpriteList{}: {}\n", spriteListIndex, spriteIDListAsString);

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

bool OutfitSpritesData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::OutfitSpritesData::DataList* OutfitSpritesData::getDataList()
{
    return &m_dataList;
}

}
