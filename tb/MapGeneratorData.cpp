#include "tb/MapGeneratorData.h"

namespace tb
{

MapGeneratorData::MapGeneratorData()
{
    //
}

MapGeneratorData::~MapGeneratorData()
{
    //
}

bool MapGeneratorData::load()
{
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_data.TemplateFileName = m_table["MapGenerator"]["TemplateFileName"].value_or("");

    g_Log.write("TemplateFileName: {}\n", m_data.TemplateFileName);

    if (m_data.TemplateFileName.empty() == true)
    {
        g_Log.write("ERROR: TemplateFileName is empty\n");
        return false;
    }

    return true;
}

bool MapGeneratorData::isLoaded()
{
    if (m_table.size() == 0)
    {
        return false;
    }

    return true;
}

tb::MapGeneratorData::Data* MapGeneratorData::getData()
{
    return &m_data;
}

}
