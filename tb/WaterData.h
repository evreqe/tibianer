#pragma once

#include "common.h"

#include "toml.hpp"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class WaterData
{

public:

    WaterData();
    ~WaterData();

    static WaterData& getInstance()
    {
        static WaterData instance;
        return instance;
    }

private:

    WaterData(const WaterData&) = delete;
    WaterData(WaterData&&) = delete;
    WaterData& operator=(const WaterData&) = delete;
    WaterData& operator=(WaterData&&) = delete;

public:

    bool load();
    bool isLoaded();

    std::vector<tb::SpriteIDList>* getSpriteIDList_List();

private:

    std::string m_fileName = "data/water.txt";

    toml::table m_data;

    std::vector<tb::SpriteIDList> m_spriteIDList_List;

    const unsigned int m_numToLoad = tb::Constants::NumWaterAnimationFrames;

};

}

namespace
{
    inline tb::WaterData& g_WaterData = tb::WaterData::getInstance();
}
