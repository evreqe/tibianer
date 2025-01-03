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

bool TileMap::load(std::uint32_t tileWidth, std::uint32_t tileHeight, const tb::SpriteIDList& tileSpriteIDList, const std::string& name, tb::TileMapType tileMapType, tb::ZAxis_t z)
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
    m_tileSpriteIDList = tileSpriteIDList;

    g_Log.write("Tile Map Z: {}\n", z);
    g_Log.write("Tile Map Name: {}\n", m_name);
    g_Log.write("Tile Map Width and Height: {}x{}\n", m_tileWidth, m_tileHeight);
    g_Log.write("Tile Map Sprite ID List Size: {}\n", m_tileSpriteIDList.size());
    g_Log.write("Tile Map Type: {}\n", magic_enum::enum_name(m_tileMapType));

    for (std::uint32_t tileIndex = 0; tb::SpriteID_t& tileSpriteID : m_tileSpriteIDList)
    {
        //g_Log.write("tileIndex: {}\n", tileIndex);

        //g_Log.write("tileSpriteID: {}\n", tileSpriteID);

        std::int32_t tileX = tileIndex % m_tileWidth;
        std::int32_t tileY = 0;

        if (tileIndex > 0)
        {
            tileY = tileIndex / m_tileHeight;
        }

        //g_Log.write("tileX: {}\n", tileX);
        //g_Log.write("tileY: {}\n", tileY);

        tb::SpriteFlags* tileSpriteFlags = &g_SpriteData.getDataList()->at(tileSpriteID).SpriteFlags;

        // TODO: this might not be needed
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

        tileIndex++;
    }

    if (m_tileMapType == tb::TileMapType::Tiles)
    {
        sf::Clock timeToApplyTilePatterns;

        g_Log.write("Applying tile patterns to tile map...\n");
        if (applyTilePatterns() == false)
        {
            g_Log.write("ERROR: Failed to apply tile patterns to tile map\n");
            return false;
        }

        g_Log.write("Tile patterns applied in {:.2f} seconds\n", timeToApplyTilePatterns.getElapsedTime().asSeconds());
    }

    m_isLoaded = true;

    return true;
}

bool TileMap::isTileIndexOutOfBounds(std::uint32_t tileIndex)
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

