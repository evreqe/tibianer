#pragma once

#include "common.h"

#include "toml.hpp"

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

    typedef struct _Data
    {
        uint32_t Index = 0;
        std::string Name;
        std::string FileName;
        uint8_t GlyphWidth = 32;
        uint8_t GlyphHeight = 32;
        float TextHeight = 1.0f;
        std::vector<unsigned int> GlyphWidthList;

    } Data, * Data_ptr;

    using DataList = std::vector<tb::BitmapFontData::Data>;

    bool load();
    bool isLoaded();

    tb::BitmapFontData::DataList* getDataList();

private:

    std::string m_fileName = "data/bitmap_fonts.txt";

    toml::table m_data;

    tb::BitmapFontData::DataList m_dataList;

    const unsigned int m_numToLoad = 8;

    const unsigned int m_numGlyphs = 96;

};

}

namespace
{
    inline tb::BitmapFontData& g_BitmapFontData = tb::BitmapFontData::getInstance();
}