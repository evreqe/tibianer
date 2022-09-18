#include "tb/Map.h"

namespace tb
{

Map::Map()
{
    //
}

Map::~Map()
{
    //
}

bool Map::load(const std::string& fileName)
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("Sprite Data is not loaded\n");
        return false;
    }

    pugi::xml_document xmlDocument;
    pugi::xml_parse_result xmlParseResult = xmlDocument.load_file(fileName.c_str());

    g_Log.write("Loading map file: {}\n", fileName);

    if (xmlParseResult.status != pugi::xml_parse_status::status_ok)
    {
        g_Log.write("ERROR: Failed to load map file: {}\nDescription: {}\n", fileName, xmlParseResult.description());
        return false;
    }

    m_fileName = fileName;

    pugi::xml_node xmlNode_map = xmlDocument.first_child();

    std::string orientation = xmlNode_map.attribute("orientation").as_string();

    if (orientation != "orthogonal")
    {
        g_Log.write("ERROR: Failed to parse map file: in Tiled Editor, under Map Properties, 'Orientation' must equal 'Orthogonal'\n");
        return false;
    }

    std::string tileRenderOrder = xmlNode_map.attribute("renderorder").as_string();

    if (tileRenderOrder != "right-down")
    {
        g_Log.write("ERROR: Failed to parse map file: in Tiled Editor, under Map Properties, 'Tile Render Order' must equal 'Right Down'\n");
        return false;
    }

    uint32_t tileWidth = xmlNode_map.attribute("tilewidth").as_uint(); // width of a single tile
    uint32_t tileHeight = xmlNode_map.attribute("tileheight").as_uint(); // height of a single tile

    if (tileWidth != tb::Constants::TileSize || tileHeight != tb::Constants::TileSize)
    {
        g_Log.write("ERROR: Failed to parse map file: in Tiled Editor, under Map Properties, 'Tile Width' and 'Tile Height' must equal '{}'\n", tb::Constants::TileSize);
        return false;
    }

    uint32_t m_tileWidth = xmlNode_map.attribute("width").as_uint(); // width is number of tiles
    uint32_t m_tileHeight = xmlNode_map.attribute("height").as_uint(); // height is number of tiles

    m_numTiles = m_tileWidth * m_tileHeight;

    m_pixelWidth = m_tileWidth * tb::Constants::TileSize;
    m_pixelHeight = m_tileHeight * tb::Constants::TileSize;

    m_numPixels = m_pixelWidth * m_pixelHeight;

    tb::Variables::MapTileWidth = m_tileWidth;
    tb::Variables::MapTileHeight = m_tileHeight;

    tb::Variables::MapNumTiles = m_numTiles;

    tb::Variables::MapPixelWidth = m_pixelWidth;
    tb::Variables::MapPixelHeight = m_pixelHeight;

    tb::Variables::MapNumPixels = m_numPixels;

    g_Log.write("Map size: {}x{} tiles ({} tiles total)\n", m_tileWidth, m_tileHeight, m_numTiles);
    g_Log.write("Map size: {}x{} pixels ({} pixels total)\n", m_pixelWidth, m_pixelHeight, m_numPixels);

    auto xmlNode_map_properties = xmlNode_map.child("properties");
    if (xmlNode_map_properties == NULL)
    {
        g_Log.write("ERROR: failed to parse map: 'properties' field not found\n");
        return false;
    }

    for (auto& xmlNode_map_properties_property : xmlNode_map_properties.children("property"))
    {
        std::string xmlNode_map_properties_property__name = xmlNode_map_properties_property.attribute("name").as_string();
        std::string xmlNode_map_properties_property__value = xmlNode_map_properties_property.attribute("value").as_string();

        g_Log.write("xml_node map_properties_property__name: {}\n", xmlNode_map_properties_property__name);
        g_Log.write("xml_node map_properties_property__value: {}\n", xmlNode_map_properties_property__value);

        if (xmlNode_map_properties_property__name == "Name")
        {
            m_properties.Name = xmlNode_map_properties_property.attribute("value").as_string();
        }
        else if (xmlNode_map_properties_property__name == "Description")
        {
            m_properties.Description = xmlNode_map_properties_property.attribute("value").as_string();
        }
        else if (xmlNode_map_properties_property__name == "Author")
        {
            m_properties.Author = xmlNode_map_properties_property.attribute("value").as_string();
        }

        else if (xmlNode_map_properties_property__name == "PlayerStartX")
        {
            m_properties.PlayerStartX = xmlNode_map_properties_property.attribute("value").as_uint();
        }
        else if (xmlNode_map_properties_property__name == "PlayerStartY")
        {
            m_properties.PlayerStartY = xmlNode_map_properties_property.attribute("value").as_uint();
        }
        else if (xmlNode_map_properties_property__name == "PlayerStartZ")
        {
            m_properties.PlayerStartZ = (tb::ZAxis_t)xmlNode_map_properties_property.attribute("value").as_uint();
        }
        else if (xmlNode_map_properties_property__name == "TimeOfDay")
        {
            m_properties.TimeOfDay = (tb::TimeOfDay)xmlNode_map_properties_property.attribute("value").as_uint();
        }
    }

    auto xmlNode_map_group = xmlNode_map.child("group");
    if (xmlNode_map_group == NULL)
    {
        g_Log.write("ERROR: failed to parse map: 'group' field not found\n");
        return false;
    }

    for (auto& xmlNode_map_group : xmlNode_map.children("group"))
    {
        std::string xmlNode_map_group__name = xmlNode_map_group.attribute("name").as_string();

        g_Log.write("xml_node map_group__name: {}\n", xmlNode_map_group__name);

        tb::ZAxis_t tileMapZ = xmlNode_map_group.attribute("name").as_uint(); // z-axis is derived from the Group name;

        auto xmlNode_map_group_layer = xmlNode_map_group.child("layer");
        if (xmlNode_map_group_layer == NULL)
        {
            g_Log.write("ERROR: failed to parse map: 'layer' field not found for 'group' with name '{}'\n", xmlNode_map_group__name);
            return false;
        }

        for (auto& xmlNode_map_group_layer : xmlNode_map_group.children("layer"))
        {
            std::string xmlNode_map_group_layer__name = xmlNode_map_group_layer.attribute("name").as_string();

            g_Log.write("xml_node map_group_layer__name: {}\n", xmlNode_map_group_layer__name);

            auto xmlNode_map_group_layer_data = xmlNode_map_group_layer.child("data");
            if (xmlNode_map_group_layer_data == NULL)
            {
                g_Log.write("ERROR: failed to parse map: 'data' field not found\n");
                return false;
            }

            std::string xmlNode_map_group_layer_data__encoding = xmlNode_map_group_layer_data.attribute("encoding").value();
            std::string xmlNode_map_group_layer_data__compression = xmlNode_map_group_layer_data.attribute("compression").value();

            bool isTileLayerFormatCorrect = true;

            if
            (
                xmlNode_map_group_layer_data__encoding    != "base64" &&
                xmlNode_map_group_layer_data__compression != "zlib"
            )
            {
                isTileLayerFormatCorrect = false;
            }

            if (isTileLayerFormatCorrect == false)
            {
                g_Log.write("ERROR: failed to parse map: 'data' field 'encoding' must be 'base64' and 'data' field 'compression' must be 'zlib'\n");
                g_Log.write("ERROR: failed to parse map: in Tiled Editor, under Map Properties, 'Tile Layer Format' must be 'Base64 (zlib compressed)'\n");
                return false;
            }

            std::string xmlNode_map_group_layer_data__string = xmlNode_map_group_layer_data.text().get();

            if (xmlNode_map_group_layer_data__string.size() == 0)
            {
                g_Log.write("Skipping layer because size is zero\n");
                continue;
            }

            // remove spaces and new lines
            Utility::String::removeWhiteSpace(xmlNode_map_group_layer_data__string);

            // skip empty layers, huge performance boost
            if (xmlNode_map_group_layer_data__string == "eJztwQEBAAAAgJD+r+4ICgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGoADwAB")
            {
                g_Log.write("Skipping layer because the Base64 encoded string is empty\n");
                continue;
            }

            g_Log.write("Decoding Base64 encoding...\n");

            xmlNode_map_group_layer_data__string = boost_base64_decode(xmlNode_map_group_layer_data__string);

            g_Log.write("Decompressing zlib compression...\n");

            xmlNode_map_group_layer_data__string = boost_zlib_decompress_string(xmlNode_map_group_layer_data__string);

            if (xmlNode_map_group_layer_data__string.size() == 0)
            {
                g_Log.write("Skipping layer because size is zero\n");
                continue;
            }

            std::istringstream xmlNode_map_group_layer_data__istringstream(xmlNode_map_group_layer_data__string);

            tb::SpriteIDList tileSpriteIDList;
            tileSpriteIDList.reserve(xmlNode_map_group_layer_data__string.size() / 4);

            for (std::size_t i = 0; i < xmlNode_map_group_layer_data__string.size(); i += 4)
            {
                uint32_t tileSpriteID;
                xmlNode_map_group_layer_data__istringstream.read(reinterpret_cast<char*>(&tileSpriteID), 4);

                tileSpriteIDList.push_back((tb::SpriteID_t)tileSpriteID);
            }

            if (tileSpriteIDList.size() == 0)
            {
                g_Log.write("Skipping layer because tileSpriteIDList.size() == 0\n");
                continue;
            }

            tb::TileMapType tileMapType = tb::TileMapType::Tiles;

            //if (xmlNode_map_group_layer__name == "Tiles")
            //{
                //tileMapType = tb::TileMapType::Tiles;
            //}
            if (xmlNode_map_group_layer__name == "Tile Edges")
            {
                tileMapType = tb::TileMapType::TileEdges;
            }

            if (tileMapType == tb::TileMapType::Tiles)
            {
                m_tileMapTiles[tileMapZ].load(m_tileWidth, m_tileHeight, tileSpriteIDList, xmlNode_map_group_layer__name, tileMapType, tileMapZ);
            }
            else if (tileMapType == tb::TileMapType::TileEdges)
            {
                m_tileMapTileEdges[tileMapZ].load(m_tileWidth, m_tileHeight, tileSpriteIDList, xmlNode_map_group_layer__name, tileMapType, tileMapZ);
            }
        }

        auto xmlNode_map_group_objectgroup = xmlNode_map_group.child("objectgroup");
        if (xmlNode_map_group_objectgroup == NULL)
        {
            g_Log.write("ERROR: failed to parse map: 'objectgroup' field not found'\n");
            return false;
        }

        for (auto& xmlNode_map_group_objectgroup : xmlNode_map_group.children("objectgroup"))
        {
            std::string xmlNode_map_group_objectgroup__name = xmlNode_map_group_objectgroup.attribute("name").as_string();

            g_Log.write("xmlNode_map_group_objectgroup__name: {}\n", xmlNode_map_group_objectgroup__name);

            tb::MapObjectLayerType mapObjectLayerType = tb::MapObjectLayerType::Objects;

            //if (xmlNode_map_group_objectgroup__name == "Objects")
            //{
                //mapObjectLayerType = tb::MapObjectLayerType::Objects;
            //}
            if (xmlNode_map_group_objectgroup__name == "Tile Edge Objects")
            {
                mapObjectLayerType = tb::MapObjectLayerType::TileEdgeObjects;
            }
            else if (xmlNode_map_group_objectgroup__name == "Entities")
            {
                mapObjectLayerType = tb::MapObjectLayerType::Entities;
            }
            else if (xmlNode_map_group_objectgroup__name == "Creatures")
            {
                mapObjectLayerType = tb::MapObjectLayerType::Creatures;
            }

            // it is possible for 'objectgroup' to not containy any 'object'
            // so we can skip the NULL check

            for (auto& xmlNode_map_group_objectgroup_object : xmlNode_map_group_objectgroup.children("object"))
            {
                tb::SpriteID_t xmlNode_map_group_objectgroup_object__gid = xmlNode_map_group_objectgroup_object.attribute("gid").as_uint();

                uint32_t xmlNode_map_group_objectgroup_object__x = xmlNode_map_group_objectgroup_object.attribute("x").as_uint();
                uint32_t xmlNode_map_group_objectgroup_object__y = xmlNode_map_group_objectgroup_object.attribute("y").as_uint();

                sf::Vector2u pixelCoords(xmlNode_map_group_objectgroup_object__x, xmlNode_map_group_objectgroup_object__y);

                g_Log.write("object pixelCoords: {}x{}\n", pixelCoords.x, pixelCoords.y);

                uint32_t tileNumber = getTileNumberByPixelCoords(pixelCoords);

                sf::Vector2u tileCoords = getTileCoordsByPixelCoords(pixelCoords);

                //tileCoords.y -= 1; // have to subtract one due to Tiled Editor

                g_Log.write("object tileCoords: {}x{}\n", tileCoords.x, tileCoords.y);

                if (mapObjectLayerType == tb::MapObjectLayerType::Objects)
                {
                    tb::Object::Ptr object = std::make_shared<tb::Object>(tileCoords, tileMapZ, xmlNode_map_group_objectgroup_object__gid);

                    // TODO: get object type from sprite data
                    //tb::ObjectType objectType = x;
                    //object->setObjectType(objectType);

                    tb::TileMap* tileMap = &m_tileMapTiles[tileMapZ];

                    if (tileMap == nullptr)
                    {
                        g_Log.write("Skipping object because tileMap == nullptr\n");
                        continue;
                    }

                    tb::Tile::List* tileList = tileMap->getTileList();

                    if (tileList == nullptr)
                    {
                        g_Log.write("Skipping object because tileList == nullptr\n");
                        continue;
                    }

                    if (tileList->size() == 0)
                    {
                        g_Log.write("Skipping object because tileList->size() == 0\n");
                        continue;
                    }

                    tb::Tile::Ptr tile = tileList->at(tileNumber);

                    if (tile == nullptr)
                    {
                        g_Log.write("Skipping object because tile == nullptr\n");
                        continue;
                    }

                    tile->addObject(object);
                }
            }
        }
    }
    g_Log.write("Applying tile object patterns to tile maps...\n");
    for (unsigned int i = tb::ZAxis::Min; i < tb::ZAxis::Max; i++)
    {
        if (m_tileMapTiles[i].applyTileObjectPatterns() == false)
        {
            g_Log.write("ERROR: Failed to apply tile object patterns to tile map index: {}\n", i);
            return false;
        }
    }

    return true;
}

