#include "tb/GuiRectData.h"

namespace tb
{

GuiRectData::GuiRectData()
{
    //
}

GuiRectData::~GuiRectData()
{
    //
}

bool GuiRectData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    auto arrayOf = m_table["GuiRect"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::GuiRectData::Data data;

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

bool GuiRectData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::GuiRectData::Data* GuiRectData::getDataByIndex(std::uint32_t index)
{
    return &m_dataList.at(index);
}

tb::GuiRectData::Data* GuiRectData::getDataByName(const std::string& name)
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

tb::GuiRectData::Data* GuiRectData::getDataByNameSV(std::string_view name)
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

tb::GuiRectData::DataList* GuiRectData::getDataList()
{
    return &m_dataList;
}

}
