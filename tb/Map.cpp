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

Map::Properties_t* Map::getProperties()
{
    return &m_properties;
}

bool Map::load(const std::string& fileName)
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: Sprite data is not loaded\n");
        return false;
    }

    if (std::filesystem::exists(fileName) == false)
    {
        g_Log.write("ERROR: File does not exist: {}\n", fileName);
        return false;
    }

    g_Log.write("Loading map from file: {}\n", fileName);

    sf::Clock timeToLoadMap;

    pugi::xml_document xmlDocument;
    pugi::xml_parse_result xmlParseResult = xmlDocument.load_file(fileName.c_str());

    if (xmlParseResult.status != pugi::xml_parse_status::status_ok)
    {
        g_Log.write("ERROR: Failed to load map from file: {}\nDescription: {}\nOffset: {}\n", fileName, xmlParseResult.description(), xmlParseResult.offset);
        return false;
    }

    m_fileName = fileName;

    pugi::xml_node xmlNode_map = xmlDocument.child("map");
    if (xmlNode_map == NULL)
    {
        g_Log.write("ERROR: 'map' node not found\n");
        return false;
    }

    std::string_view orientation = xmlNode_map.attribute("orientation").as_string();

    if (orientation != "orthogonal")
    {
        g_Log.write("ERROR: In Tiled Editor, under Map Properties, 'Orientation' must equal 'Orthogonal'\n");
        return false;
    }

    std::string_view tileRenderOrder = xmlNode_map.attribute("renderorder").as_string();

    if (tileRenderOrder != "right-down")
    {
        g_Log.write("ERROR: In Tiled Editor, under Map Properties, 'Tile Render Order' must equal 'Right Down'\n");
        return false;
    }

    uint32_t tileSizeX = xmlNode_map.attribute("tilewidth").as_uint(); // width of a single tile
    uint32_t tileSizeY = xmlNode_map.attribute("tileheight").as_uint(); // height of a single tile

    if (tileSizeX != tb::Constants::TileSize || tileSizeY != tb::Constants::TileSize)
    {
        g_Log.write("ERROR: In Tiled Editor, under Map Properties, 'Tile Width' and 'Tile Height' must equal '{}'\n", tb::Constants::TileSize);
        return false;
    }

    m_tileWidth = xmlNode_map.attribute("width").as_uint(); // number of tiles hortizontally
    m_tileHeight = xmlNode_map.attribute("height").as_uint(); // number of tiles vertically

    m_numTiles = m_tileWidth * m_tileHeight;

    m_pixelWidth = m_tileWidth * tb::Constants::TileSize;
    m_pixelHeight = m_tileHeight * tb::Constants::TileSize;

    m_numPixels = m_pixelWidth * m_pixelHeight;

    g_Log.write("Map size: {}x{} tiles ({} tiles total)\n", m_tileWidth, m_tileHeight, m_numTiles);
    g_Log.write("Map size: {}x{} pixels ({} pixels total)\n", m_pixelWidth, m_pixelHeight, m_numPixels);

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

        //g_Log.write("xml_node map_properties_property__name: {}\n", xmlNode_map_properties_property__name);
        //g_Log.write("xml_node map_properties_property__value: {}\n", xmlNode_map_properties_property__value);

        if (xmlNode_map_properties_property__name == "Name")
        {
            m_properties.Name = xmlNode_map_properties_property__value;
        }
        else if (xmlNode_map_properties_property__name == "Description")
        {
            m_properties.Description = xmlNode_map_properties_property__value;
        }
        else if (xmlNode_map_properties_property__name == "Author")
        {
            m_properties.Author = xmlNode_map_properties_property__value;
        }

        else if (xmlNode_map_properties_property__name == "PlayerStartX")
        {
            m_properties.PlayerStartX = xmlNode_map_properties_property.attribute("value").as_int();
        }
        else if (xmlNode_map_properties_property__name == "PlayerStartY")
        {
            m_properties.PlayerStartY = xmlNode_map_properties_property.attribute("value").as_int();
        }
        else if (xmlNode_map_properties_property__name == "PlayerStartZ")
        {
            m_properties.PlayerStartZ = static_cast<tb::ZAxis_t>(xmlNode_map_properties_property.attribute("value").as_uint());
        }
        else if (xmlNode_map_properties_property__name == "TimeOfDay")
        {
            auto timeOfDay = magic_enum::enum_cast<tb::TimeOfDay>(xmlNode_map_properties_property__value);

            if (timeOfDay.has_value() == true)
            {
                m_properties.TimeOfDay = timeOfDay.value();
            }
        }
    }

    pugi::xml_node xmlNode_map_group_node = xmlNode_map.child("group");
    if (xmlNode_map_group_node == NULL)
    {
        g_Log.write("ERROR: 'group' node not found\n");
        return false;
    }

    for (auto& xmlNode_map_group : xmlNode_map.children("group"))
    {
        std::string_view xmlNode_map_group__name = xmlNode_map_group.attribute("name").as_string();

        //g_Log.write("xml_node map_group__name: {}\n", xmlNode_map_group__name);

        tb::ZAxis_t tileMapZ = static_cast<tb::ZAxis_t>(xmlNode_map_group.attribute("name").as_uint()); // z-axis is the name of the Group Layer in Tiled Editor

        pugi::xml_node xmlNode_map_group_layer_node = xmlNode_map_group.child("layer");
        if (xmlNode_map_group_layer_node == NULL)
        {
            g_Log.write("ERROR: 'layer' node not found for 'group' with name: '{}'\n", xmlNode_map_group__name);
            return false;
        }

        for (auto& xmlNode_map_group_layer : xmlNode_map_group.children("layer"))
        {
            std::string xmlNode_map_group_layer__name = xmlNode_map_group_layer.attribute("name").as_string();

            //g_Log.write("xml_node map_group_layer__name: {}\n", xmlNode_map_group_layer__name);

            pugi::xml_node xmlNode_map_group_layer_data = xmlNode_map_group_layer.child("data");
            if (xmlNode_map_group_layer_data == NULL)
            {
                g_Log.write("ERROR: 'data' node not found\n");
                return false;
            }

            std::string xmlNode_map_group_layer_data__encoding = xmlNode_map_group_layer_data.attribute("encoding").value();

            bool isCompressed = false;

            pugi::xml_attribute xmlAttribute_map_group_layer_data__compression = xmlNode_map_group_layer_data.attribute("compression");
            if (xmlAttribute_map_group_layer_data__compression != NULL)
            {
                isCompressed = true;
            }

            if (isCompressed == true)
            {
                std::string_view xmlNode_map_group_layer_data__compression = xmlAttribute_map_group_layer_data__compression.value();

                if
                (
                    xmlNode_map_group_layer_data__encoding    != "base64" &&
                    xmlNode_map_group_layer_data__compression != "zlib"
                )
                {
                    g_Log.write("ERROR: Your map is compressed but may be using the wrong tile layer format'\n");
                    g_Log.write("ERROR: In Tiled Editor, under Map Properties, 'Tile Layer Format' must be 'Base64 (zlib compressed)'\n");
                    g_Log.write("ERROR: 'data' attribute 'encoding' must be 'base64' and 'data' attribute 'compression' must be 'zlib'\n");
                    return false;
                }
            }
            else
            {
                if (xmlNode_map_group_layer_data__encoding != "csv")
                {
                    g_Log.write("ERROR: Your map is NOT compressed but may be using the wrong tile layer format'\n");
                    g_Log.write("ERROR: In Tiled Editor, under Map Properties, 'Tile Layer Format' must be 'CSV'\n");
                    g_Log.write("ERROR: 'data' attribute 'encoding' must be 'csv' and 'data' attribute 'compression' must not exist\n");
                    return false;
                }
            }

            std::string xmlNode_map_group_layer_data__string = xmlNode_map_group_layer_data.text().get();

            if (xmlNode_map_group_layer_data__string.size() == 0)
            {
                g_Log.write("Skipping layer because size it is empty\n");
                continue;
            }

            // remove spaces and new lines
            tb::Utility::String::removeWhiteSpace(xmlNode_map_group_layer_data__string);

            tb::SpriteIDList tileSpriteIDList;

            if (isCompressed == true)
            {
                // Tile Layer Format: Base64 (zlib compressed)

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
                    g_Log.write("Skipping layer because it is empty\n");
                    continue;
                }

                std::istringstream xmlNode_map_group_layer_data__istringstream(xmlNode_map_group_layer_data__string);

                tileSpriteIDList.reserve(xmlNode_map_group_layer_data__string.size() / 4);

                for (std::size_t i = 0; i < xmlNode_map_group_layer_data__string.size(); i += 4)
                {
                    uint32_t tileSpriteID;
                    xmlNode_map_group_layer_data__istringstream.read(reinterpret_cast<char*>(&tileSpriteID), 4);

                    tileSpriteIDList.push_back((tb::SpriteID_t)tileSpriteID);
                }
            }
            else
            {
                // Tile Layer Format: CSV (comma seperated values)

                tileSpriteIDList.reserve(m_numTiles);

                // split string by commas and convert to integer
                std::string token;
                std::istringstream tokenStream(xmlNode_map_group_layer_data__string);
                while (std::getline(tokenStream, token, ','))
                {
                    tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(std::stoi(token));

                    //g_Log.write("spriteID: {}\n", spriteID);

                    tileSpriteIDList.push_back(spriteID);
                }
            }

            if (tileSpriteIDList.size() == 0)
            {
                g_Log.write("Skipping layer because tile sprite id list is empty\n");
                continue;
            }

            tb::TileMapType tileMapType = tb::TileMapType::Tiles;

            //skip this because "Tiles" is the default
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

        pugi::xml_node xmlNode_map_group_objectgroup_node = xmlNode_map_group.child("objectgroup");

        if (xmlNode_map_group_objectgroup_node != NULL)
        {
            for (auto& xmlNode_map_group_objectgroup : xmlNode_map_group.children("objectgroup"))
            {
                std::string_view xmlNode_map_group_objectgroup__name = xmlNode_map_group_objectgroup.attribute("name").as_string();

                //g_Log.write("xmlNode_map_group_objectgroup__name: {}\n", xmlNode_map_group_objectgroup__name);

                tb::MapObjectLayerType mapObjectLayerType = tb::MapObjectLayerType::Objects;

                // skip this becaues "Objects" is the default
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
                    tb::SpriteID_t objectSpriteID = static_cast<tb::SpriteID_t>(xmlNode_map_group_objectgroup_object.attribute("gid").as_uint());

                    //g_Log.write("object sprite ID: {}\n", objectSpriteID);

                    sf::Vector2f objectPixelCoords;

                    objectPixelCoords.x = xmlNode_map_group_objectgroup_object.attribute("x").as_float();
                    objectPixelCoords.y = xmlNode_map_group_objectgroup_object.attribute("y").as_float();

                    //g_Log.write("object pixel coords: {}x{}\n", objectPixelCoords.x, objectPixelCoords.y);

                    uint32_t objectTileIndex = getTileIndexByPixelCoords(objectPixelCoords);

                    sf::Vector2i objectTileCoords = getTileCoordsByPixelCoords(objectPixelCoords);

                    //  this was an old bug in Tiled Editor that was fixed by Orientation and Tile Render Order
                    //tileCoords.y -= 1; // have to subtract one due to Tiled Editor

                    //g_Log.write("object tile coords: {}x{}\n", objectTileCoords.x, objectTileCoords.y);

                    if (mapObjectLayerType == tb::MapObjectLayerType::Objects || mapObjectLayerType == tb::MapObjectLayerType::TileEdgeObjects)
                    {
                        tb::Object::Ptr object = std::make_shared<tb::Object>(objectTileCoords, tileMapZ, objectSpriteID);

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
                            g_Log.write("Skipping object because tileList is empty\n");
                            continue;
                        }

                        tb::Tile::Ptr tile = tileList->at(objectTileIndex);

                        if (tile == nullptr)
                        {
                            g_Log.write("Skipping object because tile == nullptr\n");
                            continue;
                        }

                        if (mapObjectLayerType == tb::MapObjectLayerType::Objects)
                        {
                            tile->addObject(object);
                        }
                        else if (mapObjectLayerType == tb::MapObjectLayerType::TileEdgeObjects)
                        {
                            tile->addTileEdgeObject(object);
                        }
                    }
                }
            }
        }
    }

    sf::Clock timeToApplyObjectPatterns;

    g_Log.write("Applying tile object patterns to tile maps...\n");

    for (unsigned int i = tb::ZAxis::Min; i < tb::ZAxis::Max; i++)
    {
        if (m_tileMapTiles[i].applyTileObjectPatterns() == false)
        {
            g_Log.write("ERROR: Failed to apply tile object patterns to tile map index: {}\n", i);
            return false;
        }
    }

    g_Log.write("Object patterns applied in {} seconds\n", timeToApplyObjectPatterns.getElapsedTime().asSeconds());

    g_Log.write("Map loaded in {} seconds\n", timeToLoadMap.getElapsedTime().asSeconds());

    return true;
}

