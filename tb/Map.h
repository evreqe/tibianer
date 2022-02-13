#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/replace_if.hpp>
#include <boost/range/algorithm/remove_if.hpp>

#include "boost_base64.hpp"
#include "boost_zlib.hpp"

#include "pugixml.hpp"

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"
//#include "tb/Script.hpp"
#include "tb/TileMap.hpp"
#include "tb/Object.hpp"
//#include "tb/Creature.hpp"

namespace tb
{

class Map
{

public:

    struct Properties_t
    {
        std::string Name;
        std::string Author;
        std::string Description;

        uint32_t PlayerStartX = 0;
        uint32_t PlayerStartY = 0;
        tb::ZAxis_t PlayerStartZ = tb::ZAxis::Default;

        tb::TimeOfDay TimeOfDay = tb::TimeOfDay::Day;
    };

    Properties_t properties;

    tb::TileMap tileMapTiles[tb::Constants::NumZAxis];
    tb::TileMap tileMapTileEdges[tb::Constants::NumZAxis];

    bool load(const std::string& fileName)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result loadResult = doc.load_file(fileName.c_str());

        if (loadResult == pugi::xml_parse_status::status_ok)
        {
            std::cout << "Error: failed to load map: " << loadResult.description() << "\n";
            return false;
        }

        m_fileName = fileName;

        pugi::xml_node docMap = doc.first_child();

        m_tileWidth  = docMap.attribute("width").as_uint();
        m_tileHeight = docMap.attribute("height").as_uint();

        m_numTiles = m_tileWidth * m_tileHeight;

        m_width  = m_tileWidth  * tb::Constants::TileSize;
        m_height = m_tileHeight * tb::Constants::TileSize;

        m_size = m_width * m_height;

        tb::Variables::MapWidth  = m_width;
        tb::Variables::MapHeight = m_height;

        tb::Variables::MapSize = m_size;

        std::cout << "Map Size: " << m_tileWidth << "x" << m_tileHeight << " (" << m_numTiles << " tiles)" << std::endl;

        auto docMapProperties = docMap.child("properties");
        if (docMapProperties == NULL)
        {
            std::cout << "Error: failed to load map: 'properties' field not found\n";
            return false;
        }

        for (auto& docMapProperty : docMapProperties.children("property"))
        {
            std::string docMapPropertyName = docMapProperty.attribute("name").value();

            std::cout << "Map Property Name: " << docMapPropertyName << "\n";

            if (docMapPropertyName == "Name")
            {
                properties.Name = docMapProperty.attribute("value").value();
            }
            else if (docMapPropertyName == "Description")
            {
                properties.Description = docMapProperty.attribute("value").value();
            }
            else if (docMapPropertyName == "Author")
            {
                properties.Author = docMapProperty.attribute("value").value();
            }

            else if (docMapPropertyName == "PlayerStartX")
            {
                properties.PlayerStartX = docMapProperty.attribute("value").as_uint();
            }
            else if (docMapPropertyName == "PlayerStartY")
            {
                properties.PlayerStartY = docMapProperty.attribute("value").as_uint();
            }
            else if (docMapPropertyName == "PlayerStartZ")
            {
                properties.PlayerStartZ = (tb::ZAxis_t)docMapProperty.attribute("value").as_uint();
            }
            else if (docMapPropertyName == "TimeOfDay")
            {
                properties.TimeOfDay = (tb::TimeOfDay)docMapProperty.attribute("value").as_uint();
            }
        }

        auto docMapGroupFind = docMap.child("group");
        if (docMapGroupFind == NULL)
        {
            std::cout << "Error: failed to load map: 'group' field not found\n";
            return false;
        }

