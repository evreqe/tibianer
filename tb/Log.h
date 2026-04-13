#pragma once

#include "common.h"

#include "tb/Log.h"

namespace tb
{

class Log
{

public:

    Log();
    ~Log();

    static Log& getInstance()
    {
        static Log instance;
        return instance;
    }

private:

    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

public:

    struct Properties
    {
        bool IsEnabled = true;

        bool PrintToConsole = true;
        bool WriteToFile = true;
    };

    struct FormatString
    {
        fmt::string_view logText;
        std::source_location sourceLocation;

        FormatString
        (
            const char* logText,
            const std::source_location& sourceLocation = std::source_location::current()
        ) : logText(logText), sourceLocation(sourceLocation) {}
    };

    void vwrite(const FormatString& formatString, fmt::format_args args);

    template <typename... Args>
    void write(const FormatString& formatString, Args&&... args)
    {
        if (m_properties.IsEnabled == false)
        {
            return;
        }

        vwrite(formatString, fmt::make_format_args(args...));
    }

    Properties* getProperties();

    void open();
    void close();
    void deleteFileContents();

    bool isEnabled();
    void setEnabled(bool b);

    std::string getText();

private:

    Properties m_properties;

    const std::string m_fileName = "log.txt";

    std::ofstream m_file;

    std::string m_text;
    std::size_t m_textReserveSize = 4096 * 1000;

    std::string m_sourceLocationText;
    std::size_t m_sourceLocationTextReserveSize = 128;

    std::string m_logText;
    std::size_t m_logTextReserveSize = 256;

};

}

namespace
{
    inline tb::Log& g_Log = tb::Log::getInstance();
}
