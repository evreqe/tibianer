#include "tb/MapGenerator.h"

namespace tb
{

MapGenerator::MapGenerator()
{
    //
}

MapGenerator::~MapGenerator()
{
    //
}

std::string MapGenerator::getTemplateFileText()
{
    const std::string& templateFileName = g_MapGeneratorData.getData()->TemplateFileName;

    std::ifstream templateFile = std::ifstream(templateFileName, std::ios::in);

    if (!templateFile)
    {
        g_Log.write("ERROR: templateFile is null\n");
        return {};
    }

    const auto templateFileSize = std::filesystem::file_size(templateFileName);

    g_Log.write("templateFileSize: {}\n", templateFileSize);

    if (templateFileSize == 0)
    {
        g_Log.write("ERROR: templateFileSize is zero\n");
        return {};
    }

    std::string templateFileText(templateFileSize, '\0');

    templateFile.read(templateFileText.data(), templateFileSize);

    if (templateFileText.empty() == true)
    {
        g_Log.write("ERROR: templateFileText is empty\n");
        return {};
    }

    g_Log.write("templateFileText: {}\n", templateFileText);

    templateFile.close();

    return templateFileText;
}

bool MapGenerator::generateMapFromImageFile(const MapGenerator::Map_t& map, const std::string& imageFileName, const std::string& outputFileName)
{
    if (outputFileName.empty() == true)
    {
        g_Log.write("ERROR: outputFileName is empty\n");
        return false;
    }

    if (outputFileName.contains(".tmx") == false)
    {
        g_Log.write("ERROR: outputFileName must have *.tmx file extension\n");
        return false;
    }

    const std::string& mapImageFileName = std::format("map_generator/images/{}", imageFileName);

    if (mapImageFileName.contains(".png") == false)
    {
        g_Log.write("ERROR: mapImageFileName must have *.png file extension\n");
        return false;
    }

    if (mapImageFileName.empty() == true)
    {
        g_Log.write("ERROR: mapImageFileName is empty\n");
        return false;
    }

    const std::string& mapName = map.Name;
    if (mapName.empty() == true)
    {
        g_Log.write("ERROR: mapName is empty\n");
        return false;
    }

    const std::string& mapAuthor = map.Author;
    if (mapAuthor.empty() == true)
    {
        g_Log.write("ERROR: mapAuthor is empty\n");
        return false;
    }

    const std::string& mapDescription = map.Description;
    if (mapDescription.empty() == true)
    {
        g_Log.write("ERROR: mapDescription is empty\n");
        return false;
    }

    const std::uint32_t& mapPlayerStartX = map.PlayerStartX;
    const std::uint32_t& mapPlayerStartY = map.PlayerStartY;
    const std::uint32_t& mapPlayerStartZ = map.PlayerStartZ;

    std::string mapPlayerStartXAsString = std::to_string(mapPlayerStartX);
    std::string mapPlayerStartYAsString = std::to_string(mapPlayerStartY);
    std::string mapPlayerStartZAsString = std::to_string(mapPlayerStartZ);

    std::string templateFileText = getTemplateFileText();
    if (templateFileText.empty() == true)
    {
        g_Log.write("ERROR: templateFileText is empty\n");
        return false;
    }

    sf::Image image;
    if (image.loadFromFile(mapImageFileName) == false)
    {
        g_Log.write("ERROR: Cannot open file: {}\n", mapImageFileName);
        return false;
    }

    tb::MapGeneratorPixelData::DataList* mapGeneratorPixelDataList = g_MapGeneratorPixelData.getDataList();
    if (mapGeneratorPixelDataList == nullptr)
    {
        g_Log.write("ERROR: mapGeneratorPixelDataList is nullptr\n");
        return false;
    }

    unsigned int imageWidth = image.getSize().x;
    unsigned int imageHeight = image.getSize().y;

    std::string imageWidthAsString = std::to_string(imageWidth);
    std::string imageHeightAsString = std::to_string(imageHeight);

    if (mapPlayerStartX > imageWidth)
    {
        g_Log.write("ERROR: mapPlayerStartX is greather than imageWidth\n");
        return false;
    }

    if (mapPlayerStartY > imageHeight)
    {
        g_Log.write("ERROR: mapPlayerStartY is greater than imageHeight\n");
        return false;
    }

    if (mapPlayerStartZ < tb::ZAxis::Min || mapPlayerStartZ > tb::ZAxis::Max)
    {
        g_Log.write("ERROR: mapPlayerStartZ is out of bounds\n");
        return false;
    }

    std::vector<std::uint32_t> tileList;

    std::vector<std::string> objectList;

    unsigned int objectIndex = 1;

    for (unsigned int y = 0; y < imageHeight; y++)
    {
        for (unsigned int x = 0; x < imageWidth; x++)
        {
            sf::Color imagePixelColor = image.getPixel(sf::Vector2u(x, y));

            bool wasPixelFound = false;

            for (auto& mapGeneratorPixelData : *mapGeneratorPixelDataList)
            {
                if (mapGeneratorPixelData.ColorR == imagePixelColor.r && mapGeneratorPixelData.ColorG == imagePixelColor.g && mapGeneratorPixelData.ColorB == imagePixelColor.b)
                {
                    std::uint32_t spriteIDListMax = static_cast<std::uint32_t>(mapGeneratorPixelData.SpriteIDList.size() - 1);

                    std::uint32_t randomSpriteID = tb::Utility::getRandomNumber(0, spriteIDListMax);

                    std::uint32_t spriteID = mapGeneratorPixelData.SpriteIDList.at(randomSpriteID);

                    if (mapGeneratorPixelData.Type == "Tile")
                    {
                        tileList.push_back(spriteID);
                    }
                    else if (mapGeneratorPixelData.Type == "Object")
                    {
                        tileList.push_back(tb::Sprites::Grass);

                        std::uint32_t objectX = x * tb::Constants::TileSize;
                        std::uint32_t objectY = y * tb::Constants::TileSize;

                        std::string objectAsString = std::format("<object id=\"{}\" gid=\"{}\" x=\"{}\" y=\"{}\" width=\"32\" height=\"32\"/>", objectIndex, spriteID, objectX, objectY);

                        objectList.push_back(objectAsString);

                        objectIndex++;
                    }

                    wasPixelFound = true;

                    break;
                }
            }

            if (wasPixelFound == false)
            {
                tileList.push_back(0);
            }
        }
    }

    tb::MapGeneratorPixelData::Data* mapGeneratorPixelDataForGrass = g_MapGeneratorPixelData.getDataByName("Grass");
    if (mapGeneratorPixelDataForGrass == nullptr)
    {
        g_Log.write("ERROR: mapGeneratorPixelDataForGrass is nullptr\n");
        return false;
    }

    tb::SpriteIDList* cornersList = &mapGeneratorPixelDataForGrass->CornersSpriteIDList;
    if (cornersList->size() != m_numCornerSpritesRequired)
    {
        g_Log.write("ERROR: cornersList has wrong size\n");
        return false;
    }

    tb::SpriteIDList* edgesList = &mapGeneratorPixelDataForGrass->EdgesSpriteIDList;
    if (edgesList->size() != m_numEdgeSpritesRequired)
    {
        g_Log.write("ERROR: edgesList has wrong size\n");
        return false;
    }

    std::vector<std::string> tileEdgeObjectList;

    for (std::size_t tileIndex = 0; tileIndex < tileList.size(); tileIndex++)
    {
        std::uint32_t spriteID = tileList.at(tileIndex);
        if (spriteID != tb::Sprites::Grass)
        {
            continue;
        }

        sf::Vector2i tileCoords;
        tileCoords.x = static_cast<int>(tileIndex % imageWidth);
        tileCoords.y = static_cast<int>(tileIndex / imageHeight);

        //tileIndex = tileCoords.x + (tileCoords.y * imageWidth);

        sf::Vector2i tileCoordsTopLeft;
        tileCoordsTopLeft.x = tileCoords.x - 1;
        tileCoordsTopLeft.y = tileCoords.y - 1;

        sf::Vector2i tileCoordsTopCenter;
        tileCoordsTopCenter.x = tileCoords.x;
        tileCoordsTopCenter.y = tileCoords.y - 1;

        sf::Vector2i tileCoordsTopRight;
        tileCoordsTopRight.x = tileCoords.x + 1;
        tileCoordsTopRight.y = tileCoords.y - 1;

        sf::Vector2i tileCoordsLeft;
        tileCoordsLeft.x = tileCoords.x - 1;
        tileCoordsLeft.y = tileCoords.y;

        sf::Vector2i tileCoordsRight;
        tileCoordsRight.x = tileCoords.x + 1;
        tileCoordsRight.y = tileCoords.y;

        sf::Vector2i tileCoordsBottomLeft;
        tileCoordsBottomLeft.x = tileCoords.x - 1;
        tileCoordsBottomLeft.y = tileCoords.y + 1;

        sf::Vector2i tileCoordsBottomCenter;
        tileCoordsBottomCenter.x = tileCoords.x;
        tileCoordsBottomCenter.y = tileCoords.y + 1;

        sf::Vector2i tileCoordsBottomRight;
        tileCoordsBottomRight.x = tileCoords.x + 1;
        tileCoordsBottomRight.y = tileCoords.y + 1;

        std::uint32_t tileIndexTopLeft       = tileCoordsTopLeft.x       + (tileCoordsTopLeft.y       * imageWidth);
        std::uint32_t tileIndexTopCenter     = tileCoordsTopCenter.x     + (tileCoordsTopCenter.y     * imageWidth);
        std::uint32_t tileIndexTopRight      = tileCoordsTopRight.x      + (tileCoordsTopRight.y      * imageWidth);
        std::uint32_t tileIndexLeft          = tileCoordsLeft.x          + (tileCoordsLeft.y          * imageWidth);
        std::uint32_t tileIndexRight         = tileCoordsRight.x         + (tileCoordsRight.y         * imageWidth);
        std::uint32_t tileIndexBottomLeft    = tileCoordsBottomLeft.x    + (tileCoordsBottomLeft.y    * imageWidth);
        std::uint32_t tileIndexBottomCenter  = tileCoordsBottomCenter.x  + (tileCoordsBottomCenter.y  * imageWidth);
        std::uint32_t tileIndexBottomRight   = tileCoordsBottomRight.x   + (tileCoordsBottomRight.y   * imageWidth);

        std::uint32_t spriteIDTopLeft      = tileList.at(tileIndexTopLeft);
        std::uint32_t spriteIDTopCenter    = tileList.at(tileIndexTopCenter);
        std::uint32_t spriteIDTopRight     = tileList.at(tileIndexTopRight);
        std::uint32_t spriteIDLeft         = tileList.at(tileIndexLeft);
        std::uint32_t spriteIDRight        = tileList.at(tileIndexRight);
        std::uint32_t spriteIDBottomLeft   = tileList.at(tileIndexBottomLeft);
        std::uint32_t spriteIDBottomCenter = tileList.at(tileIndexBottomCenter);
        std::uint32_t spriteIDBottomRight  = tileList.at(tileIndexBottomRight);

        uint32_t objectSpriteID = 0;

        sf::Vector2i* objectTileCoords = nullptr;

        const std::string objectFormatString = "<object id=\"{}\" gid=\"{}\" x=\"{}\" y=\"{}\" width=\"32\" height=\"32\"/>";

        // edge top left
        if (spriteIDTopLeft == tb::Sprites::Water && spriteIDTopCenter == tb::Sprites::Water && spriteIDLeft == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(0);

            objectTileCoords = &tileCoordsTopLeft;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge top center
        if (spriteIDTopCenter == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(1);

            objectTileCoords = &tileCoordsTopCenter;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge top right
        if (spriteIDTopRight == tb::Sprites::Water && spriteIDTopCenter == tb::Sprites::Water && spriteIDRight == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(2);

            objectTileCoords = &tileCoordsTopRight;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge left
        if (spriteIDLeft == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(3);

            objectTileCoords = &tileCoordsLeft;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge right
        if (spriteIDRight == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(5);

            objectTileCoords = &tileCoordsRight;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge bottom left
        if (spriteIDBottomLeft == tb::Sprites::Water && spriteIDBottomCenter == tb::Sprites::Water && spriteIDLeft == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(6);

            objectTileCoords = &tileCoordsBottomLeft;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge bottom center
        if (spriteIDBottomCenter == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(7);

            objectTileCoords = &tileCoordsBottomCenter;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // edge bottom right
        if (spriteIDBottomRight == tb::Sprites::Water && spriteIDBottomCenter == tb::Sprites::Water && spriteIDRight == tb::Sprites::Water)
        {
            objectSpriteID = edgesList->at(8);

            objectTileCoords = &tileCoordsBottomRight;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // corner bottom right
        if (spriteIDBottomCenter == tb::Sprites::Grass && spriteIDRight == tb::Sprites::Grass && spriteIDBottomRight == tb::Sprites::Water)
        {
            objectSpriteID = cornersList->at(0);

            objectTileCoords = &tileCoordsBottomRight;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // corner bottom left
        if (spriteIDBottomCenter == tb::Sprites::Grass && spriteIDLeft == tb::Sprites::Grass && spriteIDBottomLeft == tb::Sprites::Water)
        {
            objectSpriteID = cornersList->at(1);

            objectTileCoords = &tileCoordsBottomLeft;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // corner top right
        if (spriteIDTopCenter == tb::Sprites::Grass && spriteIDRight == tb::Sprites::Grass && spriteIDTopRight == tb::Sprites::Water)
        {
            objectSpriteID = cornersList->at(2);

            objectTileCoords = &tileCoordsTopRight;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }

        // corner top left
        if (spriteIDTopCenter == tb::Sprites::Grass && spriteIDLeft == tb::Sprites::Grass && spriteIDTopLeft == tb::Sprites::Water)
        {
            objectSpriteID = cornersList->at(3);

            objectTileCoords = &tileCoordsTopLeft;

            std::uint32_t objectX = objectTileCoords->x * tb::Constants::TileSize;
            std::uint32_t objectY = objectTileCoords->y * tb::Constants::TileSize;

            std::string objectAsString = dynamicFormat(objectFormatString, objectIndex, objectSpriteID, objectX, objectY);

            tileEdgeObjectList.push_back(objectAsString);
        }
    }

    std::string tileListAsString;
    tileListAsString.reserve(imageWidth * imageHeight);

    std::size_t tileListSize = tileList.size();

    for (std::size_t i = 0; i < tileListSize; i++)
    {
        tileListAsString.append(std::to_string(tileList.at(i)));

        if (i < tileListSize - 1)
        {
            tileListAsString.append(",");
        }

        if (i != 0 && i % imageWidth == 0)
        {
            tileListAsString.append("\n");
        }
    }

    if (tileListAsString.empty() == true)
    {
        g_Log.write("ERROR: tileListAsString is empty\n");
        return false;
    }

    g_Log.write("tileListAsString: {}\n", tileListAsString);

    std::string objectListAsString;

    std::size_t objectListSizeOfContents = 0;
    for (auto& object : objectList)
    {
        objectListSizeOfContents = objectListSizeOfContents + (object.size() + 1);
    }

    objectListAsString.reserve(objectListSizeOfContents);

    for (auto& object : objectList)
    {
        objectListAsString.append(object);
        objectListAsString.append("\n");
    }

    objectListAsString = objectListAsString.substr(0, objectListAsString.size() - 1);

    if (objectListAsString.empty() == true)
    {
        g_Log.write("ERROR: objectListAsString is empty\n");
        return false;
    }

    g_Log.write("objectListAsString: {}\n", objectListAsString);

    std::string tileEdgeObjectListAsString;

    std::size_t tileEdgeObjectListSizeOfContents = 0;
    for (auto& tileEdgeObject : tileEdgeObjectList)
    {
        tileEdgeObjectListSizeOfContents = tileEdgeObjectListSizeOfContents + (tileEdgeObject.size() + 1);
    }

    tileEdgeObjectListAsString.reserve(tileEdgeObjectListSizeOfContents);

    for (auto& tileEdgeObject : tileEdgeObjectList)
    {
        tileEdgeObjectListAsString.append(tileEdgeObject);
        tileEdgeObjectListAsString.append("\n");
    }

    tileEdgeObjectListAsString = tileEdgeObjectListAsString.substr(0, tileEdgeObjectListAsString.size() - 1);

    if (tileEdgeObjectListAsString.empty() == true)
    {
        g_Log.write("ERROR: tileEdgeObjectListAsString is empty\n");
        return false;
    }

    g_Log.write("tileEdgeObjectListAsString: {}\n", tileEdgeObjectListAsString);

    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_WIDTH;", imageWidthAsString);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_HEIGHT;", imageHeightAsString);

    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_AUTHOR;", mapAuthor);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_DESCRIPTION;", mapDescription);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_NAME;", mapName);

    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_PLAYER_START_X;", mapPlayerStartXAsString);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_PLAYER_START_Y;", mapPlayerStartYAsString);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_PLAYER_START_Z;", mapPlayerStartZAsString);

    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_TILES;", tileListAsString);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_OBJECTS;", objectListAsString);
    templateFileText = tb::Utility::String::replaceAll(templateFileText, "$MAP_TILE_EDGE_OBJECTS;", tileEdgeObjectListAsString);

    std::string mapOutputFileName = std::format("map_generator/output/{}", outputFileName);

    std::fstream outputFile;
    outputFile.open(mapOutputFileName, std::ios::out | std::ios::trunc);
    outputFile << templateFileText;
    outputFile.close();

    return true;
}

}
