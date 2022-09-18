#include "tb/TileMap.h"

namespace tb
{

TileMap::TileMap()
{
    //
}

TileMap::~TileMap()
{
    //
}

bool TileMap::load(uint32_t tileWidth, uint32_t tileHeight, tb::SpriteIDList tileSpriteIDList, const std::string& name, tb::TileMapType tileMapType, tb::ZAxis_t z)
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("g_SpriteData.isLoaded() == false\n");
        return false;
    }

    if (tileWidth == 0 || tileHeight == 0)
    {
        g_Log.write("tileWidth == 0 || tileHeight == 0\n");
        return false;
    }

    m_tileList.clear();
    m_waterTileList.clear();

    m_tileSpriteIDList.clear();
    m_tileSpriteIDList.swap(tileSpriteIDList);

    if (m_tileSpriteIDList.size() == 0)
    {
        g_Log.write("m_tileSpriteIDList.size() == 0\n");
        return false;
    }

    g_Log.write("name: {}\n",  name);
    g_Log.write("m_tileSpriteIDList.size(): {}\n", m_tileSpriteIDList.size());

    m_name = name;

    m_tileMapType = tileMapType;

    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;

    m_numTiles = m_tileWidth * m_tileHeight;

    m_z = z;

    m_waterAnimationFrame = 1; // start the animation at index 1 because the applied water pattern starts at index 0

    for (uint32_t i = 0; i < m_tileWidth; ++i)
    {
        for (uint32_t j = 0; j < m_tileHeight; ++j)
        {
            uint32_t tileNumber = i + j * m_tileWidth;

            if (tileNumber > m_tileSpriteIDList.size())
            {
                g_Log.write("tileNumber is out of bounds: {}\n", tileNumber);
                continue;
            }

            sf::Vector2u tilePixelCoords
            (
                i * tb::Constants::TileSize,
                j * tb::Constants::TileSize
            );

            tb::SpriteID_t tileSpriteID = m_tileSpriteIDList.at(tileNumber);

            tb::SpriteFlags_t* tileSpriteFlags = &g_SpriteData.getDataList()->at(tileSpriteID).SpriteFlags;

            //if (tileId == tb::TILE_NULL && m_type == tb::TileMapTypes::tiles)
            //{
                //tileFlags.set(tb::SpriteFlags::null);
            //}

            tb::Tile::Ptr tile = std::make_shared<tb::Tile>();
            tile->setTileNumber(tileNumber);
            tile->setSpriteID(tileSpriteID);
            tile->setSpriteFlags(*tileSpriteFlags);
            tile->setPixelCoords(tilePixelCoords);
            tile->setZ(z);
            m_tileList.push_back(tile);

            if (z == tb::ZAxis::Ground)
            {
                if ((*tileSpriteFlags).test(tb::SpriteFlags::Water))
                {
                    m_waterTileList.push_back(tile);
                }
            }
        }
    }

    std::sort(m_tileList.begin(), m_tileList.end(), tb::Tile::sortByTileNumber_t());

    g_Log.write("Applying tile patterns to tile map...\n");
    if (applyTilePatterns() == false)
    {
        g_Log.write("ERROR: Failed to apply tile patterns to tile map\n");
        return false;
    }

    return true;
}

void TileMap::updateTileSpriteID(tb::Tile::Ptr tile, tb::SpriteID_t spriteID)
{
    tile->setSpriteID(spriteID);
}

void TileMap::updateTileSpriteFlags(tb::Tile::Ptr tile, tb::SpriteID_t spriteID)
{
    tb::SpriteFlags_t* tileSpriteFlags = &g_SpriteData.getDataList()->at(spriteID).SpriteFlags;

    if (tileSpriteFlags != nullptr)
    {
        tile->setSpriteFlags(*tileSpriteFlags);
    }
}

tb::SpriteIDList* TileMap::getTileSpriteIDList()
{
    return &m_tileSpriteIDList;
}

