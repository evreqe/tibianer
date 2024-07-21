#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class CursorData
{

public:

    CursorData();
    ~CursorData();

    static CursorData& getInstance()
    {
        static CursorData instance;
        return instance;
    }

private:

    CursorData(const CursorData&) = delete;
    CursorData(CursorData&&) = delete;
    CursorData& operator=(const CursorData&) = delete;
    CursorData& operator=(CursorData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::string FileName;
        sf::Image Image;
        std::uint32_t Width = 0;
        std::uint32_t Height = 0;
        std::uint32_t HotSpotX = 0;
        std::uint32_t HotSpotY = 0;
    };

    using DataList = std::vector<tb::CursorData::Data>;

    bool load();
    bool isLoaded();

    tb::CursorData::Data* getDataByName(const std::string& name);
    tb::CursorData::Data* getDataByNameSV(std::string_view name);

    tb::CursorData::DataList* getDataList();

private:

    const std::string m_fileName = "data/cursors.txt";

    toml::table m_table;

    tb::CursorData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 8;

};

}

namespace
{
    inline tb::CursorData& g_CursorData = tb::CursorData::getInstance();
}