uint32_t Map::getTileIndexByTileCoords(const sf::Vector2i& tileCoords)
{
    return tileCoords.x + (tileCoords.y * m_tileWidth);
}

uint32_t Map::getTileIndexByPixelCoords(const sf::Vector2f& pixelCoords)
{
    int tileX = 0;
    int tileY = 0;

    if (pixelCoords.x != 0.0f)
    {
        tileX = static_cast<int>(pixelCoords.x / tb::Constants::TileSizeFloat);
    }

    if (pixelCoords.y != 0.0f)
    {
        tileY = static_cast<int>(pixelCoords.y / tb::Constants::TileSizeFloat);
    }

    return tileX + (tileY * m_tileWidth);
}

sf::Vector2f Map::getPixelCoordsByTileCoords(const sf::Vector2i& tileCoords)
{
    sf::Vector2f pixelCoords;

    pixelCoords.x = static_cast<float>(tileCoords.x * tb::Constants::TileSize);
    pixelCoords.y = static_cast<float>(tileCoords.y * tb::Constants::TileSize);

    return pixelCoords;
}

sf::Vector2i Map::getTileCoordsByPixelCoords(const sf::Vector2f& pixelCoords)
{
    sf::Vector2i tileCoords;

    tileCoords.x = 0;
    tileCoords.y = 0;

    if (pixelCoords.x != 0.0f)
    {
        tileCoords.x = static_cast<int>(pixelCoords.x / tb::Constants::TileSizeFloat);
    }

    if (pixelCoords.y != 0.0f)
    {
        tileCoords.y = static_cast<int>(pixelCoords.y / tb::Constants::TileSizeFloat);
    }

    return tileCoords;
}