bool Map::isTileNumberOutOfBounds(uint32_t tileNumber)
{
    if (tileNumber > (m_numTiles - 1))
    {
        return true;
    }

    return false;
}

bool Map::isTileCoordsOutOfBounds(const sf::Vector2u& tileCoords)
{
    if (tileCoords.x > (m_tileWidth  - tb::Constants::TileSize)) return true;
    if (tileCoords.y > (m_tileHeight - tb::Constants::TileSize)) return true;

    return false;
}

const std::string& Map::getFileName()
{
    return m_fileName;
}

uint32_t Map::getPixelWidth()
{
    return m_pixelWidth;
}

uint32_t Map::getPixelHeight()
{
    return m_pixelHeight;
}

uint32_t Map::getNumPixels()
{
    return m_numPixels;
}

uint32_t Map::getTileWidth()
{
    return m_tileWidth;
}

uint32_t Map::getTileHeight()
{
    return m_tileHeight;
}

uint32_t Map::getNumTiles()
{
    return m_numTiles;
}

tb::Map::Properties_t* Map::getProperties()
{
    return &m_properties;
}

tb::TileMap* Map::getTileMapTiles(tb::ZAxis_t z)
{
    return &m_tileMapTiles.at(z);
}

tb::TileMap* Map::getTileMapTileEdges(tb::ZAxis_t z)
{
    return &m_tileMapTileEdges.at(z);
}

}
