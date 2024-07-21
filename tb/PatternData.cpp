#include "tb/PatternData.h"

namespace tb
{

PatternData::PatternData()
{
    //
}

PatternData::~PatternData()
{
    //
}

bool PatternData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    auto arrayOf = m_table["Pattern"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::PatternData::Data data;

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

            std::string_view patternType = arrayTable["Type"].value_or("");

            auto patternTypeE = magic_enum::enum_cast<tb::PatternType>(patternType);
            if (patternTypeE.has_value())
            {
                data.PatternType = patternTypeE.value();

                g_Log.write("Type: {}\n", magic_enum::enum_name(patternTypeE.value()));
            }
            else
            {
                g_Log.write("ERROR: 'Type' is unknown\n");
                foundError = true;
                return false;
            }

            data.Width = arrayTable["Width"].value_or(0);
            data.Height = arrayTable["Height"].value_or(0);

            g_Log.write("Width: {}\n", data.Width);
            g_Log.write("Height: {}\n", data.Height);

            if (data.Width == 0 || data.Height == 0)
            {
                g_Log.write("ERROR: 'Width' or 'Height' is zero\n");
                foundError = true;
                return false;
            }

            std::uint32_t numSpritesRequired = data.Width * data.Height;

            data.SpriteIDList.reserve(numSpritesRequired);

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
                    g_Log.write("ERROR: Sprite ID is zero: SpriteList=[Index: {}]\n", spriteIndex);
                    foundError = true;
                    return false;
                }

                data.SpriteIDList.push_back(spriteID);

                spriteIndex++;
            }

            if (data.SpriteIDList.size() == 0)
            {
                g_Log.write("ERROR: 'SpriteList' is empty\n");
                foundError = true;
                return false;
            }

            if (data.SpriteIDList.size() != numSpritesRequired)
            {
                g_Log.write("ERROR: 'SpriteList' has the wrong size, {} instead of {}\n", data.SpriteIDList.size(), numSpritesRequired);
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

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: Loaded data is empty\n");
        return false;
    }

    return true;
}

bool PatternData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

bool PatternData::save()
{
    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: Cannot save data because it is empty\n");
        return false;
    }

    std::fstream file;
    file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

    if (file.is_open() == false)
    {
        g_Log.write("ERROR: Cannot open file: {}\n", m_fileName);
        return false;
    }

    for (auto& data : m_dataList)
    {
        file << std::format("[{}]\n", data.Index);

        file << std::format("Name=\"{}\"\n", data.Name);

        std::string_view patternTypeString = magic_enum::enum_name(data.PatternType);
        if (patternTypeString.size() == 0)
        {
            g_Log.write("ERROR: 'PatternType' is empty\n");
            return false;
        }

        file << std::format("Type=\"{}\"\n", patternTypeString);

        file << std::format("Width={}\n", data.Width);
        file << std::format("Height={}\n", data.Height);

        file << "Sprites=[";

        std::uint32_t spriteIndex = 0;

        for (auto& spriteID : data.SpriteIDList)
        {
            file << spriteID;

            if (spriteIndex != data.SpriteIDList.size())
            {
                file << ",";
            }

            spriteIndex++;
        }

        file << "]\n";
    }

    file.close();

    g_Log.write("Saved data to file: {}\n", m_fileName);

    return true;
}

tb::PatternData::DataList* PatternData::getDataList()
{
    return &m_dataList;
}

}
