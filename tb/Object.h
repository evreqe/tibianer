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

class Object : public tb::Thing
{

public:

    Object();
    ~Object();
    Object(const sf::Vector2i& tileCoords, tb::ZAxis_t z, tb::SpriteID_t spriteID);

    using Ptr = std::shared_ptr<tb::Object>;
    using List = std::vector<tb::Object::Ptr>;

    struct SortBySpriteID_t
    {
        bool operator()(tb::Object::Ptr a, tb::Object::Ptr b) const
        {
            return a->getSpriteID() < b->getSpriteID();
        }
    };

    struct SortByCount_t
    {
        bool operator()(tb::Object::Ptr a, tb::Object::Ptr b) const
        {
            return a->getCount() > b->getCount();
        }
    };

    struct ObjectProperties_t
    {
        bool Decay = false;
        bool Regenerate = false;
    };

    ObjectProperties_t* getObjectProperties();

    void update();

    void animate();

    tb::Sprite* getSprite();

    tb::SpriteID_t getSpriteID();
    void setSpriteID(tb::SpriteID_t spriteID);

    tb::ObjectType getObjectType();
    void setObjectType(tb::ObjectType objectType);

    void setCount(uint32_t count);
    uint32_t getCount();

    sf::Clock* getDecayClock();
    sf::Clock* getRegenerateClock();

private:

    ObjectProperties_t m_objectProperties;

    tb::Sprite m_sprite;

    tb::ObjectType m_objectType = tb::ObjectType::Null;

    uint32_t m_count = 1;

    sf::Clock m_decayClock;
    sf::Clock m_regenerateClock;

};

}
