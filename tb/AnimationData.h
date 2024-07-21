#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class AnimationData
{

public:

    AnimationData();
    ~AnimationData();

    static AnimationData& getInstance()
    {
        static AnimationData instance;
        return instance;
    }

private:

    AnimationData(const AnimationData&) = delete;
    AnimationData(AnimationData&&) = delete;
    AnimationData& operator=(const AnimationData&) = delete;
    AnimationData& operator=(AnimationData&&) = delete;

public:

    struct Data
    {
        std::uint32_t Index = 0;
        std::string Name;
        tb::SpriteIDList SpriteIDList;
    };

    using DataList = std::vector<tb::AnimationData::Data>;

    bool load();
    bool isLoaded();

    tb::AnimationData::DataList* getDataList();

    tb::AnimationData::Data* getDataByIndex(std::uint32_t index);
    tb::AnimationData::Data* getDataByName(const std::string& name);
    tb::AnimationData::Data* getDataByNameSV(std::string_view name);

private:

    const std::string m_fileName = "data/animations.txt";

    toml::table m_table;

    tb::AnimationData::DataList m_dataList;

    const std::uint32_t m_numToReserve = 64;

    const std::uint32_t m_numSpritesPerAnimationToReserve = 16;

};

}

namespace
{
    inline tb::AnimationData& g_AnimationData = tb::AnimationData::getInstance();
}