        for (auto& docMapGroup : docMap.children("group"))
        {
            std::string docMapGroupName = docMapGroup.attribute("name").as_string();

            std::cout << "Group Name: " << docMapGroupName << "\n";

            tb::ZAxis_t docMapGroupZAxis = std::stoul(docMapGroupName);

            auto docMapLayerFind = docMap.child("layer");
            if (docMapLayerFind == NULL)
            {
                std::cout << "Error: failed to load map: 'layer' field not found\n";
                return false;
            }

            for (auto& docMapLayer : docMap.children("layer"))
            {
                std::string docMapLayerName = docMapLayer.attribute("name").value();

                std::cout << "Layer Name: " << docMapLayerName << "\n";

                auto docMapLayerData = docMapLayer.child("data");
                if (docMapLayerData == NULL)
                {
                    std::cout << "Error: failed to load map: 'data' field not found for layer '" << docMapLayerName << "'\n";
                    return false;
                }

                bool isTileLayerFormatCorrect = true;

                for (auto& docMapLayerDataAttr : docMapLayerData.attributes())
                {
                    std::string docMapLayerDataAttrName = docMapLayerDataAttr.name();

                    std::string docMapLayerDataAttrValue = docMapLayerDataAttr.value();

                    if (docMapLayerDataAttrName == "encoding")
                    {
                        if (docMapLayerDataAttrName != "base64")
                        {
                            isTileLayerFormatCorrect = false;
                            break;
                        }
                    }

                    if (docMapLayerDataAttrName == "compression")
                    {
                        if (docMapLayerDataAttrName != "zlib")
                        {
                            isTileLayerFormatCorrect = false;
                            break;
                        }
                    }
                }

                if (isTileLayerFormatCorrect == false)
                {
                    std::cout << "Error: failed to load map: Tile Layer Format must be 'Base64 (zlib compressed)' under Map Properties in Tiled Editor\n";
                    return false;
                }

                std::string docMapLayerDataString = docMapLayerData.text().get();

                // skip empty layers, huge performance boost
                if (docMapLayerDataString == "eJztwQEBAAAAgJD+r+4ICgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGoADwAB")
                {
                    std::cout << "Skipping empty layer\n";
                    continue;
                }

                // remove spaces and new lines
                docMapLayerDataString.erase(boost::remove_if(docMapLayerDataString, boost::is_any_of(" \r\n")), docMapLayerDataString.end());

                std::cout << "Decoding Base64 for map layer '" << docMapLayerName << "'\n";

                docMapLayerDataString = boost_base64_decode(docMapLayerDataString);

                std::cout << "Decompressing zlib for map layer '" << docMapLayerName << "'\n";

                docMapLayerDataString = boost_zlib_decompress_string_fast(docMapLayerDataString);

                ////std::cout << docMapLayerDataString << "\n";

                if (docMapLayerDataString.size() == 0)
                {
                    std::cout << "Skipping layer because data string size is zero\n";
                    continue;
                }

                std::istringstream docMapLayerDataStream(docMapLayerDataString);

                std::vector<tb::SpriteID_t> docMapLayerDataTiles;
                docMapLayerDataTiles.reserve(docMapLayerDataString.size() / 4);

                for (std::size_t i = 0; i < docMapLayerDataString.size(); i += 4)
                {
                    uint32_t tileID;
                    docMapLayerDataStream.read(reinterpret_cast<char*>(&tileID), 4);

                    docMapLayerDataTiles.push_back((tb::SpriteID_t)tileID);
                }

                tb::ZAxis_t tileMapZ = docMapGroupZAxis;

                tb::TileMapType tileMapType = tb::TileMapType::Tiles;

                if (docMapLayerName == "Tile Edges")
                {
                    tileMapType = tb::TileMapType::TileEdges;
                }

                if (tileMapType == tb::TileMapType::Tiles)
                {
                    tileMapTiles[tileMapZ].load(m_width, m_height, docMapLayerDataTiles, docMapLayerName, tileMapType, tileMapZ);
                }
                else if (tileMapType == tb::TileMapType::TileEdges)
                {
                    tileMapTileEdges[tileMapZ].load(m_width, m_height, docMapLayerDataTiles, docMapLayerName, tileMapType, tileMapZ);
                }
            }

            auto docMapObjectGroupFind = docMap.child("objectgroup");
            if (docMapObjectGroupFind == NULL)
            {
                std::cout << "Error: failed to load map: 'objectgroup' field not found" << std::endl;
                return false;
            }

            for (auto& docMapObjectGroup : docMap.children("objectgroup"))
            {
                std::string docMapObjectGroupName = docMapObjectGroup.attribute("name").value();

                std::cout << "Object Group: " << docMapObjectGroupName << "\n";

                tb::ZAxis_t docMapObjectZ = docMapGroupZAxis;

                tb::MapObjectLayerType docMapObjectLayerType = tb::MapObjectLayerType::Objects;

                if (docMapObjectGroupName == "Entities")
                {
                    docMapObjectLayerType = tb::MapObjectLayerType::Entities;
                }
                else if (docMapObjectGroupName == "Creatures")
                {
                    docMapObjectLayerType = tb::MapObjectLayerType::Creatures;
                }

                tb::TileMap* tileMap = &tileMapTiles[docMapObjectZ];

                // object layer may be empty but we can still load the map
                //auto docMapObjectFind = docMapObjectGroup.child("object");
                //if (docMapObjectFind == NULL)
                //{
                    //std::cout << "Error: failed to load map: 'object' field not found for objectgroup '" << docMapObjectGroupName << "'\n";
                    //return false;
                //}

                for (auto& docMapObject : docMapObjectGroup.children("object"))
                {
                    tb::SpriteID_t docMapObjectGID;
                    uint32_t docMapObjectX;
                    uint32_t docMapObjectY;

                    std::string docMapObjectType = "Null";

                    for (auto docMapObjectAttr : docMapObject.attributes())
                    {
                        std::string docMapObjectAttrName = docMapObjectAttr.name();

                        if (docMapObjectAttrName == "gid")
                        {
                            docMapObjectGID = (tb::SpriteID_t)docMapObjectAttr.as_uint();
                        }
                        else if (docMapObjectAttrName == "x")
                        {
                            docMapObjectX = docMapObjectAttr.as_uint();
                        }
                        else if (docMapObjectAttrName == "y")
                        {
                            // Y-Axis in Tiled Editor for objects uses bottom-right coordinate instead of the top-left
                            // Subtracting by tile size fixes this problem
                            docMapObjectY = docMapObjectAttr.as_uint() - tb::Constants::TileSize;
                        }
                        else if (docMapObjectAttrName == "type")
                        {
                            docMapObjectType = docMapObjectAttr.value();
                        }
                    }

                    uint32_t tileNumber = getTileNumberByCoords(sf::Vector2u(docMapObjectX, docMapObjectY));

                    sf::Vector2u tileCoords = getTileCoordsByCoords(sf::Vector2u(docMapObjectX, docMapObjectY));

                    if (docMapObjectLayerType == tb::MapObjectLayerType::Objects)
                    {
                        tb::Object::Ptr object = std::make_shared<tb::Object>(tileCoords, docMapObjectZ, docMapObjectGID);

                        tb::ObjectType objectType = tb::KeyValues::ObjectType[docMapObjectType];

                        object->setType(objectType);

                        tb::Tile::List* tileList = tileMap->getTileList();

                        tb::Tile::Ptr tile = tileList->at(tileNumber);

                        tile->addObject(object);

/*
                        unsigned int objectCount = 0;
                        if (objectCount > 0)
                        {
                            for (unsigned int i = 1; i < objectCount; i++)
                            {
                                tb::Object::Ptr copyObject = std::make_shared<tb::Object>(*object);

                                tile->addObject(copyObject);
                            }
                        }
*/
                    }
                }
            }
        }

