#pragma once

#include "common.h"

#include "toml.hpp"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteFlags.h"

namespace tb
{

class SpriteData
{

public:

    SpriteData();
    ~SpriteData();

    static SpriteData& getInstance()
    {
        static SpriteData instance;
        return instance;
    }

private:

    SpriteData(const SpriteData&) = delete;
    SpriteData(SpriteData&&) = delete;
    SpriteData& operator=(const SpriteData&) = delete;
    SpriteData& operator=(SpriteData&&) = delete;

public:

    typedef struct _Data
    {
        tb::SpriteID_t SpriteID = 0;
        tb::SpriteFlags SpriteFlags;
        std::string Article = ""; // '' or 'a' or 'an'
        std::string Name;
        float Weight = 0.0f; // cap
        uint8_t TileWidth = 1;
        uint8_t TileHeight = 1;

    } Data, *Data_ptr;

    using DataList = std::vector<tb::SpriteData::Data>;

    bool load();
    bool isLoaded();
    bool save();

    tb::SpriteData::DataList* getDataList();

private:

    std::string m_fileName = "data/sprites.txt";

    toml::table m_data;

    tb::SpriteData::DataList m_dataList;

    const unsigned int m_numToLoad = tb::Constants::NumSprites;

};

}

namespace
{
    inline tb::SpriteData& g_SpriteData = tb::SpriteData::getInstance();
}
