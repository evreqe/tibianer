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
    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

    static Log& getInstance()
    {
        static Log log;
        return log;
    }

    typedef struct _FormatString
    {
        fmt::string_view str;
        std::source_location loc;

        _FormatString
        (
            const char* str,
            const std::source_location& loc = std::source_location::current()
        ) : str(str), loc(loc) {}
    } FormatString, * FormatString_ptr;

    void vwrite(const FormatString& format, fmt::format_args args);

    template <typename... Args>
    void write(const FormatString& format, Args&&... args)
    {
        vwrite(format, fmt::make_format_args(args...));
    }

    void open();
    void close();
    void deleteContents();

    std::string getText();

private:

    const std::string m_fileName = "log.txt";

    std::ofstream m_file;

    std::string m_text;

};

}

namespace
{
    tb::Log& g_Log = tb::Log::getInstance();
}
