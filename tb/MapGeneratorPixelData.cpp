#include "tb/MapGeneratorPixelData.h"

namespace tb
{

MapGeneratorPixelData::MapGeneratorPixelData()
{
    //
}

MapGeneratorPixelData::~MapGeneratorPixelData()
{
    //
}

bool MapGeneratorPixelData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    const std::uint32_t numGlyphs = tb::Constants::BitmapFonts::NumGlyphs;

    auto arrayOf = m_table["MapGeneratorPixel"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &numGlyphs, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::MapGeneratorPixelData::Data data;

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

            data.Type = arrayTable["Type"].value_or("");

            g_Log.write("Type: {}\n", data.Type);

            if (data.Type.size() == 0)
            {
                g_Log.write("ERROR: 'Type' is empty\n");
                foundError = true;
                return false;
            }

            data.Edge = arrayTable["Edge"].value_or("");

            g_Log.write("Edge: {}\n", data.Edge);

            if (data.Edge.size() == 0)
            {
                g_Log.write("INFO: 'Edge' is empty\n");
            }

            data.ColorR = arrayTable["ColorR"].value_or(0);
            data.ColorG = arrayTable["ColorG"].value_or(0);
            data.ColorB = arrayTable["ColorB"].value_or(0);

            g_Log.write("ColorR: {}\n", data.ColorR);
            g_Log.write("ColorG: {}\n", data.ColorG);
            g_Log.write("ColorB: {}\n", data.ColorB);

            if (data.ColorR > m_maxColorValue || data.ColorG > m_maxColorValue || data.ColorB > m_maxColorValue)
            {
                g_Log.write("ERROR: 'ColorR' or 'ColorG' or 'ColorB' is greater than {}\n", m_maxColorValue);
                foundError = true;
                return false;
            }

            // SpriteList

            tb::SpriteIDList spriteIDList;
            spriteIDList.reserve(m_numSpritesToReserve);

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

            // CornersSpriteList

            tb::SpriteIDList cornersSpriteIDList;
            cornersSpriteIDList.reserve(m_numCornerSpritesToReserve);

            auto cornersSpriteArray = arrayTable["CornersSpriteList"].as_array();

            if (cornersSpriteArray == nullptr)
            {
                g_Log.write("ERROR: 'CornersSpriteList' is nullptr\n");
                foundError = true;
                return false;
            }

            for (std::uint32_t cornersSpriteIndex = 0; auto& cornersSpriteNode : *cornersSpriteArray)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(cornersSpriteNode.value_or(tb::Constants::SpriteIDNull));
                if (spriteID == tb::Constants::SpriteIDNull)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: CornersSpriteList=[Index: {}]\n", cornersSpriteIndex);
                    foundError = true;
                    return false;
                }

                cornersSpriteIDList.push_back(spriteID);

                cornersSpriteIndex++;
            }

            data.CornersSpriteIDList = std::move(cornersSpriteIDList);

            if (data.CornersSpriteIDList.size() == 0)
            {
                g_Log.write("INFO: 'CornersSpriteList' is empty\n");
            }

            std::string cornerSpriteIDListAsString = fmt::format("{}", data.CornersSpriteIDList);

            g_Log.write("CornersSpriteList: {}\n", cornerSpriteIDListAsString);

            // EdgesSpriteList

            tb::SpriteIDList edgesSpriteIDList;
            edgesSpriteIDList.reserve(m_numEdgeSpritesToReserve);

            auto edgesSpriteArray = arrayTable["EdgesSpriteList"].as_array();

            if (edgesSpriteArray == nullptr)
            {
                g_Log.write("ERROR: 'EdgesSpriteList' is nullptr\n");
                foundError = true;
                return false;
            }

            for (std::uint32_t edgesSpriteIndex = 0; auto& edgesSpriteNode : *edgesSpriteArray)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(edgesSpriteNode.value_or(tb::Constants::SpriteIDNull));
                if (spriteID == tb::Constants::SpriteIDNull)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: EdgesSpriteList=[Index: {}]\n", edgesSpriteIndex);
                    foundError = true;
                    return false;
                }

                edgesSpriteIDList.push_back(spriteID);

                edgesSpriteIndex++;
            }

            data.EdgesSpriteIDList = std::move(edgesSpriteIDList);

            if (data.EdgesSpriteIDList.size() == 0)
            {
                g_Log.write("INFO: 'EdgesSpriteList' is empty\n");
            }

            std::string edgeSpriteIDListAsString = fmt::format("{}", data.EdgesSpriteIDList);

            g_Log.write("EdgesSpriteList: {}\n", edgeSpriteIDListAsString);

            //

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

bool MapGeneratorPixelData::isLoaded()
{
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::MapGeneratorPixelData::DataList* MapGeneratorPixelData::getDataList()
{
    return &m_dataList;
}

tb::MapGeneratorPixelData::Data* MapGeneratorPixelData::getDataByName(const std::string& name)
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
