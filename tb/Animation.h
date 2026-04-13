#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Resources.h"
#include "tb/Utility.h"

#include "tb/SpriteData.h"
#include "tb/AnimationData.h"

#include "tb/Thing.h"
#include "tb/Sprite.h"

namespace tb
{

class Animation : public tb::Thing
{

public:

    Animation();
    ~Animation();
    Animation(const tb::TileCoords& tileCoords, tb::AxisZ axisZ, std::uint32_t index);
    Animation(const tb::TileCoords& tileCoords, tb::AxisZ axisZ, const std::string& name);

    using Ptr = std::shared_ptr<tb::Animation>;
    using List = std::vector<tb::Animation::Ptr>;

    void initalize();
    void update();
    void advanceFrame();

    tb::Sprite* getSprite();
    tb::SpriteID getSpriteID();
    tb::SpriteIDList* getSpriteIDList();
    tb::AnimationData::Data* getData();
    sf::Clock* getClock();

private:

    tb::Sprite m_sprite;
    tb::SpriteIDList* m_spriteIDList = nullptr;
    tb::AnimationData::Data* m_animationData = nullptr;
    sf::Clock m_clock;
    std::uint32_t m_currentFrame = 0;
    sf::Time m_frameTime = sf::seconds(0.1f);
    std::uint32_t m_numRepeat = 0;

};

}
