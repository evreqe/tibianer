#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class TextureData
{

public:

    TextureData();
    ~TextureData();

    static TextureData& getInstance()
    {
        static TextureData instance;
        return instance;
    }

private:

    TextureData(const TextureData&) = delete;
    TextureData(TextureData&&) = delete;
    TextureData& operator=(const TextureData&) = delete;
    TextureData& operator=(TextureData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        std::string FileName;
        std::uint32_t Width = 0;
        std::uint32_t Height = 0;
        bool Repeated = false;
    };

    using DataList = std::vector<tb::TextureData::Data>;

    bool load();
    bool isLoaded();

    tb::TextureData::Data* getDataByName(const std::string& name);

    tb::TextureData::DataList* getDataList();

private:

    const std::string m_fileName = "data/textures.txt";

    toml::table m_table;

    tb::TextureData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 32;

};

}

namespace
{
    inline tb::TextureData& g_TextureData = tb::TextureData::getInstance();
}
