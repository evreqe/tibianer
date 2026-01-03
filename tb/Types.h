#pragma once

#include "common.h"

namespace tb
{
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using f32 = float;
    using f64 = double;

    using SpriteID = std::uint16_t;
    using SpriteIDList = std::vector<tb::SpriteID>;

    using ZAxis = std::uint8_t;

    struct ZAxisVisible
    {
        tb::ZAxis Begin;
        tb::ZAxis End;
    };

    using LightBrightness = std::uint8_t;
    using OutfitIndex = std::uint8_t;
}
