#pragma once

#include "common.h"

#include "tb/Constants.h"

namespace tb
{

class TileBase
{

public:

    TileBase();
    ~TileBase();

    tb::TileIndex getTileIndex();
    void setTileIndex(tb::TileIndex tileIndex);

    tb::TileCoords getTileCoords();
    void setTileCoords(const tb::TileCoords& tileCoords);

    tb::TileCoord getTileX();
    void setTileX(tb::TileCoord tileX);

    tb::TileCoord getTileY();
    void setTileY(tb::TileCoord tileY);

    tb::PixelCoords getPixelCoords();
    void setPixelCoords(const tb::PixelCoords& pixelCoords);

    tb::PixelCoord getPixelX();
    void setPixelX(tb::PixelCoord pixelX);

    tb::PixelCoord getPixelY();
    void setPixelY(tb::PixelCoord pixelY);

    tb::AxisZ getAxisZ();
    void setAxisZ(tb::AxisZ axisZ);

private:

    tb::TileIndex m_tileIndex = 0;

    tb::TileCoords m_tileCoords;
    tb::PixelCoords m_pixelCoords;

    tb::AxisZ m_axisZ = tb::Constants::AxisZDefault;

};

}
