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

            tb::PatternData::Data data;

            data.Index = i;

            data.Name = m_data[index]["Name"].value_or("");

            if (data.Name.size() == 0)
            {
                g_Log.write("ERROR: 'Name' is empty\n");
                return false;
            }

            std::string_view patternType = m_data[index]["Type"].value_or("");

            auto patternTypeEx = magic_enum::enum_cast<tb::PatternType>(patternType);
            if (patternTypeEx.has_value())
            {
                data.PatternType = patternTypeEx.value();
            }
            else
            {
                g_Log.write("ERROR: 'Type' is unknown\n");
                return false;
            }

            data.Width = static_cast<uint8_t>(m_data[index]["Width"].value_or(0));
            data.Height = static_cast<uint8_t>(m_data[index]["Height"].value_or(0));

            if (data.Width == 0 || data.Height == 0)
            {
                g_Log.write("ERROR: 'Width' or 'Height' is zero\n");
                return false;
            }

            auto sprites = m_data[index]["Sprites"].as_array();

            if (sprites == nullptr)
            {
                g_Log.write("ERROR: nullptr\n");
                return false;
            }

            for (unsigned int j = 0; auto& sprite : *sprites)
            {
                tb::SpriteID_t spriteID = static_cast<tb::SpriteID_t>(sprite.value_or(0));
                if (spriteID == 0)
                {
                    g_Log.write("ERROR: Sprite ID is zero at index: [{}] Sprites=[#{}]\n", i, j);
                    return false;
                }

                g_Log.write("Sprite ID: {}\n", spriteID);

                data.SpriteIDList.push_back(spriteID);

                j++;
            }

            if (data.SpriteIDList.size() == 0)
            {
                g_Log.write("ERROR: 'Sprites' is empty\n");
                return false;
            }

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

    bool PatternData::isLoaded()
    {
        if (m_data.size() == 0) return false;
        if (m_dataList.size() == 0) return false;

        return true;
    }

    bool PatternData::save()
    {
        if (m_dataList.size() == 0)
        {
            g_Log.write("ERROR: Cannot save data because it is empty\n");
            return false;
        }

        std::fstream file;
        file.open(m_fileName.c_str(), std::ios::out | std::ios::trunc);

        if (file.is_open() == false)
        {
            g_Log.write("ERROR: Cannot open file: {}\n", m_fileName);
            return false;
        }

        for (auto& data : m_dataList)
        {
            file << std::format("[{}]\n", data.Index);

            file << std::format("Name=\"{}\"\n", data.Name);

            std::string_view patternTypeString = magic_enum::enum_name(data.PatternType);
            if (patternTypeString.size() == 0)
            {
                g_Log.write("ERROR: 'PatternType' is empty\n");
                return false;
            }

            file << std::format("Type=\"{}\"\n", patternTypeString);

            file << std::format("Width={}\n", data.Width);
            file << std::format("Height={}\n", data.Height);

            file << "Sprites=[";

            uint32_t spriteIndex = 0;

            for (auto& spriteID : data.SpriteIDList)
            {
                file << spriteID;

                if (spriteIndex != data.SpriteIDList.size())
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

    tb::PatternData::DataList* PatternData::getDataList()
    {
        return &m_dataList;
    }

}
