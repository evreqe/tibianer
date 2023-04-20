#include "tb/MessageOfTheDayData.h"

namespace tb
{

MessageOfTheDayData::MessageOfTheDayData()
{
    //
}

MessageOfTheDayData::~MessageOfTheDayData()
{
    //
}

bool MessageOfTheDayData::load()
{
    if (std::filesystem::exists(m_fileName) == false)
    {
        g_Log.write("ERROR: File does not exist: {}\n", m_fileName);
        return false;
    }

    m_file.open(m_fileName);

    if (m_file.is_open() == false)
    {
        g_Log.write("ERROR: Failed to load data from file: {}\n", m_fileName);
        return false;
    }

    g_Log.write("Loaded data from file: {}\n", m_fileName);

    m_dataList.clear();
    m_dataList.reserve(m_numToLoad);

    std::string line;
    while (std::getline(m_file, line))
    {
        if (line.starts_with("#") == true)
        {
            continue;
        }

        m_dataList.push_back(line);
    }

    m_file.close();

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    return true;
}

bool MessageOfTheDayData::isLoaded()
{
    if (m_dataList.size() == 0)
    {
        return false;
    }

    return true;
}

tb::MessageOfTheDayData::DataList* MessageOfTheDayData::getDataList()
{
    return &m_dataList;
}

std::string MessageOfTheDayData::getMessageOfTheDay()
{
    const std::chrono::time_point timePointNow {std::chrono::system_clock::now()};

    const std::chrono::year_month_day yearMonthDay {std::chrono::floor<std::chrono::days>(timePointNow)};

    unsigned int day = static_cast<unsigned int>(yearMonthDay.day());

    size_t numMessages = m_dataList.size();

    if (numMessages == 0)
    {
        return "ERROR: No messages found!";
    }

    uint32_t messageIndex = 0;

    if (day > numMessages)
    {
        messageIndex = tb::Utility::getRandomNumber(0, numMessages - 1);
    }
    else
    {
        messageIndex = day - 1;
    }

    return m_dataList.at(messageIndex);
}

}
