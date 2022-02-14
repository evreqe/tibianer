#pragma once

#include <format>
#include <fstream>
#include <string>
#include <vector>

#include "toml.hpp"

#include "tb/Utility.h"
#include "tb/Constants.h"

namespace tb
{

class SpriteData
{

public:

    typedef struct _Data
    {
        tb::SpriteID_t SpriteID = 0;
        tb::SpriteFlags_t SpriteFlags;
        std::string Article; // 'a' or 'an'
        std::string Name;
        float Weight = 0.0f; // cap
        uint8_t TileWidth = 1;
        uint8_t TileHeight = 1;

    } Data, *Data_ptr;

    typedef std::vector<tb::SpriteData::Data> DataList;

    SpriteData();

    bool load();
    bool save();

    tb::SpriteData::DataList* getDataList();

private:

    std::string m_fileName = "data/sprites.txt";

    toml::table m_data;

    tb::SpriteData::DataList m_dataList;

};

}
