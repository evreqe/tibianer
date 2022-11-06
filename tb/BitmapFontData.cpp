#include "tb/BitmapFontData.h"

namespace tb
{

BitmapFontData::BitmapFontData()
{
    //
}

BitmapFontData::~BitmapFontData()
{
    //
}

bool BitmapFontData::load()
{
    if (std::filesystem::exists(m_fileName) == false)
    {
        g_Log.write("ERROR: File does not exist: {}\n", m_fileName);
        return false;
    }

    m_data.clear();
    m_data = toml::parse_file(m_fileName);
    if (m_data.size() == 0)
    {
        g_Log.write("ERROR: Failed to load data from file: {}\n", m_fileName);
        return false;
    }

    g_Log.write("Loaded data from file: {}\n", m_fileName);

    m_dataList.clear();
    m_dataList.reserve(m_numToLoad);

    for (unsigned int i = 0; i < m_numToLoad; i++)
    {
        std::string index = std::to_string(i);

        if (!m_data[index])
        {
            break;
        }

        g_Log.write("Index: {}\n", index);

        tb::BitmapFontData::Data data;
        data.GlyphWidthList.reserve(m_numGlyphs);

        data.Index = i;

        data.Name = m_data[index]["Name"].value_or("");

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        g_Log.write("Name: {}\n", data.Name);

        data.FileName = m_data[index]["FileName"].value_or("");

        if (data.FileName.size() == 0)
        {
            g_Log.write("ERROR: 'FileName' is empty\n");
            return false;
        }

        g_Log.write("FileName: {}\n", data.FileName);

        data.GlyphWidth = static_cast<uint8_t>(m_data[index]["GlyphWidth"].value_or(0));
        data.GlyphHeight = static_cast<uint8_t>(m_data[index]["GlyphHeight"].value_or(0));

        if (data.GlyphWidth == 0 || data.GlyphHeight == 0)
        {
            g_Log.write("ERROR: 'GlyphWidth' or 'GlyphHeight' is zero\n");
            return false;
        }

        g_Log.write("GlyphWidth: {}\n", data.GlyphWidth);
        g_Log.write("GlyphHeight: {}\n", data.GlyphHeight);

        data.TextHeight = m_data[index]["TextHeight"].value_or(0.0f);

        if (data.TextHeight < 1.0f)
        {
            g_Log.write("ERROR: 'TextHeight' is less than 1.0\n");
            return false;
        }

        g_Log.write("TextHeight: {}\n", data.TextHeight);

        auto glyphWidthListArray = m_data[index]["GlyphWidthList"].as_array();

        if (glyphWidthListArray == nullptr)
        {
            g_Log.write("ERROR: glyphWidthListArray == nullptr\n");
            return false;
        }

        for (unsigned int j = 0; auto& glyphWidthNode : *glyphWidthListArray)
        {
            uint32_t glyphWidth = glyphWidthNode.value_or(0);
            if (glyphWidth == 0)
            {
                g_Log.write("ERROR: Glypth width is zero at index: [{}] GlyphWidthList=[#{}]\n", i, j);
                return false;
            }

            data.GlyphWidthList.push_back(glyphWidth);

            j++;
        }

        if (data.GlyphWidthList.size() == 0)
        {
            g_Log.write("ERROR: 'GlyphWidthList' is empty\n");
            return false;
        }

        if (data.GlyphWidthList.size() != m_numGlyphs)
        {
            g_Log.write("ERROR: 'GlyphWidthList' has the wrong size, {} instead of {}\n", data.GlyphWidthList.size(), m_numGlyphs);
            return false;
        }

        std::string glypthWidthListStr = fmt::format("{}", data.GlyphWidthList);

        g_Log.write("GlyphWidthList: {}\n", glypthWidthListStr);

        m_dataList.push_back(data);
    }

    g_Log.write("Loaded data size: {}\n", m_dataList.size());

    if (m_dataList.size() == 0)
    {
        g_Log.write("ERROR: Loaded data is empty\n");
        return false;
    }

    return true;
}

bool BitmapFontData::isLoaded()
{
    if (m_data.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::BitmapFontData::DataList* BitmapFontData::getDataList()
{
    return &m_dataList;
}

}
