#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/MapGeneratorData.h"
#include "tb/MapGeneratorPixelData.h"

namespace tb
{

class MapGenerator
{

public:

    MapGenerator();
    ~MapGenerator();

    static MapGenerator& getInstance()
    {
        static MapGenerator instance;
        return instance;
    }

private:

    MapGenerator(const MapGenerator&) = delete;
    MapGenerator(MapGenerator&&) = delete;
    MapGenerator& operator=(const MapGenerator&) = delete;
    MapGenerator& operator=(MapGenerator&&) = delete;

public:

    struct Map_t
    {
        std::string Name;
        std::string Author;
        std::string Description;
        std::uint32_t PlayerStartX = 0;
        std::uint32_t PlayerStartY = 0;
        std::uint32_t PlayerStartZ = tb::ZAxis::Default;
    };

    template<typename... Args>
    std::string dynamicFormat(std::string_view fmt, Args&&... args)
    {
        return std::vformat(fmt, std::make_format_args(args...));
    }

    std::string getTemplateFileText();
    bool generateMapFromImageFile(const MapGenerator::Map_t& map, const std::string& imageFileName, const std::string& outputFileName);

private:

    const std::uint32_t m_numCornerSpritesRequired = 4;
    const std::uint32_t m_numEdgeSpritesRequired = 9;

};

}

namespace
{
    inline tb::MapGenerator& g_MapGenerator = tb::MapGenerator::getInstance();
}
