#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"

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

    struct Properties_t
    {
        bool IsEnabled = true;

        bool PrintToConsole = true;
        bool WriteToFile = true;
    };

    typedef struct _FormatString
    {
        fmt::string_view str;
        std::source_location loc;

        _FormatString
        (
            const char* str,
            const std::source_location& loc = std::source_location::current()
        ) : str(str), loc(loc) {}
    } FormatString, *FormatString_ptr;

    void vwrite(const FormatString& format, fmt::format_args args);

    template <typename... Args>
    void write(const FormatString& format, Args&&... args)
    {
        if (m_properties.IsEnabled == false)
        {
            return;
        }

        vwrite(format, fmt::make_format_args(args...));

        ////auto fireAndForget = std::async(std::launch::async, &Log::vwrite, this, format, fmt::make_format_args(args...));
    }

    Properties_t* getProperties();

    void open();
    void close();
    void deleteFileContents();

    bool isEnabled();
    void setIsEnabled(bool b);

    std::string getText();

private:

    Properties_t m_properties;

    const std::string m_fileName = "log.txt";

    std::ofstream m_file;

    std::string m_text;
    std::size_t m_textReserveSize = 4096 * 1000;

    std::string m_sourceText;
    std::size_t m_sourceTextReserveSize = 128;

    std::string m_logText;
    std::size_t m_logTextReserveSize = 256;

};

}

namespace
{
    inline tb::Log& g_Log = tb::Log::getInstance();
}
