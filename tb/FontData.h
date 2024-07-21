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

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::string FileName;
    };

    using DataList = std::vector<tb::FontData::Data>;

    bool load();
    bool isLoaded();

    tb::FontData::Data* getDataByName(const std::string& name);
    tb::FontData::Data* getDataByNameSV(std::string_view name);

    tb::FontData::DataList* getDataList();

private:

    const std::string m_fileName = "data/fonts.txt";

    toml::table m_table;

    tb::FontData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 8;

};

}

namespace
{
    inline tb::FontData& g_FontData = tb::FontData::getInstance();
}
