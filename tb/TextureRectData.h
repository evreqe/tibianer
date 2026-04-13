#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class TextureRectData
{

public:

    TextureRectData();
    ~TextureRectData();

    static TextureRectData& getInstance()
    {
        static TextureRectData instance;
        return instance;
    }

private:

    TextureRectData(const TextureRectData&) = delete;
    TextureRectData(TextureRectData&&) = delete;
    TextureRectData& operator=(const TextureRectData&) = delete;
    TextureRectData& operator=(TextureRectData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string TextureName;
        std::string Name;
        std::uint32_t X = 0;
        std::uint32_t Y = 0;
        std::uint32_t Width = 0;
        std::uint32_t Height = 0;
    };

    using DataList = std::vector<tb::TextureRectData::Data>;

    bool load();
    bool isLoaded();

    tb::TextureRectData::Data* getDataByIndex(std::uint32_t index);
    tb::TextureRectData::Data* getDataByName(const std::string& name);
    tb::TextureRectData::Data* getDataByNameSV(std::string_view name);

    tb::TextureRectData::DataList* getDataList();

private:

    const std::string m_fileName = "data/texture_rects.txt";

    toml::table m_table;

    tb::TextureRectData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 64;

};

}

namespace
{
    inline tb::TextureRectData& g_TextureRectData = tb::TextureRectData::getInstance();
}

