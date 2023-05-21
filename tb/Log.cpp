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

    std::string_view functionName = loc.function_name();

    std::size_t beginPosition;
    if ((beginPosition = functionName.find("tb::")) != std::string::npos)
    {
        std::size_t endPosition;
        if ((endPosition = functionName.find("(", beginPosition)) != std::string::npos && endPosition != beginPosition)
        {
            endPosition = endPosition + 1;

            functionName = functionName.substr(beginPosition, endPosition - beginPosition);
        }
    }

    m_sourceText = fmt::format(FMT_COMPILE("[{}:{}:{}()] "), fileName, loc.line(), functionName);

    std::stringstream ss;
    ss << m_sourceText;
    fmt::vprint(ss, format.str, args);

    m_logText = ss.str();

    // append to internal string
    m_text.append(m_logText);

    // print to console
    if (m_properties.PrintToConsole == true)
    {
        std::cout << m_logText;
    }

    // write to file
    if (m_properties.WriteToFile == true)
    {
        m_file << m_logText;
    }
}

Log::Properties_t* Log::getProperties()
{
    return &m_properties;
}

void Log::open()
{
    m_text.clear();
    m_text.reserve(m_textReserveSize);

    m_sourceText.clear();
    m_sourceText.reserve(m_sourceTextReserveSize);

    m_logText.clear();
    m_logText.reserve(m_logTextReserveSize);

    m_file.open(m_fileName, std::ofstream::out | std::ofstream::app);
}

void Log::close()
{
    m_text.clear();
    m_sourceText.clear();
    m_logText.clear();

    m_file.flush();
    m_file.close();
}

void Log::deleteFileContents()
{
    m_file.open(m_fileName, std::ofstream::out | std::ofstream::trunc);
    m_file.close();
}

bool Log::isEnabled()
{
    return m_properties.IsEnabled;
}

void Log::setIsEnabled(bool b)
{
    m_properties.IsEnabled = b;
}

std::string Log::getText()
{
    return m_text;
}

}