tb::Tile::List* TileMap::getTileList()
{
    return &m_tileList;
}

tb::Tile::List* TileMap::getWaterTileList()
{
    return &m_waterTileList;
}

void TileMap::loadWaterTiles()
{
    m_waterTileList.clear();

    for (auto& tile : m_tileList)
    {
        if (tile->getSpriteFlags().test(tb::SpriteFlags::Water))
        {
            m_waterTileList.push_back(tile);
        }
    }
}

bool TileMap::doAnimatedWater()
{
    auto waterSpriteIDList_List = g_WaterData.getSpriteIDList_List();
    if (waterSpriteIDList_List == nullptr)
    {
        g_Log.write("ERROR: waterSpriteIDList_List == nullptr\n");
        return false;
    }

    if (m_waterAnimationFrame >= tb::Constants::NumWaterAnimationFrames)
    {
        m_waterAnimationFrame = 0;
    }

   tb::SpriteIDList* waterSpriteIDList = &waterSpriteIDList_List->at(m_waterAnimationFrame);
    if (waterSpriteIDList == nullptr)
    {
        g_Log.write("ERROR: waterSpriteIDList == nullptr\n");
        return false;
    }

    for (auto& tile : m_waterTileList)
    {
        uint32_t tileColumnIndex = m_tileWidth - tile->getTileX();

        tileColumnIndex = m_tileWidth - tileColumnIndex;

        uint32_t tileRowIndex = m_tileHeight - tile->getTileY();

        tileRowIndex = m_tileHeight - tileRowIndex;

        uint32_t spriteIndex = tileColumnIndex;

        while (spriteIndex > (tb::Constants::WaterPatternWidth - 1))
        {
            spriteIndex = spriteIndex - tb::Constants::WaterPatternWidth;
        }

        while (tileRowIndex > (tb::Constants::WaterPatternHeight - 1))
        {
            tileRowIndex = tileRowIndex - tb::Constants::WaterPatternHeight;
        }

        if (tileRowIndex > 0)
        {
            spriteIndex += tb::Constants::WaterPatternWidth * tileRowIndex;
        }

        if (spriteIndex < waterSpriteIDList->size())
        {
            updateTileSpriteID(tile, waterSpriteIDList->at(spriteIndex));
        }
    }

    m_waterAnimationFrame++;

    return true;
}

bool TileMap::applyTilePatterns()
{
    auto patternList = g_PatternData.getPatternList();
    if (patternList == nullptr)
    {
        g_Log.write("ERROR: patternList == nullptr\n");
        return false;
    }

    for (auto& pattern : *patternList)
    {
        if (pattern.PatternType != PatternType::Tile)
        {
            continue;
        }

        bool isWater= false;

        tb::Tile::List* tileList = &m_tileList;

        if (pattern.Name == "water")
        {
            tileList = &m_waterTileList;

            isWater = true;
        }

        for (auto& tile : *tileList)
        {
            if (isWater == false)
            {
                tb::SpriteID_t tileSpriteID = tile->getSpriteID();

                if (std::find(pattern.Sprites.begin(), pattern.Sprites.end(), tileSpriteID) == pattern.Sprites.end())
                {
                    continue;
                }
            }

            uint32_t tileColumnIndex = m_tileWidth - tile->getTileX();

            tileColumnIndex = m_tileWidth - tileColumnIndex;

            uint32_t tileRowIndex = m_tileHeight - tile->getTileY();

            tileRowIndex = m_tileHeight - tileRowIndex;

            uint32_t spriteIndex = tileColumnIndex;

            while (spriteIndex > (pattern.Width - 1))
            {
                spriteIndex = spriteIndex - pattern.Width;
            }

            while (tileRowIndex > (pattern.Height - 1))
            {
                tileRowIndex = tileRowIndex - pattern.Height;
            }

            if (tileRowIndex > 0)
            {
                spriteIndex += pattern.Width * tileRowIndex;
            }

            if (spriteIndex < pattern.Sprites.size())
            {
                updateTileSpriteID(tile, pattern.Sprites.at(spriteIndex));
            }
        }
    }

    return true;
}

