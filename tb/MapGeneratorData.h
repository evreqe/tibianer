#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class MapGeneratorData
{

public:

    MapGeneratorData();
    ~MapGeneratorData();

    static MapGeneratorData& getInstance()
    {
        static MapGeneratorData instance;
        return instance;
    }

private:

    MapGeneratorData(const MapGeneratorData&) = delete;
    MapGeneratorData(MapGeneratorData&&) = delete;
    MapGeneratorData& operator=(const MapGeneratorData&) = delete;
    MapGeneratorData& operator=(MapGeneratorData&&) = delete;

public:

    struct Data
    {
        std::string TemplateFileName;
    };

    bool load();
    bool isLoaded();

    tb::MapGeneratorData::Data* getData();

private:

    const std::string m_fileName = "data/map_generator.txt";

    toml::table m_table;

    tb::MapGeneratorData::Data m_data;

};

}

namespace
{
    inline tb::MapGeneratorData& g_MapGeneratorData = tb::MapGeneratorData::getInstance();
}
