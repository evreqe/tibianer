#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteData.h"
#include "tb/PatternData.h"
#include "tb/WaterAnimationData.h"

#include "tb/Tile.h"
#include "tb/Sprite.h"
#include "tb/SpriteBatch.h"
#include "tb/LightBatch.h"

#include "tb/Thing.h"
#include "tb/Object.h"
#include "tb/Creature.h"

namespace tb
{

class TileMap
{

public:

    TileMap();
    ~TileMap();

    using Array = std::array<tb::TileMap, tb::Constants::NumZAxis>;

    bool load(uint32_t tileWidth, uint32_t tileHeight, const tb::SpriteIDList& tileSpriteIDList, const std::string& name, tb::TileMapType tileMapType, tb::ZAxis_t z);

    bool isTileIndexOutOfBounds(uint32_t tileIndex);

    void updateTileSpriteID(tb::Tile::Ptr tile, tb::SpriteID_t spriteID);
    void updateTileSpriteFlags(tb::Tile::Ptr tile, tb::SpriteID_t spriteID);

    tb::SpriteIDList* getTileSpriteIDList();

    tb::Tile::List* getTileList();
    tb::Tile::List* getWaterTileList();

    tb::Tile::List getTileListWithinTileRect(const sf::IntRect& tileRect);

    void loadWaterTiles();

    bool doAnimatedWater(const sf::IntRect& tileRect);

    bool applyTilePatterns();
    bool applyTileObjectPatterns();

    const std::string& getName();
    void setName(const std::string& name);

    tb::TileMapType getTileMapType();
    void setTileMapType(tb::TileMapType tileMapType);

    tb::ZAxis_t getZ();
    void setZ(tb::ZAxis_t z);

    bool isVisibleWithinTileRect(const sf::IntRect& tileRect);

    void draw(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget);

    void drawLights(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget);

private:

    std::string m_name;

    tb::TileMapType m_tileMapType = tb::TileMapType::Tiles;

    uint32_t m_tileWidth = 0;
    uint32_t m_tileHeight = 0;

    uint32_t m_numTiles = 0;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    tb::SpriteIDList m_tileSpriteIDList;

    tb::Tile::List m_tileList;
    tb::Tile::List m_waterTileList;

    uint32_t m_waterAnimationFrame = 0;

    std::vector<sf::Vertex> m_vertexList;

};

}
