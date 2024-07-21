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
    tb::Utility::LibToml::LoadFileResult loadFileResult = tb::Utility::LibToml::loadFile(m_table, m_fileName);

    g_Log.write("{}", loadFileResult.Text);

    if (loadFileResult.Success == false)
    {
        return false;
    }

    m_dataList.clear();
    m_dataList.reserve(m_numToReserve);

    const std::uint32_t numGlyphs = tb::Constants::BitmapFonts::NumGlyphs;

    auto arrayOf = m_table["BitmapFont"].as_array();

    std::uint32_t arrayIndex = 0;

    bool foundError = false;

    arrayOf->for_each
    (
        [this, &numGlyphs, &arrayIndex, &foundError](toml::table& arrayTable)
        {
            tb::BitmapFontData::Data data;
            data.CharacterWidthList.reserve(numGlyphs);

            data.Index = arrayIndex;

            g_Log.write("Index: {}\n", arrayIndex);

            data.Name = arrayTable["Name"].value_or("");

            g_Log.write("Name: {}\n", data.Name);

            if (data.Name.size() == 0)
            {
                g_Log.write("ERROR: 'Name' is empty\n");
                foundError = true;
                return false;
            }

            data.FileName = arrayTable["FileName"].value_or("");

            g_Log.write("FileName: {}\n", data.FileName);

            if (data.FileName.size() == 0)
            {
                g_Log.write("ERROR: 'FileName' is empty\n");
                foundError = true;
                return false;
            }

            data.GlyphWidth = arrayTable["GlyphWidth"].value_or(0);
            data.GlyphHeight = arrayTable["GlyphHeight"].value_or(0);

            g_Log.write("GlyphWidth: {}\n", data.GlyphWidth);
            g_Log.write("GlyphHeight: {}\n", data.GlyphHeight);

            if (data.GlyphWidth == 0 || data.GlyphHeight == 0)
            {
                g_Log.write("ERROR: 'GlyphWidth' or 'GlyphHeight' is zero\n");
                foundError = true;
                return false;
            }

            data.CharacterSpace = arrayTable["CharacterSpace"].value_or(0);

            g_Log.write("CharacterSpace: {}\n", data.CharacterSpace);

            data.CharacterHeight = arrayTable["CharacterHeight"].value_or(1);

            g_Log.write("CharacterHeight: {}\n", data.CharacterHeight);

            if (data.CharacterHeight < 1)
            {
                g_Log.write("ERROR: 'CharacterHeight' is less than 1\n");
                foundError = true;
                return false;
            }

            auto characterWidthListArray = arrayTable["CharacterWidthList"].as_array();

            if (characterWidthListArray == nullptr)
            {
                g_Log.write("ERROR: 'CharacterWidthList' is nullptr\n");
                foundError = true;
                return false;
            }

            for (std::int32_t characterWidthIndex = 0; auto& characterWidthNode : *characterWidthListArray)
            {
                std::int32_t characterWidth = characterWidthNode.value_or(0);

                data.CharacterWidthList.push_back(characterWidth);

                characterWidthIndex++;
            }

            if (data.CharacterWidthList.size() == 0)
            {
                g_Log.write("ERROR: 'CharacterWidthList' is empty\n");
                foundError = true;
                return false;
            }

            if (data.CharacterWidthList.size() != numGlyphs)
            {
                g_Log.write("ERROR: 'CharacterWidthList' has the wrong size, size is {} instead of {}\n", data.CharacterWidthList.size(), numGlyphs);
                foundError = true;
                return false;
            }

            std::string characterWidthListAsString = fmt::format("{}", data.CharacterWidthList);

            g_Log.write("CharacterWidthList: {}\n", characterWidthListAsString);

            m_dataList.push_back(data);

            arrayIndex++;

            return true;
        }
    );

    if (foundError == true)
    {
        g_Log.write("ERROR: Cannot load data because an error was found\n");
        return false;
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
