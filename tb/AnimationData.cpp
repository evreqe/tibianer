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
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    auto arrayOf = m_table["Animation"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::AnimationData::Data data;

            data.Index = arrayIndex;

            g_Log.write("Index: {}\n", arrayIndex);

            data.Name = arrayTable["Name"].value_or("");

            g_Log.write("Name: {}\n", data.Name);

            if (data.Name.size() == 0)
            {
                g_Log.write("ERROR: 'Name' is empty\n");
                foundError = true;
                return false;
            }

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(m_numSpritesPerAnimationToReserve);

            auto spriteArray = arrayTable["SpriteList"].as_array();

            if (spriteArray == nullptr)
            {
                g_Log.write("ERROR: 'SpriteList' is nullptr\n");
                foundError = true;
                return false;
            }

            for (std::uint32_t spriteIndex = 0; auto& spriteNode : *spriteArray)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(spriteNode.value_or(tb::Constants::SpriteIDNull));
                if (spriteID == tb::Constants::SpriteIDNull)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: SpriteList=[Index: {}]\n", spriteIndex);
                    foundError = true;
                    return false;
                }

                spriteIDList.push_back(spriteID);

                spriteIndex++;
            }

            data.SpriteIDList = std::move(spriteIDList);

            if (data.SpriteIDList.size() == 0)
            {
                g_Log.write("ERROR: 'SpriteList' is empty\n");
                foundError = true;
                return false;
            }

            std::string spriteIDListAsString = fmt::format("{}", data.SpriteIDList);

            g_Log.write("SpriteList: {}\n", spriteIDListAsString);

            m_dataList.push_back(data);

            arrayIndex++;

            return true;
        }
    );

    if (foundError == true)
    {
        g_Log.write("ERROR: Cannot load data because an error was found\n");
        return false;
    }

    g_Log.write("Loaded data list size: {}\n", m_dataList.size());

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

tb::AnimationData::Data* AnimationData::getDataByIndex(std::uint32_t index)
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
