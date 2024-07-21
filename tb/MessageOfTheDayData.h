#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class MessageOfTheDayData
{

public:

    MessageOfTheDayData();
    ~MessageOfTheDayData();

    static MessageOfTheDayData& getInstance()
    {
        static MessageOfTheDayData instance;
        return instance;
    }

private:

    MessageOfTheDayData(const MessageOfTheDayData&) = delete;
    MessageOfTheDayData(MessageOfTheDayData&&) = delete;
    MessageOfTheDayData& operator=(const MessageOfTheDayData&) = delete;
    MessageOfTheDayData& operator=(MessageOfTheDayData&&) = delete;

public:

    using DataList = std::vector<std::string>;

    bool load();
    bool isLoaded();

    tb::MessageOfTheDayData::DataList* getDataList();

    std::string getMessageOfTheDay();

private:

    const std::string m_fileName = "data/motd.txt";

    std::ifstream m_file;

    tb::MessageOfTheDayData::DataList m_dataList;

    const std::uint32_t m_numToLoad = 365; // num days in a year

};

}

namespace
{
    inline tb::MessageOfTheDayData& g_MessageOfTheDayData = tb::MessageOfTheDayData::getInstance();
}
