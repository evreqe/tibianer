#pragma once

#include "common.h"

#include "toml.hpp"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

    class PatternData
    {

    public:

        PatternData();
        ~PatternData();
        PatternData(const PatternData&) = delete;
        PatternData(PatternData&&) = delete;
        PatternData& operator=(const PatternData&) = delete;
        PatternData& operator=(PatternData&&) = delete;

        static PatternData& getInstance()
        {
            static PatternData patternData;
            return patternData;
        }

        typedef struct _Pattern
        {
            uint32_t Index = 0;
            std::string Name;
            tb::PatternType PatternType = tb::PatternType::Tile;
            uint8_t Width = 0;
            uint8_t Height = 0;
           tb::SpriteIDList SpriteIDList;
        } Pattern, * Pattern_ptr;

        using PatternList = std::vector<tb::PatternData::Pattern>;

        bool load();
        bool isLoaded();
        bool save();

        tb::PatternData::PatternList* getPatternList();

    private:

        std::string m_fileName = "data/patterns.txt";

        toml::table m_data;

        tb::PatternData::PatternList m_patternList;

        const uint8_t m_numPatternsToLoad = 16;

    };

}

namespace
{
    tb::PatternData& g_PatternData = tb::PatternData::getInstance();
}
