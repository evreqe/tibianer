#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class ClickRectData
{

public:

    ClickRectData();
    ~ClickRectData();

    static ClickRectData& getInstance()
    {
        static ClickRectData instance;
        return instance;
    }

private:

    ClickRectData(const ClickRectData&) = delete;
    ClickRectData(ClickRectData&&) = delete;
    ClickRectData& operator=(const ClickRectData&) = delete;
    ClickRectData& operator=(ClickRectData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::uint32_t X = 0;
        std::uint32_t Y = 0;
        std::uint32_t Width = 0;
        std::uint32_t Height = 0;
    };

    using DataList = std::vector<tb::ClickRectData::Data>;

    bool load();
    bool isLoaded();

    tb::ClickRectData::DataList* getDataList();

    tb::ClickRectData::Data* getDataByName(const std::string& name);
    tb::ClickRectData::Data* getDataByNameSV(std::string_view name);

private:

    const std::string m_fileName = "data/click_rect.txt";

    toml::table m_table;

    tb::ClickRectData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 8;

};

}

namespace
{
    inline tb::ClickRectData& g_ClickRectData = tb::ClickRectData::getInstance();
}
