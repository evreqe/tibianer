#pragma once

#include "common.h"

#include "tb/Constants.h"
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
    using Array = std::array<tb::TileMap, tb::Constants::NumZAxis>;

    bool load(std::uint32_t tileWidth, std::uint32_t tileHeight, const tb::SpriteIDList& tileSpriteIDList, const std::string& name, tb::TileMapType tileMapType, tb::ZAxis_t z);

    bool isTileIndexOutOfBounds(std::uint32_t tileIndex);

    void updateTileSpriteID(tb::Tile::Ptr tile, tb::SpriteID_t spriteID);
    void updateTileSpriteFlags(tb::Tile::Ptr tile, tb::SpriteID_t spriteID);

    tb::SpriteIDList* getTileSpriteIDList();

    tb::Tile::List* getTileList();

    tb::Tile::List getTileListWithinTileRect(const sf::IntRect& tileRect);

    bool doAnimatedWater(const sf::IntRect& tileRect);
    bool doAnimatedObjects(const sf::IntRect& tileRect);

    bool applyTilePatterns();
    bool applyTileObjectPatterns();

    bool isLoaded();

    std::string getName();
    void setName(const std::string& name);

    tb::TileMapType getTileMapType();
    void setTileMapType(tb::TileMapType tileMapType);

    tb::ZAxis_t getZ();
    void setZ(tb::ZAxis_t z);

    bool isVisibleWithinTileRect(const sf::IntRect& tileRect);

    void drawTiles(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget);
    void drawThings(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget);
    void drawLights(const sf::IntRect& tileRect, sf::RenderTarget& renderTarget, tb::LightBrightness_t lightBrightness);

private:

    bool m_isLoaded = false;

    std::string m_name;

    tb::TileMapType m_tileMapType = tb::TileMapType::Tiles;

    std::uint32_t m_tileWidth = 0;
    std::uint32_t m_tileHeight = 0;

    std::uint32_t m_numTiles = 0;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    tb::SpriteIDList m_tileSpriteIDList;

    tb::Tile::List m_tileList;

    std::uint32_t m_waterAnimationFrame = 0;

    std::vector<sf::Vertex> m_tileVertexList;

};

}
