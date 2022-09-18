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
        WaterData(const WaterData&) = delete;
        WaterData(WaterData&&) = delete;
        WaterData& operator=(const WaterData&) = delete;
        WaterData& operator=(WaterData&&) = delete;

        static WaterData& getInstance()
        {
            static WaterData waterData;
            return waterData;
        }

        bool load();
        bool isLoaded();

        std::vector<tb::SpriteIDList>* getSpriteIDList_List();

    private:

        std::string m_fileName = "data/water_sprites.txt";

        toml::table m_data;

        std::vector<tb::SpriteIDList> m_spriteIDList_List;

    };

}

namespace
{
    tb::WaterData& g_WaterData = tb::WaterData::getInstance();
}
