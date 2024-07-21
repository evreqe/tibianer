#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class WaterAnimationData
{

public:

    WaterAnimationData();
    ~WaterAnimationData();

    static WaterAnimationData& getInstance()
    {
        static WaterAnimationData instance;
        return instance;
    }

private:

    WaterAnimationData(const WaterAnimationData&) = delete;
    WaterAnimationData(WaterAnimationData&&) = delete;
    WaterAnimationData& operator=(const WaterAnimationData&) = delete;
    WaterAnimationData& operator=(WaterAnimationData&&) = delete;

public:

    bool load();
    bool isLoaded();

    std::vector<tb::SpriteIDList>* getSpriteIDList_List();

private:

    const std::string m_fileName = "data/water_animations.txt";

    toml::table m_table;

    std::vector<tb::SpriteIDList> m_spriteIDList_List;

    const std::uint32_t m_numToLoad = tb::Constants::NumWaterAnimationFrames;

};

}

namespace
{
    inline tb::WaterAnimationData& g_WaterAnimationData = tb::WaterAnimationData::getInstance();
}
