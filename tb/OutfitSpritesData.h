#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class OutfitSpritesData
{

public:

    OutfitSpritesData();
    ~OutfitSpritesData();

    static OutfitSpritesData& getInstance()
    {
        static OutfitSpritesData instance;
        return instance;
    }

private:

    OutfitSpritesData(const OutfitSpritesData&) = delete;
    OutfitSpritesData(OutfitSpritesData&&) = delete;
    OutfitSpritesData& operator=(const OutfitSpritesData&) = delete;
    OutfitSpritesData& operator=(OutfitSpritesData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::vector<tb::SpriteIDList> SpriteIDList_List;
    };

    using DataList = std::vector<tb::OutfitSpritesData::Data>;

    bool load();
    bool isLoaded();

    tb::OutfitSpritesData::DataList* getDataList();

private:

    const std::string m_fileName = "data/outfit_sprites.txt";

    toml::table m_table;

    tb::OutfitSpritesData::DataList m_dataList;

    const std::uint32_t m_numToLoad = tb::Constants::NumOutfitSpriteIndex;

    const std::uint32_t m_numSpriteIDListToLoadPerIndex = 16;    // Sprites#=[]

};

}

namespace
{
    inline tb::OutfitSpritesData& g_OutfitSpritesData = tb::OutfitSpritesData::getInstance();
}
