#include "common.h"

#include "tb/TextureRectData.h"

namespace tb
{

TextureRectData::TextureRectData()
{
    //
}

TextureRectData::~TextureRectData()
{
    //
}

bool TextureRectData::load()
{
    tb::LibTOML::LoadFileResult loadFileResult = tb::LibTOML::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    auto arrayOf = m_table["TextureRect"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::TextureRectData::Data data;

            data.Index = arrayIndex;

            g_Log.write("Index: {}\n", arrayIndex);

            data.TextureName = arrayTable["TextureName"].value_or("");

            g_Log.write("TextureName: {}\n", data.TextureName);

            data.Name = arrayTable["Name"].value_or("");

            g_Log.write("Name: {}\n", data.Name);

            if (data.Name.size() == 0)
            {
                g_Log.write("ERROR: 'Name' is empty\n");
                foundError = true;
                return false;
            }

            data.X = arrayTable["X"].value_or(0);
            data.Y = arrayTable["Y"].value_or(0);

            g_Log.write("X: {}\n", data.X);
            g_Log.write("Y: {}\n", data.Y);

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

            m_dataList.push_back(data);

            arrayIndex++;

            return true;
        }
    );

    if (foundError == true)
    {
        g_Log.write("ERROR: cannot load data because an error was found\n");
        return false;
    }

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: loaded data is empty\n");
        return false;
    }

    return true;
}

bool TextureRectData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::TextureRectData::Data* TextureRectData::getDataByIndex(std::uint32_t index)
{
    return &m_dataList.at(index);
}

tb::TextureRectData::Data* TextureRectData::getDataByName(const std::string& name)
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

tb::TextureRectData::Data* TextureRectData::getDataByNameSV(std::string_view name)
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

tb::TextureRectData::DataList* TextureRectData::getDataList()
{
    return &m_dataList;
}

}
