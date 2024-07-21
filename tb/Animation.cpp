#include "tb/Animation.h"

namespace tb
{

Animation::Animation()
{
    setThingType(tb::ThingType::Animation);
}

Animation::~Animation()
{
    //
}

Animation::Animation(const sf::Vector2i& tileCoords, tb::ZAxis_t z, std::uint32_t index)
{
    setThingType(tb::ThingType::Animation);

    setTileCoords(tileCoords);
    setZ(z);

    m_animationData = g_AnimationData.getDataByIndex(index);

    if (m_animationData == nullptr)
    {
        g_Log.write("ERROR: m_animationData == nullptr\n");
    }

    initalize();
}

Animation::Animation(const sf::Vector2i& tileCoords, tb::ZAxis_t z, const std::string& name)
{
    setThingType(tb::ThingType::Animation);

    setTileCoords(tileCoords);
    setZ(z);

    m_animationData = g_AnimationData.getDataByName(name);

    if (m_animationData == nullptr)
    {
        g_Log.write("ERROR: m_animationData == nullptr\n");
    }

    initalize();
}

void Animation::initalize()
{
    m_spriteIDList = &m_animationData->SpriteIDList;

    if (m_spriteIDList == nullptr)
    {
        g_Log.write("ERROR: m_spriteIDList == nullptr\n");
    }

    if (m_spriteIDList->size() == 0)
    {
        g_Log.write("ERROR: m_spriteIDList is empty\n");
    }

    m_sprite.setID(m_spriteIDList->at(0));

    m_currentFrame = 0;

    m_clock.restart();

    update();
}

void Animation::update()
{
    sf::Vector2f pixelCoords = getPixelCoords();

    m_sprite.setPosition(pixelCoords);

    advanceFrame();
}

void Animation::advanceFrame()
{
    tb::Thing::ThingProperties_t* thingProperties = getThingProperties();

    if (thingProperties->Erase == true)
    {
        return;
    }

    sf::Time timeElapsed = m_clock.getElapsedTime();

    if (timeElapsed >= m_frameTime)
    {
        m_currentFrame++;

        if (m_currentFrame >= m_spriteIDList->size())
        {
            m_currentFrame = 0;

            if (m_numRepeat > 0)
            {
                m_numRepeat--;
            }
            else
            {
                thingProperties->Erase = true;
                return;
            }
        }

        m_sprite.setID(m_spriteIDList->at(m_currentFrame));

        m_clock.restart();
    }
}

tb::Sprite* Animation::getSprite()
{
    return &m_sprite;
}

tb::AnimationData::Data* Animation::getData()
{
    return m_animationData;
}

tb::SpriteIDList* Animation::getSpriteIDList()
{
    return m_spriteIDList;
}

sf::Clock* Animation::getClock()
{
    return &m_clock;
}

}
