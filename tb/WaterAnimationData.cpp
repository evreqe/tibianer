#include "tb/WaterAnimationData.h"

namespace tb
{

WaterAnimationData::WaterAnimationData()
{
    //
}

WaterAnimationData::~WaterAnimationData()
{
    //
}

bool WaterAnimationData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_spriteIDList_List.clear();
    m_spriteIDList_List.reserve(m_numToLoad);

    for (std::uint32_t i = 0; i < m_numToLoad; i++)
    {
        std::string index = std::to_string(i);

        if (!m_table[index])
        {
            g_Log.write("ERROR: '{}' is missing data at index: [{}]\n", m_fileName, i);
            return false;
        }

        g_Log.write("Index: {}\n", index);

        tb::SpriteIDList spriteIDList;
        spriteIDList.reserve(tb::Constants::NumWaterSpritesPerAnimationFrame);

        auto spriteArray = m_table[index]["SpriteList"].as_array();

        if (spriteArray == nullptr)
        {
            g_Log.write("ERROR: 'SpriteList' is nullptr\n");
            return false;
        }

        for (std::uint32_t spriteIndex = 0; auto& spriteNode : *spriteArray)
        {
            tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(spriteNode.value_or(tb::Constants::SpriteIDNull));
            if (spriteID == tb::Constants::SpriteIDNull)
            {
                g_Log.write("ERROR: Sprite ID is zero at index: SpriteList=[Index: {}]\n", spriteIndex);
                return false;
            }

            spriteIDList.push_back(spriteID);

            spriteIndex++;
        }

        if (spriteIDList.size() == 0)
        {
            g_Log.write("ERROR: 'SpriteList' is empty\n");
            return false;
        }

        if (spriteIDList.size() != tb::Constants::NumWaterSpritesPerAnimationFrame)
        {
            g_Log.write("ERROR: 'SpriteList' has the wrong size, size is {} instead of {}\n", spriteIDList.size(), tb::Constants::NumWaterSpritesPerAnimationFrame);
            return false;
        }

        std::string spriteIDListAsString = fmt::format("{}", spriteIDList);

        g_Log.write("SpriteList: {}\n", spriteIDListAsString);

        m_spriteIDList_List.push_back(spriteIDList);
    }

    g_Log.write("Loaded data size: {}\n", m_spriteIDList_List.size());

    if (m_spriteIDList_List.size() != tb::Constants::NumWaterAnimationFrames)
    {
        g_Log.write("ERROR: Loaded data has the wrong size, size is {} instead of {}\n", m_spriteIDList_List.size(), tb::Constants::NumWaterAnimationFrames);
        return false;
    }

/*
    g_Log.write("Sprite ID list list:\n");

    for (auto& spriteIDListEx : m_spriteIDList_List)
    {
        g_Log.write("--> Sprite ID list:\n");

        for (auto& spriteID : spriteIDListEx)
        {
            g_Log.write("----> Sprite ID: {}\n", spriteID);
        }
    }
*/

    return true;
}

bool WaterAnimationData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_spriteIDList_List.size() == 0) return false;

    return true;
}

std::vector<tb::SpriteIDList>* WaterAnimationData::getSpriteIDList_List()
{
    return &m_spriteIDList_List;
}

}
