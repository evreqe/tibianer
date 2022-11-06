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

bool TileMap::load(uint32_t tileWidth, uint32_t tileHeight, const tb::SpriteIDList& tileSpriteIDList, const std::string& name, tb::TileMapType tileMapType, tb::ZAxis_t z)
{
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: Sprite data is not loaded\n");
        return false;
    }

    if (tileWidth == 0 || tileHeight == 0)
    {
        g_Log.write("ERROR: Tile width or tile height is zero\n");
        return false;
    }

    if (tileSpriteIDList.size() == 0)
    {
        g_Log.write("ERROR: Tile sprite ID list is empty\n");
        return false;
    }

    if (name.size() == 0)
    {
        g_Log.write("ERROR: Name is empty\n");
        return false;
    }

    m_name = name;

    m_tileMapType = tileMapType;

    m_tileWidth = tileWidth;
    m_tileHeight = tileHeight;

    m_numTiles = m_tileWidth * m_tileHeight;

    m_z = z;

    m_waterAnimationFrame = 1; // start the animation at index 1 because the applied water pattern starts at index 0

    m_tileList.clear();
    m_tileList.reserve(m_numTiles);

    m_tileSpriteIDList.clear();
    m_tileSpriteIDList.reserve(m_numTiles);
    //m_tileSpriteIDList.swap(tileSpriteIDList); // cannot use swap with const reference
    m_tileSpriteIDList = tileSpriteIDList;

    g_Log.write("z: {}\n", z);
    g_Log.write("name: {}\n", m_name);
    g_Log.write("tile width and height: {}x{}\n", m_tileWidth, m_tileHeight);
    g_Log.write("tile sprite ID list size: {}\n", m_tileSpriteIDList.size());
    g_Log.write("tile map type: {}\n", magic_enum::enum_name(m_tileMapType));

    for (int tileX = 0; tileX < m_tileWidth; tileX++)
    {
        for (int tileY = 0; tileY < m_tileHeight; tileY++)
        {
            uint32_t tileIndex = tileX + tileY * m_tileWidth;

            if (tileIndex > m_tileSpriteIDList.size())
            {
                g_Log.write("ERROR: Tile index is out of bounds: {}\n", tileIndex);
                continue;
            }

            tb::SpriteID_t tileSpriteID = m_tileSpriteIDList.at(tileIndex);

            tb::SpriteFlags* tileSpriteFlags = &g_SpriteData.getDataList()->at(tileSpriteID).SpriteFlags;

            if (tileSpriteID == tb::Constants::SpriteIDNull && m_tileMapType == tb::TileMapType::Tiles)
            {
                tileSpriteFlags->setFlag(tb::SpriteFlag::Null, true);
            }

            tb::Tile::Ptr tile = std::make_shared<tb::Tile>();
            tile->setTileIndex(tileIndex);
            tile->setSpriteID(tileSpriteID);
            tile->setSpriteFlags(*tileSpriteFlags);
            tile->setTileCoords(sf::Vector2i(tileX, tileY));
            tile->setZ(z);
            m_tileList.push_back(tile);
        }
    }

    std::sort(m_tileList.begin(), m_tileList.end(), tb::Tile::SortByTileIndex_t());

    if (m_tileMapType == tb::TileMapType::Tiles)
    {
        loadWaterTiles();

        sf::Clock timeToApplyTilePatterns;

        g_Log.write("Applying tile patterns to tile map...\n");
        if (applyTilePatterns() == false)
        {
            g_Log.write("ERROR: Failed to apply tile patterns to tile map\n");
            return false;
        }

        g_Log.write("Tile patterns applied in {} seconds\n", timeToApplyTilePatterns.getElapsedTime().asSeconds());
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
    tb::SpriteFlags* tileSpriteFlags = &g_SpriteData.getDataList()->at(spriteID).SpriteFlags;

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

tb::Tile::List TileMap::getTileListWithinTileRect(const sf::IntRect& tileRect)
{
    tb::Tile::List tileList;

    if (m_tileList.size() == 0)
    {
        return tileList;
    }

    int x1 = tileRect.left;
    int y1 = tileRect.top;

    int x2 = tileRect.width;
    int y2 = tileRect.height;

    for (int tileX = x1; tileX < x1 + x2; tileX++)
    {
        for (int tileY = y1; tileY < y1 + y2; tileY++)
        {
            if (tileX < 0) continue;
            if (tileY < 0) continue;

            if (tileX > m_tileWidth - 1) continue;
            if (tileY > m_tileHeight - 1) continue;

            uint32_t tileIndex = tileX + tileY * m_tileWidth;

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

            tileList.push_back(tile);
        }
    }

    return tileList;
}

void TileMap::loadWaterTiles()
{
    if (m_z != tb::ZAxis::Default)
    {
        return;
    }

    if (m_tileMapType != tb::TileMapType::Tiles)
    {
        return;
    }

    m_waterTileList.clear();
    m_waterTileList.reserve(m_numTiles);

    for (auto& tile : m_tileList)
    {
        if (tile->getSpriteFlags()->hasFlag(tb::SpriteFlag::Water) == true)
        {
            m_waterTileList.push_back(tile);
        }
    }
}

bool TileMap::doAnimatedWater(const sf::IntRect& tileRect)
{
    auto waterSpriteIDList_List = g_WaterAnimationData.getSpriteIDList_List();
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

    tb::Tile::List tileList = getTileListWithinTileRect(tileRect);

    for (auto& tile : tileList)
    {
        if (tile->getSpriteFlags()->hasFlag(tb::SpriteFlag::Water) == false)
        {
            continue;
        }

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
    auto patternList = g_PatternData.getDataList();
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

        if (pattern.Name == "Water")
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

            while (spriteIndex > static_cast<unsigned int>(pattern.Width - 1))
            {
                spriteIndex = spriteIndex - pattern.Width;
            }

            while (tileRowIndex > static_cast<unsigned int>(pattern.Height - 1))
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
    auto patternList = g_PatternData.getDataList();
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
                        int objectTileX = object->getTileX();

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
                        int objectTileY = object->getTileY();

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

bool TileMap::isVisibleWithinTileRect(const sf::IntRect& tileRect)
{
    // checks to see if any of the tiles of this tile map are visible within a rectangle
    // used to skip drawing of a tile map if the player cannot see it

    if (m_tileList.size() == 0)
    {
        return false;
    }

    int x1 = tileRect.left;
    int y1 = tileRect.top;

    int x2 = tileRect.width;
    int y2 = tileRect.height;

    for (int tileX = x1; tileX < x1 + x2; tileX++)
    {
        for (int tileY = y1; tileY < y1 + y2; tileY++)
        {
            if (tileX < 0) continue;
            if (tileY < 0) continue;

            if (tileX > m_tileWidth - 1) continue;
            if (tileY > m_tileHeight - 1) continue;

            uint32_t tileIndex = tileX + tileY * m_tileWidth;

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

            return true;
        }
    }

    return false;
}

void TileMap::draw(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget)
{
    tb::Tile::List tileList = getTileListWithinTileRect(tileRect);

    if (tileList.size() == 0)
    {
        return;
    }

    sf::RenderStates renderStates;
    renderStates.texture = &tb::Textures::Sprites;

    m_vertexList.clear();
    m_vertexList.reserve(m_numTiles * 4);

    unsigned int spritesSizeX = tb::Textures::Sprites.getSize().x;
    unsigned int spritesSizeY = tb::Textures::Sprites.getSize().y;

    for (auto& tile : tileList)
    {
        tb::SpriteID_t tileSpriteID = tile->getSpriteID();

        if (tileSpriteID == tb::Constants::SpriteIDNull)
        {
            continue;
        }

        int tileX = tile->getTileX();
        int tileY = tile->getTileY();

        unsigned int u = (tileSpriteID - 1) % (spritesSizeX / tb::Constants::TileSize);
        unsigned int v = (tileSpriteID - 1) / (spritesSizeY / tb::Constants::TileSize);

        sf::Vertex vertex[4];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2i(tileX       * tb::Constants::TileSize, tileY       * tb::Constants::TileSize));
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2i((tileX + 1) * tb::Constants::TileSize, tileY       * tb::Constants::TileSize));
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2i((tileX + 1) * tb::Constants::TileSize, (tileY + 1) * tb::Constants::TileSize));
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2i(tileX       * tb::Constants::TileSize, (tileY + 1) * tb::Constants::TileSize));

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2i(u       * tb::Constants::TileSize, v       * tb::Constants::TileSize));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2i((u + 1) * tb::Constants::TileSize, v       * tb::Constants::TileSize));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2i((u + 1) * tb::Constants::TileSize, (v + 1) * tb::Constants::TileSize));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2i(u       * tb::Constants::TileSize, (v + 1) * tb::Constants::TileSize));

        tb::SpriteFlags* tileSpriteFlags = tile->getSpriteFlags();

        if (tileSpriteFlags->hasFlag(tb::SpriteFlag::NoDraw) == true)
        {
            vertex[0].color = sf::Color::Transparent;
            vertex[1].color = sf::Color::Transparent;
            vertex[2].color = sf::Color::Transparent;
            vertex[3].color = sf::Color::Transparent;
        }

        m_vertexList.push_back(vertex[0]);
        m_vertexList.push_back(vertex[1]);
        m_vertexList.push_back(vertex[2]);
        m_vertexList.push_back(vertex[3]);
    }

    //g_Log.write("m_vertexList.size(): {}\n", m_vertexList.size());

    if (m_vertexList.size() != 0)
    {
        renderTarget.draw(&m_vertexList[0], m_vertexList.size(), sf::Quads, renderStates);
    }

    tb::SpriteBatch spriteBatch;

    for (auto& tile : tileList)
    {
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

    if (spriteBatch.getNumSprites() != 0)
    {
        spriteBatch.draw(renderTarget, renderStates);
    }
}

}