tb::Tile::List TileMap::getTileListWithinTileRect(const sf::IntRect& tileRect)
{
    tb::Tile::List tileList;

    if (m_tileList.size() == 0)
    {
        return tileList;
    }

    std::int32_t x1 = tileRect.position.x;
    std::int32_t y1 = tileRect.position.y;

    std::int32_t x2 = x1 + tileRect.size.x;
    std::int32_t y2 = y1 + tileRect.size.y;

    for (std::int32_t tileX = x1; tileX < x2; tileX++)
    {
        for (std::int32_t tileY = y1; tileY < y2; tileY++)
        {
            if (tileX < 0) continue;
            if (tileY < 0) continue;

            if ((std::uint32_t)tileX > m_tileWidth  - 1) continue;
            if ((std::uint32_t)tileY > m_tileHeight - 1) continue;

            std::uint32_t tileIndex = tileX + tileY * m_tileWidth;

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

        std::uint32_t tileColumnIndex = m_tileWidth - tile->getTileX();

        tileColumnIndex = m_tileWidth - tileColumnIndex;

        std::uint32_t tileRowIndex = m_tileHeight - tile->getTileY();

        tileRowIndex = m_tileHeight - tileRowIndex;

        std::uint32_t spriteIndex = tileColumnIndex;

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

bool TileMap::doAnimatedObjects(const sf::IntRect& tileRect)
{
    tb::Tile::List tileList = getTileListWithinTileRect(tileRect);

    for (auto& tile : tileList)
    {
        tb::Object::List* objectList = tile->getObjectList();

        for (auto& object : *objectList)
        {
            object->animate();
        }
    }

    return true;
}

bool TileMap::applyTilePatterns()
{
    tb::PatternData::DataList* patternDataList = g_PatternData.getDataList();
    if (patternDataList == nullptr)
    {
        g_Log.write("ERROR: patternDataList == nullptr\n");
        return false;
    }

    for (auto& patternData : *patternDataList)
    {
        if (patternData.PatternType != PatternType::Tile)
        {
            continue;
        }

        tb::Tile::List* tileList = &m_tileList;

        for (auto& tile : *tileList)
        {
            tb::SpriteID_t tileSpriteID = tile->getSpriteID();

            if (std::find(patternData.SpriteIDList.begin(), patternData.SpriteIDList.end(), tileSpriteID) == patternData.SpriteIDList.end())
            {
                continue;
            }

            std::uint32_t tileColumnIndex = m_tileWidth - tile->getTileX();

            tileColumnIndex = m_tileWidth - tileColumnIndex;

            std::uint32_t tileRowIndex = m_tileHeight - tile->getTileY();

            tileRowIndex = m_tileHeight - tileRowIndex;

            std::uint32_t spriteIndex = tileColumnIndex;

            while (spriteIndex > static_cast<unsigned int>(patternData.Width - 1))
            {
                spriteIndex = spriteIndex - patternData.Width;
            }

            while (tileRowIndex > static_cast<unsigned int>(patternData.Height - 1))
            {
                tileRowIndex = tileRowIndex - patternData.Height;
            }

            if (tileRowIndex > 0)
            {
                spriteIndex += patternData.Width * tileRowIndex;
            }

            if (spriteIndex < patternData.SpriteIDList.size())
            {
                updateTileSpriteID(tile, patternData.SpriteIDList.at(spriteIndex));
            }
        }
    }

    return true;
}

bool TileMap::applyTileObjectPatterns()
{
    auto patternDataList = g_PatternData.getDataList();
    if (patternDataList == nullptr)
    {
        g_Log.write("ERROR: patternDataList == nullptr\n");
        return false;
    }

    for (auto& patternData : *patternDataList)
    {
        if (patternData.PatternType != PatternType::Object)
        {
            continue;
        }

        for (auto& tile : m_tileList)
        {
            tb::Object::List* tileObjectList = tile->getObjectList();

            for (auto& object : *tileObjectList)
            {
                tb::SpriteID_t objectSpriteID = object->getSpriteID();

                if (std::find(patternData.SpriteIDList.begin(), patternData.SpriteIDList.end(), objectSpriteID) != patternData.SpriteIDList.end())
                {
                    if (patternData.Width > patternData.Height) // horizontal
                    {
                        std::int32_t objectTileX = object->getTileX();

                        if (m_z & 1)
                        {
                            if (objectTileX & 1)
                            {
                                object->setSpriteID(patternData.SpriteIDList.front());
                            }
                            else
                            {
                                object->setSpriteID(patternData.SpriteIDList.back());
                            }
                        }
                        else
                        {
                            if (objectTileX & 1)
                            {
                                object->setSpriteID(patternData.SpriteIDList.back());
                            }
                            else
                            {
                                object->setSpriteID(patternData.SpriteIDList.front());
                            }
                        }
                    }
                    else if (patternData.Height > patternData.Width) // vertical
                    {
                        std::int32_t objectTileY = object->getTileY();

                        if (m_z & 1)
                        {
                            if (objectTileY & 1)
                            {
                                object->setSpriteID(patternData.SpriteIDList.front());
                            }
                            else
                            {
                                object->setSpriteID(patternData.SpriteIDList.back());
                            }
                        }
                        else
                        {
                            if (objectTileY & 1)
                            {
                                object->setSpriteID(patternData.SpriteIDList.back());
                            }
                            else
                            {
                                object->setSpriteID(patternData.SpriteIDList.front());
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool TileMap::isLoaded()
{
    return m_isLoaded;
}

std::string TileMap::getName()
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

    std::int32_t x1 = tileRect.position.x;
    std::int32_t y1 = tileRect.position.y;

    std::int32_t x2 = x1 + tileRect.size.x;
    std::int32_t y2 = y1 + tileRect.size.y;

    for (std::int32_t tileX = x1; tileX < x2; tileX++)
    {
        for (std::int32_t tileY = y1; tileY < y2; tileY++)
        {
            if (tileX < 0) continue;
            if (tileY < 0) continue;

            if ((std::uint32_t)tileX > m_tileWidth - 1) continue;
            if ((std::uint32_t)tileY > m_tileHeight - 1) continue;

            std::uint32_t tileIndex = tileX + tileY * m_tileWidth;

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

void TileMap::drawTiles(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget)
{
    tb::Tile::List tileList = getTileListWithinTileRect(tileRect);

    if (tileList.size() == 0)
    {
        return;
    }

    //g_Log.write("Drawing {} tile(s)...\n", tileList.size());

    const std::uint32_t tileSize = tb::Constants::TileSize;

    sf::Vector2u spriteTextureSize = tb::Textures::Sprites.getSize();

    const std::uint32_t numVertices = m_numTiles * m_numVertexPerTile;

    m_tileVertexList.clear();
    m_tileVertexList.reserve(numVertices);

    for (auto& tile : tileList)
    {
        tb::SpriteID_t tileSpriteID = tile->getSpriteID();

        if (tileSpriteID == tb::Constants::SpriteIDNull)
        {
            return;
        }

        std::int32_t tileX = tile->getTileX();
        std::int32_t tileY = tile->getTileY();

        std::uint32_t tileU = (tileSpriteID - 1) % (spriteTextureSize.x / tileSize);
        std::uint32_t tileV = (tileSpriteID - 1) / (spriteTextureSize.y / tileSize);

        sf::Vertex vertex[m_numVertexPerTile];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2i(tileX       * tileSize, tileY       * tileSize)); // top left
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2i((tileX + 1) * tileSize, tileY       * tileSize)); // top right
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2i(tileX       * tileSize, (tileY + 1) * tileSize)); // bottom left
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2i(tileX       * tileSize, (tileY + 1) * tileSize)); // bottom left
        vertex[4].position = static_cast<sf::Vector2f>(sf::Vector2i((tileX + 1) * tileSize, tileY       * tileSize)); // top right
        vertex[5].position = static_cast<sf::Vector2f>(sf::Vector2i((tileX + 1) * tileSize, (tileY + 1) * tileSize)); // bottom right

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2i(tileU       * tileSize, tileV           * tileSize));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2i((tileU + 1) * tileSize, tileV           * tileSize));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2i(tileU       * tileSize, (tileV + 1)     * tileSize));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2i(tileU       * tileSize, (tileV + 1)     * tileSize));
        vertex[4].texCoords = static_cast<sf::Vector2f>(sf::Vector2i((tileU + 1) * tileSize, tileV           * tileSize));
        vertex[5].texCoords = static_cast<sf::Vector2f>(sf::Vector2i((tileU + 1) * tileSize, (tileV + 1)     * tileSize));

        tb::SpriteFlags* tileSpriteFlags = tile->getSpriteFlags();

        if (tileSpriteFlags->hasFlag(tb::SpriteFlag::NoDraw) == true)
        {
            vertex[0].color = sf::Color::Transparent;
            vertex[1].color = sf::Color::Transparent;
            vertex[2].color = sf::Color::Transparent;
            vertex[3].color = sf::Color::Transparent;
            vertex[4].color = sf::Color::Transparent;
            vertex[5].color = sf::Color::Transparent;
        }

        m_tileVertexList.push_back(vertex[0]);
        m_tileVertexList.push_back(vertex[1]);
        m_tileVertexList.push_back(vertex[2]);
        m_tileVertexList.push_back(vertex[3]);
        m_tileVertexList.push_back(vertex[4]);
        m_tileVertexList.push_back(vertex[5]);
    }

    //g_Log.write("m_tileVertexList.size(): {}\n", m_tileVertexList.size());

    if (m_tileVertexList.size() != 0)
    {
        sf::RenderStates renderStates;
        renderStates.texture = &tb::Textures::Sprites;

        renderTarget.draw(&m_tileVertexList[0], m_tileVertexList.size(), sf::PrimitiveType::Triangles, renderStates);
    }
}

void TileMap::drawThings(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget)
{
    tb::Tile::List tileList = getTileListWithinTileRect(tileRect);

    if (tileList.size() == 0)
    {
        return;
    }

    tb::SpriteBatch spriteBatch;

    for (auto& tile : tileList)
    {
        tb::Object::List* tileEdgeObjectList = tile->getTileEdgeObjectList();

        for (auto& tileEdgeObject : *tileEdgeObjectList)
        {
            tb::Sprite* tileEdgeObjectSprite = tileEdgeObject->getSprite();

            if (tileEdgeObjectSprite == nullptr)
            {
                continue;
            }

            spriteBatch.addSprite(tileEdgeObjectSprite, false);
        }

        tb::Thing::List thingList;

        tb::Object::List* objectList = tile->getObjectList();
        tb::Creature::List* creatureList = tile->getCreatureList();
        tb::Animation::List* animationList = tile->getAnimationList();

        std::size_t thingListReserveSize = objectList->size() + creatureList->size() + animationList->size();

        thingList.reserve(thingListReserveSize);

        thingList.insert(thingList.end(), objectList->begin(), objectList->end());
        thingList.insert(thingList.end(), creatureList->begin(), creatureList->end());
        thingList.insert(thingList.end(), animationList->begin(), animationList->end());

        std::stable_sort(std::execution::par, thingList.begin(), thingList.end(), tb::Thing::SortByTileCoords_t());

        for (auto& thing : thingList)
        {
            if (thing->getThingType() == tb::ThingType::Object)
            {
                tb::Object::Ptr object = std::static_pointer_cast<tb::Object>(thing);

                object->update();

                if (object->getThingProperties()->Erase == true)
                {
                    tile->removeObject(object);
                    continue;
                }

                tb::Sprite* objectSprite = object->getSprite();

                if (objectSprite == nullptr)
                {
                    continue;
                }

                spriteBatch.addSprite(objectSprite, true);
            }
            else if (thing->getThingType() == tb::ThingType::Creature)
            {
                tb::Creature::Ptr creature = std::static_pointer_cast<tb::Creature>(thing);

                creature->update();

                if (creature->getThingProperties()->Erase == true)
                {
                    tile->removeCreature(creature);
                    continue;
                }

                std::vector<tb::Sprite*> creatureSpriteList = creature->getSpriteList();

                for (auto& creatureSprite : creatureSpriteList)
                {
                    if (creatureSprite == nullptr)
                    {
                        continue;
                    }

                    spriteBatch.addSprite(creatureSprite, false);
                }
            }
            else if (thing->getThingType() == tb::ThingType::Animation)
            {
                tb::Animation::Ptr animation = std::static_pointer_cast<tb::Animation>(thing);

                animation->update();

                if (animation->getThingProperties()->Erase == true)
                {
                    tile->removeAnimation(animation);
                    continue;
                }

                tb::Sprite* animationSprite = animation->getSprite();

                if (animationSprite == nullptr)
                {
                    continue;
                }

                spriteBatch.addSprite(animationSprite, false);
            }
        }
    }

    if (spriteBatch.getNumSprites() != 0)
    {
        sf::RenderStates renderStates;
        renderStates.texture = &tb::Textures::Sprites;

        spriteBatch.draw(renderTarget, renderStates);
    }
}

void TileMap::drawLights(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget, tb::LightBrightness_t lightBrightness)
{
    tb::Tile::List tileList = getTileListWithinTileRect(tileRect);

    if (tileList.size() == 0)
    {
        return;
    }

    tb::LightBatch lightBatch;

    for (auto& tile1 : tileList)
    {
        sf::Vector2f tile1Position = tile1->getPixelCoords();

        tb::Object::List* objectList = tile1->getObjectList();

        for (auto& object : *objectList)
        {
            tb::SpriteID_t objectSpriteID = object->getSpriteID();

            tb::SpriteData::Data* objectSpriteData = &g_SpriteData.getDataList()->at(objectSpriteID);

            float objectLightRadius = objectSpriteData->LightRadius;

            if (objectLightRadius < 1.0f)
            {
                continue;
            }

            objectLightRadius = objectLightRadius * tb::Constants::TileSizeAsFloat;

            for (auto& tile2 : tileList)
            {
                sf::Vector2f tile2Position = tile2->getPixelCoords();

                float distance = -1.0f;

                if (tb::Utility::isPositionInsideCircle(tile1Position, tile2Position, objectLightRadius, distance) == false)
                {
                    continue;
                }

                float brightness = ((objectLightRadius - distance) / objectLightRadius) * 255.0f;

                std::uint8_t rgb = static_cast<std::uint8_t>(brightness);

                sf::Color lightColor = sf::Color(rgb, rgb, rgb, 255);

                lightBatch.addLight(tile2Position, lightColor);
            }
        }
    }

    if (lightBatch.getNumLights() != 0)
    {
        lightBatch.draw(renderTarget, sf::BlendAdd);
    }
}

}
