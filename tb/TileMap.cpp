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
            uint32_t tileIndex = i + j * m_tileWidth;

            if (tileIndex > m_tileSpriteIDList.size())
            {
                g_Log.write("tileIndex is out of bounds: {}\n", tileIndex);
                continue;
            }

            sf::Vector2u tilePixelCoords
            (
                i * tb::Constants::TileSize,
                j * tb::Constants::TileSize
            );

            tb::SpriteID_t tileSpriteID = m_tileSpriteIDList.at(tileIndex);

            tb::SpriteFlags_t* tileSpriteFlags = &g_SpriteData.getDataList()->at(tileSpriteID).SpriteFlags;

            //if (tileId == tb::TILE_NULL && m_type == tb::TileMapTypes::tiles)
            //{
                //tileFlags.set(tb::SpriteFlags::null);
            //}

            tb::Tile::Ptr tile = std::make_shared<tb::Tile>();
            tile->setTileIndex(tileIndex);
            tile->setSpriteID(tileSpriteID);
            tile->setSpriteFlags(*tileSpriteFlags);
            tile->setPixelCoords(tilePixelCoords);
            tile->setZ(z);
            m_tileList.push_back(tile);

            if (z == tb::ZAxis::Default)
            {
                if ((*tileSpriteFlags).test(tb::SpriteFlags::Water))
                {
                    m_waterTileList.push_back(tile);
                }
            }
        }
    }

    std::sort(m_tileList.begin(), m_tileList.end(), tb::Tile::sortByTileIndex_t());

    g_Log.write("Applying tile patterns to tile map...\n");
    if (applyTilePatterns() == false)
    {
        g_Log.write("ERROR: Failed to apply tile patterns to tile map\n");
        return false;
    }

    return true;
}

bool TileMap::isTileIndexOutOfBounds(uint32_t tileIndex)
{
    if (tileIndex > (m_numTiles - 1))
    {
        return true;
    }

    return false;
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

                if (std::find(pattern.SpriteIDList.begin(), pattern.SpriteIDList.end(), tileSpriteID) == pattern.SpriteIDList.end())
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

            if (spriteIndex < pattern.SpriteIDList.size())
            {
                updateTileSpriteID(tile, pattern.SpriteIDList.at(spriteIndex));
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

                if (std::find(pattern.SpriteIDList.begin(), pattern.SpriteIDList.end(), objectSpriteID) != pattern.SpriteIDList.end())
                {
                    if (pattern.Width > pattern.Height) // horizontal
                    {
                        uint32_t objectTileX = object->getTileX();

                        if (m_z & 1)
                        {
                            if (objectTileX & 1)
                            {
                                object->setSpriteID(pattern.SpriteIDList.front());
                            }
                            else
                            {
                                object->setSpriteID(pattern.SpriteIDList.back());
                            }
                        }
                        else
                        {
                            if (objectTileX & 1)
                            {
                                object->setSpriteID(pattern.SpriteIDList.back());
                            }
                            else
                            {
                                object->setSpriteID(pattern.SpriteIDList.front());
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
                                object->setSpriteID(pattern.SpriteIDList.front());
                            }
                            else
                            {
                                object->setSpriteID(pattern.SpriteIDList.back());
                            }
                        }
                        else
                        {
                            if (objectTileY & 1)
                            {
                                object->setSpriteID(pattern.SpriteIDList.back());
                            }
                            else
                            {
                                object->setSpriteID(pattern.SpriteIDList.front());
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
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

void TileMap::draw(const sf::IntRect& rect, sf::RenderTarget& renderTarget)
{
    if (m_tileList.size() == 0)
    {
        return;
    }

    sf::RenderStates renderStates;
    renderStates.texture = &tb::Textures::Sprites;

    m_vertexList.clear();
    m_vertexList.reserve(m_numTiles * 4);

    //g_Log.write("left,top,width,height: {},{},{},{}\n", rect.left, rect.top, rect.width, rect.height);

    int x1 = rect.left;
    int y1 = rect.top;

    int x2 = rect.width;
    int y2 = rect.height;

    for (int i = x1; i < x1 + x2; i++)
    {
        for (int j = y1; j < y1 + y2; j++)
        {
            if (i < 0) continue;
            if (j < 0) continue;

            if (i > m_tileWidth - 1) continue;
            if (j > m_tileHeight - 1) continue;

            uint32_t tileIndex = i + (j * m_tileWidth);

            if (isTileIndexOutOfBounds(tileIndex) == true)
            {
                continue;
            }

            tb::Tile::Ptr tile = m_tileList.at(tileIndex);

            if (tile == nullptr)
            {
                continue;
            }

            tb::SpriteID_t tileSpriteID = tile->getSpriteID();

            if (tileSpriteID == tb::Constants::SpriteIDNull)
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

    tb::SpriteBatch spriteBatch;

    x1 = rect.left;
    y1 = rect.top;

    x2 = rect.width;
    y2 = rect.height;

    for (int i = x1; i < x1 + x2; i++)
    {
        for (int j = y1; j < y1 + y2; j++)
        {
            if (i < 0) continue;
            if (j < 0) continue;

            if (i > m_tileWidth - 1) continue;
            if (j > m_tileHeight - 1) continue;

            uint32_t tileIndex = i + (j * m_tileWidth);

            if (isTileIndexOutOfBounds(tileIndex) == true)
            {
                continue;
            }

            tb::Tile::Ptr tile = m_tileList.at(tileIndex);

            if (tile == nullptr)
            {
                continue;
            }

            tb::Thing::List thingList;

            tb::Object::List* objectList = tile->getObjectList();
            tb::Creature::List* creatureList = tile->getCreatureList();

            size_t thingListReserveSize = objectList->size() + creatureList->size();

            thingList.reserve(thingListReserveSize);

            std::copy(objectList->begin(), objectList->end(), std::back_inserter(thingList));
            std::copy(creatureList->begin(), creatureList->end(), std::back_inserter(thingList));

            std::stable_sort(thingList.begin(), thingList.end(), tb::Thing::SortByTileCoords_t());

            for (auto& thing : thingList)
            {
                if (thing->getThingType() == tb::ThingType::Object)
                {
                    tb::Object::Ptr object = std::static_pointer_cast<tb::Object>(thing);

                    object->update();

                    tb::Sprite* sprite = object->getSprite();

                    spriteBatch.addSprite(sprite, true);
                }
                else if (thing->getThingType() == tb::ThingType::Creature)
                {
                    tb::Creature::Ptr creature = std::static_pointer_cast<tb::Creature>(thing);

                    creature->update();

                    tb::Sprite* sprite = creature->getDummySprite();

                    spriteBatch.addSprite(sprite, true);
                }
            }
        }
    }

    if (spriteBatch.getNumSprites() != 0)
    {
        spriteBatch.draw(renderTarget, renderStates);
    }
}

}
