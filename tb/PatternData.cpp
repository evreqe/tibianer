#include "tb/PatternData.h"

namespace tb
{

    PatternData::PatternData()
    {
        //
    }

    PatternData::~PatternData()
    {
        //
    }

    bool PatternData::load()
    {
        m_patternList.clear();
        m_patternList.reserve(32);

        m_data = toml::parse_file(m_fileName);
        if (m_data.size() == 0)
        {
            g_Log.write("ERROR: Failed to parse data from file: {}\n", m_fileName);
            return false;
        }

        g_Log.write("Loaded data from file: {}\n", m_fileName);

        for (unsigned int i = 0; i < m_numPatternsToLoad; i++)
        {
            std::string patternIndex = std::to_string(i);

            if (!m_data[patternIndex])
            {
                break;
            }

            g_Log.write("Index: {}\n", i);

            tb::PatternData::Pattern pattern;

            pattern.Index = i;

            pattern.Name = m_data[patternIndex]["Name"].value_or("");

            if (pattern.Name.size() == 0)
            {
                g_Log.write("ERROR: Name cannot be empty\n");
                return false;
            }

            std::string_view patternType = m_data[patternIndex]["Type"].value_or("");

            if (patternType == "tile")
            {
                pattern.PatternType = tb::PatternType::Tile;
            }
            else if (patternType == "object")
            {
                pattern.PatternType = tb::PatternType::Object;
            }
            else
            {
                g_Log.write("ERROR: PatternType is unknown\n");
                return false;
            }

            pattern.Width = m_data[patternIndex]["Width"].value_or(0);
            pattern.Height = m_data[patternIndex]["Height"].value_or(0);

            if (pattern.Width == 0 || pattern.Height == 0)
            {
                g_Log.write("ERROR: Width or Height cannot be zero\n");
                return false;
            }

            auto sprites = m_data[patternIndex]["Sprites"].as_array();

            if (sprites == nullptr)
            {
                g_Log.write("ERROR: nullptr\n");
                return false;
            }

            for (auto& sprite : *sprites)
            {
                uint32_t spriteID = sprite.value_or(0);
                if (spriteID == 0)
                {
                    g_Log.write("ERROR: Sprite ID cannot be zero at index: {}\n", i);
                    return false;
                }

                g_Log.write("Sprite ID: {}\n", spriteID);

                pattern.SpriteIDList.push_back(spriteID);
            }

            if (pattern.SpriteIDList.size() == 0)
            {
                g_Log.write("ERROR: Sprite ID list cannot be empty\n");
                return false;
            }

            m_patternList.push_back(pattern);
        }

        g_Log.write("Loaded data size: {}\n", m_patternList.size());

        if (m_patternList.size() == 0)
        {
            g_Log.write("ERROR: Loaded data has the wrong size\n");
            return false;
        }

        return true;
    }

    bool PatternData::isLoaded()
    {
        if (m_data.size() == 0) return false;
        if (m_patternList.size() == 0) return false;

        return true;
    }

    bool PatternData::save()
    {
        if (m_patternList.size() == 0)
        {
            g_Log.write("ERROR: Cannot save data because it is empty\n");
            return false;
        }

        std::fstream file;
        file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

        if (file.is_open() == false)
        {
            g_Log.write("Cannot open file: {}\n", m_fileName);
            return false;
        }

        for (auto& pattern : m_patternList)
        {
            file << std::format("[{}]\n", pattern.Index);

            file << std::format("Name=\"{}\"\n", pattern.Name);

            file << std::format("Width={}\n", pattern.Width);
            file << std::format("Height={}\n", pattern.Height);

            file << "Sprites=[";

            uint32_t spriteIndex = 0;

            for (auto& spriteID : pattern.SpriteIDList)
            {
                file << spriteID;

                if (spriteIndex != pattern.SpriteIDList.size())
                {
                    file << ",";
                }

                spriteIndex++;
            }

            file << "]\n";
        }

        file.close();

        g_Log.write("Saved data to file: {}\n", m_fileName);

        return true;
    }

    tb::PatternData::PatternList* PatternData::getPatternList()
    {
        return &m_patternList;
    }

}
