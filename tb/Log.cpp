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

void Log::vwrite(const FormatString_t& formatString, fmt::format_args args)
{
    const auto& sourceLocation = formatString.sourceLocation;

    m_sourceLocationText = fmt::format("[{}] ", sourceLocation);

    std::stringstream ss;
    ss << m_sourceLocationText;

    fmt::vprint(ss, formatString.logText, args);

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

    m_sourceLocationText.clear();
    m_sourceLocationText.reserve(m_sourceLocationTextReserveSize);

    m_logText.clear();
    m_logText.reserve(m_logTextReserveSize);

    m_file.open(m_fileName, std::ofstream::out | std::ofstream::app);
}

void Log::close()
{
    m_text.clear();
    m_sourceLocationText.clear();
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
