#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class PatternData
{

public:

    PatternData();
    ~PatternData();

    static PatternData& getInstance()
    {
        static PatternData instance;
        return instance;
    }

private:

    PatternData(const PatternData&) = delete;
    PatternData(PatternData&&) = delete;
    PatternData& operator=(const PatternData&) = delete;
    PatternData& operator=(PatternData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        tb::PatternType PatternType = tb::PatternType::Tile;
        std::uint32_t Width = 0;
        std::uint32_t Height = 0;
        tb::SpriteIDList SpriteIDList;
    };

    using DataList = std::vector<tb::PatternData::Data>;

    bool load();
    bool isLoaded();
    bool save();

    tb::PatternData::DataList* getDataList();

private:

    const std::string m_fileName = "data/patterns.txt";

    toml::table m_table;

    tb::PatternData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 32;

};

}

namespace
{
    inline tb::PatternData& g_PatternData = tb::PatternData::getInstance();
}