bool TileMap::applyTileObjectPatterns()
{
    auto patternList = g_PatternData.getPatternList();
    if (patternList == nullptr)
    {
        g_Log.write("ERROR: patternList == nullptr\n");
        return false;
    }

    for (auto& pattern : *patternList)
    {
        if (pattern.PatternType != PatternType::Object)
        {
            continue;
        }

        for (auto& tile : m_tileList)
        {
            auto tileObjectList = tile->getObjectList();
            if (tileObjectList == nullptr)
            {
                continue;
            }

            for (auto& object : *tileObjectList)
            {
                auto objectSpriteID = object->getSpriteID();

                if (std::find(pattern.Sprites.begin(), pattern.Sprites.end(), objectSpriteID) != pattern.Sprites.end())
                {
                    if (pattern.Width > pattern.Height) // horizontal
                    {
                        uint32_t objectTileX = object->getTileX();

                        if (m_z & 1)
                        {
                            if (objectTileX & 1)
                            {
                                object->setSpriteID(pattern.Sprites.front());
                            }
                            else
                            {
                                object->setSpriteID(pattern.Sprites.back());
                            }
                        }
                        else
                        {
                            if (objectTileX & 1)
                            {
                                object->setSpriteID(pattern.Sprites.back());
                            }
                            else
                            {
                                object->setSpriteID(pattern.Sprites.front());
                            }
                        }
                    }
                    else if (pattern.Height > pattern.Width) // vertical
                    {
                        uint32_t objectTileY = object->getTileY();

                        if (m_z & 1)
                        {
                            if (objectTileY & 1)
                            {
                                object->setSpriteID(pattern.Sprites.front());
                            }
                            else
                            {
                                object->setSpriteID(pattern.Sprites.back());
                            }
                        }
                        else
                        {
                            if (objectTileY & 1)
                            {
                                object->setSpriteID(pattern.Sprites.back());
                            }
                            else
                            {
                                object->setSpriteID(pattern.Sprites.front());
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

sf::Vector2u TileMap::getTileCoordsByTileNumber(uint32_t tileNumber)
{
    unsigned int x = (tileNumber % m_tileWidth) * tb::Constants::TileSize;
    unsigned int y = (tileNumber / m_tileHeight);

    return sf::Vector2u(x, y);
}

const std::string& TileMap::getName()
{
    return m_name;
}

void TileMap::setName(const std::string& name)
{
    m_name = name;
}

tb::TileMapType TileMap::getTileMapType()
{
    return m_tileMapType;
}

void TileMap::setTileMapType(tb::TileMapType tileMapType)
{
    m_tileMapType = tileMapType;
}

tb::ZAxis_t TileMap::getZ()
{
    return m_z;
}

void TileMap::setZ(tb::ZAxis_t z)
{
    m_z = z;
}

void TileMap::draw(sf::RenderTarget& renderTarget)
{
    if (m_tileList.size() == 0)
    {
        return;
    }

    sf::RenderStates renderStates;
    renderStates.texture = &tb::Textures::Sprites;

    m_vertexList.clear();
    m_vertexList.reserve(m_numTiles * 4);

    int x1 = 0;
    int y1 = 0;

    int x2 = 416 / 32;    // 13x9 tiles
    int y2 = 288 / 32;

    for (int i = x1; i < x1 + x2; i++)
    {
        for (int j = y1; j < y1 + y2; j++)
        {
            if (i < 0) continue;
            if (j < 0) continue;

            if (i > m_tileWidth - 1) continue;
            if (j > m_tileHeight - 1) continue;

            uint32_t tileNumber = i + (j * m_tileWidth);

            // tile number is out of bounds
            if (tileNumber > (m_numTiles - 1))
            {
                continue;
            }

            tb::Tile::Ptr tile = m_tileList.at(tileNumber);

            if (tile == nullptr)
            {
                continue;
            }

            tb::SpriteID_t tileSpriteID = tile->getSpriteID();

            if (tileSpriteID == tb::Constants::TileNull)
            {
                continue;
            }

            int tu = (tileSpriteID - 1) % (tb::Textures::Sprites.getSize().x / tb::Constants::TileSize);
            int tv = (tileSpriteID - 1) / (tb::Textures::Sprites.getSize().y / tb::Constants::TileSize);

            sf::Vertex quad[4];

            quad[0].position = sf::Vector2f(i       * tb::Constants::TileSize, j       * tb::Constants::TileSize);
            quad[1].position = sf::Vector2f((i + 1) * tb::Constants::TileSize, j       * tb::Constants::TileSize);
            quad[2].position = sf::Vector2f((i + 1) * tb::Constants::TileSize, (j + 1) * tb::Constants::TileSize);
            quad[3].position = sf::Vector2f(i       * tb::Constants::TileSize, (j + 1) * tb::Constants::TileSize);

            quad[0].texCoords = sf::Vector2f(tu       * tb::Constants::TileSize, tv       * tb::Constants::TileSize);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tb::Constants::TileSize, tv       * tb::Constants::TileSize);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tb::Constants::TileSize, (tv + 1) * tb::Constants::TileSize);
            quad[3].texCoords = sf::Vector2f(tu       * tb::Constants::TileSize, (tv + 1) * tb::Constants::TileSize);

            tb::SpriteFlags_t tileFlags = tile->getSpriteFlags();

            if (tileFlags.test(tb::SpriteFlags::NoDraw))
            {
                quad[0].color = sf::Color::Transparent;
                quad[1].color = sf::Color::Transparent;
                quad[2].color = sf::Color::Transparent;
                quad[3].color = sf::Color::Transparent;
            }

            m_vertexList.push_back(quad[0]);
            m_vertexList.push_back(quad[1]);
            m_vertexList.push_back(quad[2]);
            m_vertexList.push_back(quad[3]);
        }
    }

    //g_Log.write("m_vertexList.size(): {}\n", m_vertexList.size());

    if (m_vertexList.size() != 0)
    {
        renderTarget.draw(&m_vertexList[0], m_vertexList.size(), sf::Quads, renderStates);
    }

    //x1 = 0;
    //y1 = 0;

    //x2 = 4096;
    //y2 = 4096;

    tb::SpriteBatch spriteBatch;

    for (uint32_t tileNumber = 0; tileNumber < m_numTiles; tileNumber++)
    {
        // tile number is out of bounds
        if (tileNumber > (m_numTiles - 1))
        {
            continue;
        }

        tb::Tile::Ptr tile = m_tileList.at(tileNumber);

        if (tile == nullptr)
        {
            continue;
        }

        tb::Object::List* tileObjectList = tile->getObjectList();

        if (tileObjectList == nullptr)
        {
            continue;
        }

        if (tileObjectList->size() == 0)
        {
            continue;
        }

        tb::Thing::List tileThingList;

        std::copy(tileObjectList->begin(), tileObjectList->end(), std::back_inserter(tileThingList));

        std::stable_sort(tileThingList.begin(), tileThingList.end(), tb::Thing::SortByTileCoords_t());

        for (auto& thing : tileThingList)
        {
            if (thing->getThingType() == tb::ThingType::Object)
            {
                tb::Object::Ptr object = std::static_pointer_cast<tb::Object>(thing);

                object->update();

                tb::Sprite sprite = *object->getSprite();

                spriteBatch.addSprite(sprite, true);
            }
        }

/*
        for (auto& object : *tileObjectList)
        {
            auto sprite = *object->getSprite();

            object->update();

            //target.draw(sprite);

            spriteBatch.addSprite(sprite, true);
        }
*/
    }

    if (spriteBatch.getNumSprites() != 0)
    {
        spriteBatch.draw(renderTarget, renderStates);
    }
}

}
