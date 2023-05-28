#include "tb/AnimationData.h"

namespace tb
{

AnimationData::AnimationData()
{
    //
}

AnimationData::~AnimationData()
{
    //
}

bool AnimationData::load()
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
            continue;
        }

        g_Log.write("Index: {}\n", index);

        tb::AnimationData::Data data;

        data.Index = i;

        data.Name = m_table[index]["Name"].value_or("");

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        g_Log.write("Name: {}\n", data.Name);

        tb::SpriteIDList spriteIDList;
        spriteIDList.reserve(m_numSpritesPerAnimationToReserve);

        auto spritesArray = m_table[index]["Sprites"].as_array();

        if (spritesArray == nullptr)
        {
            g_Log.write("ERROR: spritesArray == nullptr\n");
            return false;
        }

        for (unsigned int j = 0; auto& spritesNode : *spritesArray)
        {
            tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(spritesNode.value_or(tb::Constants::SpriteIDNull));
            if (spriteID == tb::Constants::SpriteIDNull)
            {
                g_Log.write("ERROR: Sprite ID is zero at index: [{}] Sprites=[#{}]\n", i, j);
                return false;
            }

            spriteIDList.push_back(spriteID);
        }

        data.SpriteIDList = std::move(spriteIDList);

        if (data.SpriteIDList.size() == 0)
        {
            g_Log.write("ERROR: 'Sprites' is empty at index: [{}]\n", i);
            return false;
        }

        std::string spriteIDListStr = fmt::format("{}", data.SpriteIDList);

        g_Log.write("Sprites: {}\n", spriteIDListStr);

        m_dataList.push_back(data);
    }

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    return true;
}

bool AnimationData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::AnimationData::DataList* AnimationData::getDataList()
{
    return &m_dataList;
}

tb::AnimationData::Data* AnimationData::getDataByIndex(uint32_t index)
{
    return &m_dataList.at(index);
}

tb::AnimationData::Data* AnimationData::getDataByName(const std::string& name)
{
    for (auto& data : m_dataList)
    {
        if (data.Name == name)
        {
            return &data;
        }
    }

    return nullptr;
}

tb::AnimationData::Data* AnimationData::getDataByNameSV(std::string_view name)
{
    for (auto& data : m_dataList)
    {
        if (data.Name == name)
        {
            return &data;
        }
    }

    return nullptr;
}

}
