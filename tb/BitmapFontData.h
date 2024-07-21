#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class BitmapFontData
{

public:

    BitmapFontData();
    ~BitmapFontData();

    static BitmapFontData& getInstance()
    {
        static BitmapFontData instance;
        return instance;
    }

private:

    BitmapFontData(const BitmapFontData&) = delete;
    BitmapFontData(BitmapFontData&&) = delete;
    BitmapFontData& operator=(const BitmapFontData&) = delete;
    BitmapFontData& operator=(BitmapFontData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::string FileName;
        std::uint32_t GlyphWidth = 32;
        std::uint32_t GlyphHeight = 32;
        std::int32_t CharacterSpace = 0;
        std::int32_t CharacterHeight = 1;
        std::vector<std::int32_t> CharacterWidthList;

    };

    using DataList = std::vector<tb::BitmapFontData::Data>;

    bool load();
    bool isLoaded();

    tb::BitmapFontData::DataList* getDataList();

private:

    const std::string m_fileName = "data/bitmap_fonts.txt";

    toml::table m_table;

    tb::BitmapFontData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 8;

};

}

namespace
{
    inline tb::BitmapFontData& g_BitmapFontData = tb::BitmapFontData::getInstance();
}
