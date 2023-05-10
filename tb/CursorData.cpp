#include "tb/CursorData.h"

namespace tb
{

CursorData::CursorData()
{
    //
}

CursorData::~CursorData()
{
    //
}

bool CursorData::load()
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

        tb::CursorData::Data data;

        data.Index = i;

        data.Name = m_table[index]["Name"].value_or("");

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        g_Log.write("FileName: {}\n", data.FileName);
        data.FileName = m_table[index]["FileName"].value_or("");

        if (data.FileName.size() == 0)
        {
            g_Log.write("ERROR: 'FileName' is empty\n");
            return false;
        }

        g_Log.write("FileName: {}\n", data.FileName);

        if (data.Image.loadFromFile(data.FileName) == false)
        {
            g_Log.write("ERROR: Failed to load image from file: {}\n", data.FileName);
            return false;
        }

        sf::Vector2u imageSize = data.Image.getSize();

        g_Log.write("Image size: {}x{}\n", imageSize.x, imageSize.y);

        data.Width = m_table[index]["Width"].value_or(0);
        data.Height = m_table[index]["Height"].value_or(0);

        if (data.Width == 0 || data.Height == 0)
        {
            g_Log.write("ERROR: 'Width' or 'Height' is zero\n");
            return false;
        }

        g_Log.write("Width: {}\n", data.Width);
        g_Log.write("Height: {}\n", data.Height);

        if (data.Width != imageSize.x || data.Height != imageSize.y)
        {
            g_Log.write("ERROR: 'Width' or 'Height' does not match image size\n");
            return false;
        }

        data.HotSpotX = m_table[index]["HotSpotX"].value_or(0);
        data.HotSpotY = m_table[index]["HotSpotY"].value_or(0);

        g_Log.write("HotSpotX: {}\n", data.HotSpotX);
        g_Log.write("HotSpotY: {}\n", data.HotSpotY);

        if (data.HotSpotX > imageSize.x || data.HotSpotY > imageSize.y)
        {
            g_Log.write("ERROR: 'HotSpotX' or 'HotSpotY' is out of bounds of image size\n");
            return false;
        }

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

bool CursorData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::CursorData::Data* CursorData::getDataByName(const std::string& name)
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

tb::CursorData::DataList* CursorData::getDataList()
{
    return &m_dataList;
}

}
