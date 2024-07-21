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
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    auto arrayOf = m_table["Cursor"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::CursorData::Data data;

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

            data.FileName = arrayTable["FileName"].value_or("");

            g_Log.write("FileName: {}\n", data.FileName);

            if (data.FileName.size() == 0)
            {
                g_Log.write("ERROR: 'FileName' is empty\n");
                foundError = true;
                return false;
            }

            if (data.Image.loadFromFile(data.FileName) == false)
            {
                g_Log.write("ERROR: Failed to load image from file: {}\n", data.FileName);
                foundError = true;
                return false;
            }

            sf::Vector2u imageSize = data.Image.getSize();

            g_Log.write("Image size: {}x{}\n", imageSize.x, imageSize.y);

            if (imageSize.x == 0 || imageSize.y == 0)
            {
                g_Log.write("ERROR: Image size 'Width' or 'Height' is zero\n");
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

            if (data.Width != imageSize.x || data.Height != imageSize.y)
            {
                g_Log.write("ERROR: 'Width' or 'Height' does not match image size from file: {}\n", data.FileName);
                foundError = true;
                return false;
            }

            data.HotSpotX = arrayTable["HotSpotX"].value_or(0);
            data.HotSpotY = arrayTable["HotSpotY"].value_or(0);

            g_Log.write("HotSpotX: {}\n", data.HotSpotX);
            g_Log.write("HotSpotY: {}\n", data.HotSpotY);

            if (data.HotSpotX > imageSize.x || data.HotSpotY > imageSize.y)
            {
                g_Log.write("ERROR: 'HotSpotX' or 'HotSpotY' is out of bounds of image size from file: {}\n", data.FileName);
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

    g_Log.write("Loaded data list size: {}\n", m_dataList.size());

    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: Loaded data list is empty\n");
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

tb::CursorData::Data* CursorData::getDataByNameSV(std::string_view name)
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
