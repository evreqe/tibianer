#include "tb/Log.h"

namespace tb
{

Log::Log()
{
    //
}

Log::~Log()
{
    //
}

void Log::vwrite(const FormatString& format, fmt::format_args args)
{
    const auto& loc = format.loc;

    std::string_view fileName = loc.file_name();

    // trim the path down to just the file name and extension
    if (fileName.contains("\\") == true)
    {
        fileName = fileName.substr(fileName.rfind("\\") + 1);
    }

    std::string sourceText = fmt::format("[{}:{}:{}()] ", fileName, loc.line(), loc.function_name());

    fmt::print("{}", sourceText);
    fmt::vprint(format.str, args);

    m_file << sourceText;
    fmt::vprint(m_file, format.str, args);

    std::stringstream ss;
    ss << sourceText;
    fmt::vprint(ss, format.str, args);
    m_text.append(ss.str());
}

void Log::open()
{
    m_text.clear();
    m_file.open(m_fileName, std::ofstream::out | std::ofstream::app);
}

void Log::close()
{
    m_text.clear();
    m_file.close();
}

void Log::deleteContents()
{
    m_text.clear();
    m_file.open(m_fileName, std::ofstream::out | std::ofstream::trunc);
    m_file.close();
}

std::string Log::getText()
{
    return m_text;
}

}
