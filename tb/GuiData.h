#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class GuiData
{

public:

    GuiData();
    ~GuiData();

    static GuiData& getInstance()
    {
        static GuiData instance;
        return instance;
    }

private:

    GuiData(const GuiData&) = delete;
    GuiData(GuiData&&) = delete;
    GuiData& operator=(const GuiData&) = delete;
    GuiData& operator=(GuiData&&) = delete;

public:

    typedef struct _Data
    {
        uint32_t Index = 0;
        std::string Name;
        uint32_t X = 0;
        uint32_t Y = 0;
        uint32_t Width = 0;
        uint32_t Height = 0;
    } Data, * Data_ptr;

    using DataList = std::vector<tb::GuiData::Data>;

    bool load();
    bool isLoaded();

    tb::GuiData::Data* getDataByName(const std::string& name);

    tb::GuiData::DataList* getDataList();

private:

    std::string m_fileName = "data/gui.txt";

    toml::table m_table;

    tb::GuiData::DataList m_dataList;

    const unsigned int m_numToLoad = 64;

};

}

namespace
{
    inline tb::GuiData& g_GuiData = tb::GuiData::getInstance();
}