sf::Vector2i Map::getTileCoordsByTileIndex(uint32_t tileIndex)
{
    sf::Vector2i tileCoords;

    tileCoords.x = (tileIndex % m_tileWidth) * tb::Constants::TileSize;
    tileCoords.y = (tileIndex / m_tileHeight);

    return tileCoords;
}

sf::Vector2f Map::getPixelCoordsByTileIndex(uint32_t tileIndex)
{
    sf::Vector2i tileCoords = getTileCoordsByTileIndex(tileIndex);

    sf::Vector2f pixelCoords;

    pixelCoords.x = static_cast<float>(tileCoords.x * tb::Constants::TileSize);
    pixelCoords.y = static_cast<float>(tileCoords.x * tb::Constants::TileSize);

    return pixelCoords;
}

bool Map::isTileIndexOutOfBounds(uint32_t tileIndex)
{
    if (tileIndex > (m_numTiles - 1))
    {
        return true;
    }

    return false;
}

bool Map::isTileCoordsOutOfBounds(const sf::Vector2i& tileCoords)
{
    if (tileCoords.x > (m_tileWidth - tb::Constants::TileSize)) return true;
    if (tileCoords.y > (m_tileHeight - tb::Constants::TileSize)) return true;

    return false;
}

tb::Tile::Ptr Map::getTileOfThing(tb::Thing::Ptr thing)
{
    if (thing == nullptr)
    {
        return nullptr;
    }

    tb::Tile::List* tileList = m_tileMapTiles.at(thing->getZ()).getTileList();

    if (tileList->size() == 0)
    {
        return nullptr;
    }

    uint32_t tileIndex = getTileIndexByTileCoords(thing->getTileCoords());

    if (isTileIndexOutOfBounds(tileIndex) == true)
    {
        g_Log.write("ERROR: Tile index is out of bounds: {}\n", tileIndex);
        return nullptr;
    }

    return tileList->at(tileIndex);
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

tb::TileMap* Map::getTileMapTiles(tb::ZAxis_t z)
{
    return &m_tileMapTiles.at(z);
}

tb::TileMap* Map::getTileMapTileEdges(tb::ZAxis_t z)
{
    return &m_tileMapTileEdges.at(z);
}

}
