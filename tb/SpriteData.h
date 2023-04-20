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

    struct Data
    {
        tb::SpriteID_t SpriteID = 0;
        tb::SpriteFlags SpriteFlags;

        std::string Name;
        std::string Article = ""; // '' or 'a' or 'an'
        std::string Description;

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

    tb::SpriteID_t getSpriteIDBySpriteName(const std::string& spriteName);

private:

    std::string m_fileName = "data/sprites.txt";

    toml::table m_table;

    tb::SpriteData::DataList m_dataList;

    std::unordered_map<std::string, tb::SpriteID_t> m_spriteNameToSpriteIDMap;

    const unsigned int m_numToLoad = tb::Constants::NumSprites;

};

}

namespace
{
    inline tb::SpriteData& g_SpriteData = tb::SpriteData::getInstance();
}
