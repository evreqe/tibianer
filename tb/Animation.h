#pragma once

#include "common.h"

#include "tb/Constants.h"
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
    Animation(const sf::Vector2i& tileCoords, tb::ZAxis_t z, uint32_t index);
    Animation(const sf::Vector2i& tileCoords, tb::ZAxis_t z, const std::string& name);

    using Ptr = std::shared_ptr<tb::Animation>;
    using List = std::vector<tb::Animation::Ptr>;

    void initalize();

    void update();

    void advanceFrame();

    tb::Sprite* getSprite();

    tb::AnimationData::Data* getData();

    tb::SpriteIDList* getSpriteIDList();

    sf::Clock* getClock();

private:

    tb::Sprite m_sprite;

    tb::AnimationData::Data* m_animationData = nullptr;

    tb::SpriteIDList* m_spriteIDList = nullptr;

    sf::Clock m_clock;

    uint32_t m_currentFrame = 0;

    sf::Time m_frameTime = sf::seconds(0.1f);

    uint32_t m_numRepeat = 0;

};

}
