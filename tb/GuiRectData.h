#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class GuiRectData
{

public:

    GuiRectData();
    ~GuiRectData();

    static GuiRectData& getInstance()
    {
        static GuiRectData instance;
        return instance;
    }

private:

    GuiRectData(const GuiRectData&) = delete;
    GuiRectData(GuiRectData&&) = delete;
    GuiRectData& operator=(const GuiRectData&) = delete;
    GuiRectData& operator=(GuiRectData&&) = delete;

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

    using DataList = std::vector<tb::GuiRectData::Data>;

    bool load();
    bool isLoaded();

    tb::GuiRectData::Data* getDataByIndex(std::uint32_t index);
    tb::GuiRectData::Data* getDataByName(const std::string& name);
    tb::GuiRectData::Data* getDataByNameSV(std::string_view name);

    tb::GuiRectData::DataList* getDataList();

private:

    const std::string m_fileName = "data/gui_rect.txt";

    toml::table m_table;

    tb::GuiRectData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 64;

};

}

namespace
{
    inline tb::GuiRectData& g_GuiRectData = tb::GuiRectData::getInstance();
}

