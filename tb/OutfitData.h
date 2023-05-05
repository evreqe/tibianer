#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class OutfitData
{

public:

    OutfitData();
    ~OutfitData();

    static OutfitData& getInstance()
    {
        static OutfitData instance;
        return instance;
    }

private:

    OutfitData(const OutfitData&) = delete;
    OutfitData(OutfitData&&) = delete;
    OutfitData& operator=(const OutfitData&) = delete;
    OutfitData& operator=(OutfitData&&) = delete;

public:

    typedef struct _Data
    {
        uint32_t Index = 0;
        std::string Name;
        std::vector<tb::SpriteIDList> SpriteIDList_List;
    } Data, *Data_ptr;

    using DataList = std::vector<tb::OutfitData::Data>;

    bool load();
    bool isLoaded();

    tb::OutfitData::DataList* getDataList();

private:

    std::string m_fileName = "data/outfits.txt";

    toml::table m_table;

    tb::OutfitData::DataList m_dataList;

    const unsigned int m_numToLoad = tb::Constants::NumOutfitSpriteIndex;

    const unsigned int m_numSpriteIDListToLoadPerIndex = 16;    // Sprites#=[]

};

}

namespace
{
    inline tb::OutfitData& g_OutfitData = tb::OutfitData::getInstance();
}
