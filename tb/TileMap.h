#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Resources.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteData.h"
#include "tb/PatternData.h"
#include "tb/WaterAnimationData.h"
#include "tb/AnimationData.h"

#include "tb/Tile.h"
#include "tb/Sprite.h"
#include "tb/SpriteBatch.h"
#include "tb/LightBatch.h"
#include "tb/Thing.h"
#include "tb/Object.h"
#include "tb/Creature.h"
#include "tb/Animation.h"

namespace tb
{

class TileMap
{

public:

    TileMap();
    ~TileMap();

    using Ptr = std::shared_ptr<tb::TileMap>;
    using List = std::vector<tb::TileMap::Ptr>;
    using Array = std::array<tb::TileMap, tb::Constants::NumAxisZ>;

    bool load(std::uint32_t tileWidth, std::uint32_t tileHeight, const tb::SpriteIDList& tileSpriteIDList, const std::string& name, tb::TileMapType tileMapType, tb::AxisZ axisZ);

    bool isTileIndexOutOfBounds(tb::TileIndex tileIndex);

    void updateTileUsingSpriteID(tb::Tile::Ptr tile, tb::SpriteID spriteID);

    tb::SpriteIDList* getTileSpriteIDList();

    tb::Tile::List* getTileList();

    tb::Tile::List getTileListWithinTileRect(const tb::TileRect& tileRect);

    bool doAnimatedWater(const tb::TileRect& tileRect);
    bool doAnimatedObjects(const tb::TileRect& tileRect);

    bool applyTilePatterns();
    bool applyTileObjectPatterns();

    bool isLoaded();

    std::string getName();
    void setName(const std::string& name);

    tb::TileMapType getTileMapType();
    void setTileMapType(tb::TileMapType tileMapType);

    tb::AxisZ getAxisZ();
    void setAxisZ(tb::AxisZ axisZ);

    bool isVisibleWithinTileRect(const tb::TileRect& tileRect);

    void drawTiles(const tb::TileRect& tileRect, sf::RenderTarget& renderTarget);
    void drawThings(const tb::TileRect& tileRect, sf::RenderTarget& renderTarget);
    void drawLights(const tb::TileRect& tileRect, sf::RenderTarget& renderTarget, tb::LightBrightness lightBrightness);

private:

    bool m_isLoaded = false;

    std::string m_name;

    tb::TileMapType m_tileMapType = tb::TileMapType::Tiles;

    std::uint32_t m_tileWidth = 0;
    std::uint32_t m_tileHeight = 0;

    std::uint32_t m_numTiles = 0;

    tb::AxisZ m_axisZ = tb::Constants::AxisZDefault;

    tb::SpriteIDList m_tileSpriteIDList;

    tb::Tile::List m_tileList;

    std::uint32_t m_waterAnimationFrame = 0;

    tb::VertexList m_tileVertexList;

    static const std::uint32_t m_numVertexPerTile = 6;

    tb::SpriteBatch m_spriteBatch;
    tb::LightBatch m_lightBatch;

};

}
