#include "tb/MapData.h"

namespace tb
{

MapData::MapData()
{
    //
}

MapData::~MapData()
{
    //
}

bool MapData::load()
{
    std::vector<std::string> folderNameList;

    for (const auto& directoryEntry : std::filesystem::directory_iterator("maps/"))
    {
        if (directoryEntry.is_directory() == true)
        {
            std::string folderName = std::format("{}/", directoryEntry.path().string());

            g_Log.write("Folder Name: {}\n", folderName);

            folderNameList.push_back(folderName);
        }
    }

    std::vector<std::string> fileNameList;

    for (auto& folderName : folderNameList)
    {
        for (const auto& directoryEntry : std::filesystem::directory_iterator(folderName))
        {
            if (directoryEntry.is_regular_file() == true)
            {
                if (directoryEntry.path().extension().string() == m_mapFileNameExtension)
                {
                    std::string fileName = directoryEntry.path().string();

                    g_Log.write("File Name: {}\n", fileName);

                    fileNameList.push_back(fileName);
                }
            }
        }
    }

    // TODO: check if more than one .tmx file exists

    // TODO: other folders inside the map's folder such as scripts, sounds, music, etc

    m_dataList.clear();
    m_dataList.reserve(fileNameList.size());

    for (auto& fileName : fileNameList)
    {
        if (std::filesystem::exists(fileName) == false)
        {
            g_Log.write("ERROR: File does not exist: {}\n", fileName);
            return false;
        }

        pugi::xml_document xmlDocument;
        pugi::xml_parse_result xmlParseResult = xmlDocument.load_file(fileName.c_str());

        if (xmlParseResult.status != pugi::xml_parse_status::status_ok)
        {
            g_Log.write("ERROR: Failed to load map from file: {}\nDescription: {}\nOffset: {}\n", fileName, xmlParseResult.description(), xmlParseResult.offset);
            return false;
        }

        g_Log.write("Loaded data from file: {}\n", fileName);

        tb::MapData::Data data;

        data.FileName = fileName;

        g_Log.write("FileName: {}\n", data.FileName);

        pugi::xml_node xmlNode_map = xmlDocument.child("map");
        if (xmlNode_map == NULL)
        {
            g_Log.write("ERROR: 'map' node not found\n");
            return false;
        }

        data.TileWidth = xmlNode_map.attribute("width").as_uint(); // number of tiles hortizontally
        data.TileHeight = xmlNode_map.attribute("height").as_uint(); // number of tiles vertically

        g_Log.write("TileWidth: {}\n", data.TileWidth);
        g_Log.write("TileHeight: {}\n", data.TileHeight);

        pugi::xml_node xmlNode_map_properties = xmlNode_map.child("properties");
        if (xmlNode_map_properties == NULL)
        {
            g_Log.write("ERROR: 'properties' node not found\n");
            return false;
        }

        for (auto& xmlNode_map_properties_property : xmlNode_map_properties.children("property"))
        {
            std::string_view xmlNode_map_properties_property__name = xmlNode_map_properties_property.attribute("name").as_string();
            std::string_view xmlNode_map_properties_property__value = xmlNode_map_properties_property.attribute("value").as_string();

            if (xmlNode_map_properties_property__name == "Name")
            {
                data.Name = xmlNode_map_properties_property__value;

                g_Log.write("Name: {}\n", data.Name);
            }
            else if (xmlNode_map_properties_property__name == "Description")
            {
                data.Description = xmlNode_map_properties_property__value;

                g_Log.write("Description: {}\n", data.Description);
            }
            else if (xmlNode_map_properties_property__name == "Author")
            {
                data.Author = xmlNode_map_properties_property__value;

                g_Log.write("Author: {}\n", data.Author);
            }
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

bool MapData::isLoaded()
{
    if (m_dataList.size() == 0)
    {
        return false;
    }

    return true;
}

tb::MapData::Data* MapData::getDataByFileName(const std::string& fileName)
{
    for (auto& data : m_dataList)
    {
        if (data.FileName == fileName)
        {
            return &data;
        }
    }

    return nullptr;
}

tb::MapData::Data* MapData::getDataByName(const std::string& name)
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

tb::MapData::DataList* MapData::getDataList()
{
    return &m_dataList;
}

}
