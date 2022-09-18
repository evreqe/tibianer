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
        m_patternList.reserve(tb::Constants::NumPatterns);

        m_data = toml::parse_file(m_fileName);
        if (m_data.size() == 0)
        {
            g_Log.write("ERROR: Pattern data failed to parse from file: {}\n", m_fileName);
            return false;
        }

        g_Log.write("Pattern data loaded from file: {}\n", m_fileName);

        for (unsigned int i = 0; i < tb::Constants::NumPatterns; i++)
        {
            std::string patternIndex = std::to_string(i);

            if (!m_data[patternIndex])
            {
                continue;
            }

            g_Log.write("Pattern index: {}\n", i);

            tb::PatternData::Pattern pattern;

            pattern.Index = i;

            pattern.Name = m_data[patternIndex]["Name"].value_or("");

            if (pattern.Name.size() == 0)
            {
                g_Log.write("ERROR: pattern.Name.size() == 0\n");
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
                g_Log.write("ERROR: unknown patternType\n");
                return false;
            }

            pattern.Width = m_data[patternIndex]["Width"].value_or(0);
            pattern.Height = m_data[patternIndex]["Height"].value_or(0);

            if (pattern.Width == 0 || pattern.Height == 0)
            {
                g_Log.write("ERROR: pattern.Width == 0 || pattern.Height == 0\n");
                return false;
            }

            auto sprites = m_data[patternIndex]["Sprites"].as_array();

            if (sprites)
            {
                for (auto& sprite : *sprites)
                {
                    uint32_t spriteID = sprite.value_or(0);
                    if (spriteID == 0)
                    {
                        g_Log.write("ERROR: spriteID == 0\n");
                        return false;
                    }

                    g_Log.write("Pattern sprite ID: {}\n", spriteID);

                    pattern.Sprites.push_back(spriteID);
                }
            }

            if (pattern.Sprites.size() == 0)
            {
                g_Log.write("ERROR: pattern.Sprites.size() == 0\n");
                return false;
            }

            m_patternList.push_back(pattern);
        }

        g_Log.write("Pattern data list size: {}\n", m_patternList.size());

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
            g_Log.write("m_patternList.size() == 0\n");
            return false;
        }

        std::fstream file;
        file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

        if (file.is_open() == false)
        {
            g_Log.write("file.is_open() == false\n");
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

            for (auto& spriteID : pattern.Sprites)
            {
                file << spriteID;

                if (spriteIndex != pattern.Sprites.size())
                {
                    file << ", ";
                }

                spriteIndex++;
            }

            file << "]\n";
        }

        file.close();

        g_Log.write("Pattern data saved to file: {}\n", m_fileName);

        return true;
    }

    tb::PatternData::PatternList* PatternData::getPatternList()
    {
        return &m_patternList;
    }

}