        for (unsigned int i = tb::ZAxis::Min; i < tb::ZAxis::Max; i++)
        {
            tileMapTiles[i].applyTileObjectPatterns();
        }

        return true;
    }

    template <class T>
    uint32_t getTileNumberByCoords(T coords)
    {
        uint32_t x = coords.x / tb::Constants::TileSize;
        uint32_t y = coords.y / tb::Constants::TileSize;

        return x + (y * m_width);
    }

    template <class T>
    sf::Vector2u getTileCoordsByCoords(T coords)
    {
        uint32_t x = coords.x / tb::Constants::TileSize;
        uint32_t y = coords.y / tb::Constants::TileSize;

        return {x, y};
    }

    bool isTileNumberOutOfBounds(uint32_t tileNumber)
    {
        if (tileNumber < 0 || tileNumber > m_numTiles - 1)
        {
            return true;
        }

        return false;
    }

    bool isTileCoordsOutOfBounds(const sf::Vector2u& tileCoords)
    {
        if
        (
            tileCoords.x < 0                                         ||
            tileCoords.y < 0                                         ||
            tileCoords.x > m_tileWidth  - tb::Constants::TileSize ||
            tileCoords.y > m_tileHeight - tb::Constants::TileSize
        )
        {
            return true;
        }

        return false;
    }

    const std::string& getFileName() const
    {
        return m_fileName;
    }

    uint32_t getWidth()
    {
        return m_width;
    }

    uint32_t getHeight()
    {
        return m_height;
    }

    uint32_t getSize()
    {
        return m_size;
    }

    uint32_t getTileWidth()
    {
        return m_tileWidth;
    }

    uint32_t getTileHeight()
    {
        return m_tileHeight;
    }

    uint32_t getNumTiles()
    {
        return m_numTiles;
    }

private:

    std::string m_fileName = std::string();

    uint32_t m_width = 0;
    uint32_t m_height = 0;

    uint32_t m_size = 0; // = m_width * m_height

    uint32_t m_tileWidth = 0;
    uint32_t m_tileHeight = 0;

    uint32_t m_numTiles = 0;

};

}
