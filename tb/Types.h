#pragma once

#include "common.h"

namespace tb
{

using TileIndex = std::uint32_t;

using TileCoords = sf::Vector2i;
using PixelCoords = sf::Vector2f;

using TileCoord = std::int32_t;
using PixelCoord = float;

using TileRect = sf::IntRect;
using PixelRect = sf::FloatRect;

using VertexList = std::vector<sf::Vertex>;
using VertexPointerList = std::vector<sf::Vertex*>;

using SpriteID = std::uint16_t;
using SpriteIDList = std::vector<tb::SpriteID>;

using AxisZ = std::uint8_t;

struct AxisZVisibility
{
    tb::AxisZ Begin;
    tb::AxisZ End;
};

using LightBrightness = std::uint8_t;
using OutfitIndex = std::uint8_t;

}
