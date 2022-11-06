#pragma once

#include "common.h"

#include "toml.hpp"

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

        typedef struct _Data
        {
            uint32_t Index = 0;
            std::string Name;
            std::string FileName;
            uint32_t Width = 0;
            uint32_t Height = 0;
            bool Repeated = false;
        } Data, *Data_ptr;

        using DataList = std::vector<tb::TextureData::Data>;

        bool load();
        bool isLoaded();

        tb::TextureData::Data* getDataByName(const std::string& name);

        tb::TextureData::DataList* getDataList();

    private:

        std::string m_fileName = "data/textures.txt";

        toml::table m_data;

        tb::TextureData::DataList m_dataList;

        const unsigned int m_numToLoad = 16;

    };

}

namespace
{
    inline tb::TextureData& g_TextureData = tb::TextureData::getInstance();
}
