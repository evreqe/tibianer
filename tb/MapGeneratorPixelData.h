#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class MapGeneratorPixelData
{

public:

    MapGeneratorPixelData();
    ~MapGeneratorPixelData();

    static MapGeneratorPixelData& getInstance()
    {
        static MapGeneratorPixelData instance;
        return instance;
    }

private:

    MapGeneratorPixelData(const MapGeneratorPixelData&) = delete;
    MapGeneratorPixelData(MapGeneratorPixelData&&) = delete;
    MapGeneratorPixelData& operator=(const MapGeneratorPixelData&) = delete;
    MapGeneratorPixelData& operator=(MapGeneratorPixelData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::string Type;
        std::string Edge;
        std::uint32_t ColorR = 0;
        std::uint32_t ColorG = 0;
        std::uint32_t ColorB = 0;
        tb::SpriteIDList SpriteIDList;
        tb::SpriteIDList CornersSpriteIDList;
        tb::SpriteIDList EdgesSpriteIDList;
    };

    using DataList = std::vector<tb::MapGeneratorPixelData::Data>;

    bool load();
    bool isLoaded();

    tb::MapGeneratorPixelData::DataList* getDataList();

    tb::MapGeneratorPixelData::Data* getDataByName(const std::string& name);

private:

    const std::string m_fileName = "data/map_generator_pixels.txt";

    toml::table m_table;

    tb::MapGeneratorPixelData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 8;

    const std::uint32_t m_numSpritesToReserve = 4;
    const std::uint32_t m_numCornerSpritesToReserve = 4;
    const std::uint32_t m_numEdgeSpritesToReserve = 9;

    const std::uint32_t m_maxColorValue = 255;

};

}

namespace
{
    inline tb::MapGeneratorPixelData& g_MapGeneratorPixelData = tb::MapGeneratorPixelData::getInstance();
}
