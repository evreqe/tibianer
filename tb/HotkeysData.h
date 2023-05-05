#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class HotkeysData
{

public:

    HotkeysData();
    ~HotkeysData();

    static HotkeysData& getInstance()
    {
        static HotkeysData instance;
        return instance;
    }

private:

    HotkeysData(const HotkeysData&) = delete;
    HotkeysData(HotkeysData&&) = delete;
    HotkeysData& operator=(const HotkeysData&) = delete;
    HotkeysData& operator=(HotkeysData&&) = delete;

public:

    typedef struct _Data
    {
        std::string F1;
        std::string F2;
        std::string F3;
        std::string F4;
        std::string F5;
        std::string F6;
        std::string F7;
        std::string F8;
        std::string F9;
        std::string F10;
        std::string F11;
        std::string F12;
    } Data, * Data_ptr;

    bool load();
    bool isLoaded();

    bool save();

    tb::HotkeysData::Data* getData();
    void setData(const tb::HotkeysData::Data& data);

private:

    std::string m_fileName = "config/hotkeys.txt";

    toml::table m_table;

    tb::HotkeysData::Data m_data;

};

}

namespace
{
    inline tb::HotkeysData& g_HotkeysData = tb::HotkeysData::getInstance();
}
