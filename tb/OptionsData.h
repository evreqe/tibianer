#pragma once

#include "common.h"

#include "toml.hpp"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

    class OptionsData
    {

    public:

        OptionsData();
        ~OptionsData();

        static OptionsData& getInstance()
        {
            static OptionsData instance;
            return instance;
        }

    private:

        OptionsData(const OptionsData&) = delete;
        OptionsData(OptionsData&&) = delete;
        OptionsData& operator=(const OptionsData&) = delete;
        OptionsData& operator=(OptionsData&&) = delete;

    public:

        typedef struct _Data
        {
            std::string PlayerName;
        } Data, * Data_ptr;

        bool load();
        bool isLoaded();

        bool save();

        tb::OptionsData::Data* getData();

    private:

        std::string m_fileName = "config/options.txt";

        toml::table m_table;

        tb::OptionsData::Data m_data;

    };

}

namespace
{
    inline tb::OptionsData& g_OptionsData = tb::OptionsData::getInstance();
}
