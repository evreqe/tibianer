#pragma once

#include "common.h"

#include "toml.hpp"

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

    typedef struct _Data
    {
        uint32_t Index = 0;
        std::string Name;
        tb::PatternType PatternType = tb::PatternType::Tile;
        uint8_t Width = 0;
        uint8_t Height = 0;
        tb::SpriteIDList SpriteIDList;
    } Data, *Data_ptr;

    using DataList = std::vector<tb::PatternData::Data>;

    bool load();
    bool isLoaded();
    bool save();

    tb::PatternData::DataList* getDataList();

private:

    std::string m_fileName = "data/patterns.txt";

    toml::table m_table;

    tb::PatternData::DataList m_dataList;

    const unsigned int m_numToLoad = 16;

};

}

namespace
{
    inline tb::PatternData& g_PatternData = tb::PatternData::getInstance();
}
