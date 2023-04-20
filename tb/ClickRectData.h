#pragma once

#include "common.h"

#include "toml.hpp"

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

        typedef struct _Data
        {
            uint32_t Index = 0;
            std::string Name;
            uint32_t X = 0;
            uint32_t Y = 0;
            uint32_t Width = 0;
            uint32_t Height = 0;
        } Data, * Data_ptr;

        using DataList = std::vector<tb::ClickRectData::Data>;

        bool load();
        bool isLoaded();

        tb::ClickRectData::DataList* getDataList();

        tb::ClickRectData::Data* getDataByName(const std::string& name);

    private:

        std::string m_fileName = "data/click_rect.txt";

        toml::table m_table;

        tb::ClickRectData::DataList m_dataList;

        const unsigned int m_numToLoad = 8;

    };

}

namespace
{
    inline tb::ClickRectData& g_ClickRectData = tb::ClickRectData::getInstance();
}
