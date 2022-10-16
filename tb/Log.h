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
        if (m_isEnabled == false)
        {
            return;
        }

        vwrite(format, fmt::make_format_args(args...));
    }

    void open();
    void close();
    void deleteContents();

    bool isEnabled();
    void setIsEnabled(bool b);

    std::string getText();

private:

    bool m_isEnabled = true;

    const std::string m_fileName = "log.txt";

    std::ofstream m_file;

    std::string m_text;

};

}

namespace
{
    inline tb::Log& g_Log = tb::Log::getInstance();
}
