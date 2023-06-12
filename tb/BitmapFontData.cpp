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

    m_table.clear();

    try
    {
        m_table = toml::parse_file(m_fileName);
    }
    catch (const toml::parse_error& parseError)
    {
        g_Log.write("ERROR: Failed to load data from file: {}\n", m_fileName);
        g_Log.write("Description: {}\nLine: {}\nColumn: {}\n", parseError.description(), parseError.source().begin.line, parseError.source().begin.column);
        return false;
    }

    g_Log.write("Loaded data from file: {}\n", m_fileName);

    m_dataList.clear();
    m_dataList.reserve(m_numToLoad);

    for (unsigned int i = 0; i < m_numToLoad; i++)
    {
        std::string index = std::to_string(i);

        if (!m_table[index])
        {
            break;
        }

        g_Log.write("Index: {}\n", index);

        tb::BitmapFontData::Data data;
        data.CharacterWidthList.reserve(m_numGlyphs);

        data.Index = i;

        data.Name = m_table[index]["Name"].value_or("");

        if (data.Name.size() == 0)
        {
            g_Log.write("ERROR: 'Name' is empty\n");
            return false;
        }

        g_Log.write("Name: {}\n", data.Name);

        data.FileName = m_table[index]["FileName"].value_or("");

        if (data.FileName.size() == 0)
        {
            g_Log.write("ERROR: 'FileName' is empty\n");
            return false;
        }

        g_Log.write("FileName: {}\n", data.FileName);

        data.GlyphWidth = static_cast<uint8_t>(m_table[index]["GlyphWidth"].value_or(0));
        data.GlyphHeight = static_cast<uint8_t>(m_table[index]["GlyphHeight"].value_or(0));

        if (data.GlyphWidth == 0 || data.GlyphHeight == 0)
        {
            g_Log.write("ERROR: 'GlyphWidth' or 'GlyphHeight' is zero\n");
            return false;
        }

        g_Log.write("GlyphWidth: {}\n", data.GlyphWidth);
        g_Log.write("GlyphHeight: {}\n", data.GlyphHeight);

        data.CharacterSpace = m_table[index]["CharacterSpace"].value_or(0);

        g_Log.write("CharacterSpace: {}\n", data.CharacterSpace);

        data.CharacterHeight = m_table[index]["CharacterHeight"].value_or(1);

        if (data.CharacterHeight < 1)
        {
            g_Log.write("ERROR: 'CharacterHeight' is less than 1\n");
            return false;
        }

        g_Log.write("CharacterHeight: {}\n", data.CharacterHeight);

        auto characterWidthListArray = m_table[index]["CharacterWidthList"].as_array();

        if (characterWidthListArray == nullptr)
        {
            g_Log.write("ERROR: characterWidthListArray == nullptr\n");
            return false;
        }

        for (int j = 0; auto& characterWidthNode : *characterWidthListArray)
        {
            int characterWidth = characterWidthNode.value_or(0);

            data.CharacterWidthList.push_back(characterWidth);

            j++;
        }

        if (data.CharacterWidthList.size() == 0)
        {
            g_Log.write("ERROR: 'CharacterWidthList' is empty\n");
            return false;
        }

        if (data.CharacterWidthList.size() != m_numGlyphs)
        {
            g_Log.write("ERROR: 'CharacterWidthList' has the wrong size, {} instead of {}\n", data.CharacterWidthList.size(), m_numGlyphs);
            return false;
        }

        std::string characterWidthListAsString = fmt::format("{}", data.CharacterWidthList);

        g_Log.write("CharacterWidthList: {}\n", characterWidthListAsString);

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
    if (m_table.size() == 0) return false;
    if (m_dataList.size() == 0) return false;

    return true;
}

tb::BitmapFontData::DataList* BitmapFontData::getDataList()
{
    return &m_dataList;
}

}
