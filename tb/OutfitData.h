#pragma once

#include "common.h"

#include "toml.hpp"

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
        OutfitData(const OutfitData&) = delete;
        OutfitData(OutfitData&&) = delete;
        OutfitData& operator=(const OutfitData&) = delete;
        OutfitData& operator=(OutfitData&&) = delete;

        static OutfitData& getInstance()
        {
            static OutfitData OutfitData;
            return OutfitData;
        }

        typedef struct _Outfit
        {
            uint32_t Index = 0;
            std::string Name;
            std::vector<tb::SpriteIDList> SpriteIDList_List;
        } Outfit, * Outfit_ptr;

        using OutfitList = std::vector<tb::OutfitData::Outfit>;

        bool load();
        bool isLoaded();

        tb::OutfitData::OutfitList* getOutfitList();

    private:

        std::string m_fileName = "data/outfits.txt";

        toml::table m_data;

        tb::OutfitData::OutfitList m_outfitList;

        const uint8_t m_numSpriteIDListToLoadPerIndex = 16;

    };

}

namespace
{
    tb::OutfitData& g_OutfitData = tb::OutfitData::getInstance();
}
