#include "tb/TextureData.h"

namespace tb
{

TextureData::TextureData()
{
    //
}

TextureData::~TextureData()
{
    //
}

bool TextureData::load()
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
            break;
        }

        g_Log.write("Index: {}\n", index);

        tb::TextureData::Data data;

        data.Index = i;

        data.Name = m_table[index]["Name"].value_or("");

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        g_Log.write("Name: {}\n", data.Name);

        data.FileName = m_table[index]["FileName"].value_or("");

        if (data.FileName.size() == 0)
        {
            g_Log.write("ERROR: 'FileName' is empty\n");
            return false;
        }

        g_Log.write("FileName: {}\n", data.FileName);

        data.Width = m_table[index]["Width"].value_or(0);
        data.Height = m_table[index]["Height"].value_or(0);

        if (data.Width == 0 || data.Height == 0)
        {
            g_Log.write("ERROR: 'Width' or 'Height' is zero\n");
            return false;
        }

        g_Log.write("Width: {}\n", data.Width);
        g_Log.write("Height: {}\n", data.Height);

        data.Repeated = m_table[index]["Repeated"].value_or(false);

        g_Log.write("Repeated: {}\n", data.Repeated);

        m_dataList.push_back(data);
    }

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: Loaded data is empty\n");
        return false;
    }

    return true;
}

bool TextureData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::TextureData::Data* TextureData::getDataByName(const std::string& name)
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

tb::TextureData::DataList* TextureData::getDataList()
{
    return &m_dataList;
}

}
