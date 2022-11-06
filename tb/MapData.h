#pragma once

#include "common.h"

#include "pugixml.hpp"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

    class MapData
    {

    public:

        MapData();
        ~MapData();

        static MapData& getInstance()
        {
            static MapData instance;
            return instance;
        }

    private:

        MapData(const MapData&) = delete;
        MapData(MapData&&) = delete;
        MapData& operator=(const MapData&) = delete;
        MapData& operator=(MapData&&) = delete;

    public:

        typedef struct _Data
        {
            std::string FileName;
            std::string Name;
            std::string Description;
            std::string Author;
            uint32_t TileWidth = 0;
            uint32_t TileHeight = 0;
        } Data, * Data_ptr;

        using DataList = std::vector<tb::MapData::Data>;

        bool load();
        bool isLoaded();

        tb::MapData::Data* getDataByFileName(const std::string& fileName);
        tb::MapData::Data* getDataByName(const std::string& name);

        tb::MapData::DataList* getDataList();

    private:

        tb::MapData::DataList m_dataList;

        const std::string m_mapFileNameExtension = ".tmx";

    };

}

namespace
{
    inline tb::MapData& g_MapData = tb::MapData::getInstance();
}
