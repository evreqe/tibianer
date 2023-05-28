#pragma once

#include "common.h"

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

    struct Data
    {
        tb::SpriteID_t SpriteID = 0;
        tb::SpriteFlags SpriteFlags;

        std::string Name;
        std::string Article; // '' or 'a' or 'an'
        std::string Description;

        std::string AnimationName;

        uint8_t TileWidth = 1;
        uint8_t TileHeight = 1;

        float Weight = 0.0f; // cap
        float LightRadius = 0.0f;
    };

    using DataList = std::vector<tb::SpriteData::Data>;

    bool load();
    bool isLoaded();
    bool save();

    tb::SpriteData::DataList* getDataList();

    tb::SpriteData::Data* getDataBySpriteID(const tb::SpriteID_t& spriteID);
    tb::SpriteData::Data* getDataByName(const std::string& name);
    tb::SpriteData::Data* getDataByNameSV(std::string_view name);

private:

    std::string m_fileName = "data/sprites.txt";

    toml::table m_table;

    tb::SpriteData::DataList m_dataList;

    const unsigned int m_numToLoad = tb::Constants::NumSprites;

};

}

namespace
{
    inline tb::SpriteData& g_SpriteData = tb::SpriteData::getInstance();
}
