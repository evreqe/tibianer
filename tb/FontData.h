#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class FontData
{

public:

    FontData();
    ~FontData();

    static FontData& getInstance()
    {
        static FontData instance;
        return instance;
    }

private:

    FontData(const FontData&) = delete;
    FontData(FontData&&) = delete;
    FontData& operator=(const FontData&) = delete;
    FontData& operator=(FontData&&) = delete;

public:

    typedef struct _Data
    {
        uint32_t Index = 0;
        std::string Name;
        std::string FileName;
    } Data, * Data_ptr;

    using DataList = std::vector<tb::FontData::Data>;

    bool load();
    bool isLoaded();

    tb::FontData::Data* getDataByName(const std::string& name);

    tb::FontData::DataList* getDataList();

private:

    std::string m_fileName = "data/fonts.txt";

    toml::table m_table;

    tb::FontData::DataList m_dataList;

    const unsigned int m_numToLoad = 32;

};

}

namespace
{
    inline tb::FontData& g_FontData = tb::FontData::getInstance();
}
