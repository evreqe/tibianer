#include "common.h"

#include "tb/Animation.h"

namespace tb
{

Animation::Animation() :
    m_sprite(tb::Resources::Textures::SpriteSheet)
{
    setThingType(tb::ThingType::Animation);
}

Animation::~Animation()
{
    //
}

Animation::Animation(const sf::Vector2i& tileCoords, tb::ZAxis z, std::uint32_t index) :
    m_sprite(tb::Resources::Textures::SpriteSheet)
{
    setThingType(tb::ThingType::Animation);

    setTileCoords(tileCoords);
    setZ(z);

    m_animationData = g_AnimationData.getDataByIndex(index);

    initalize();
}

Animation::Animation(const sf::Vector2i& tileCoords, tb::ZAxis z, const std::string& name) :
    m_sprite(tb::Resources::Textures::SpriteSheet)
{
    setThingType(tb::ThingType::Animation);

    setTileCoords(tileCoords);
    setZ(z);

    m_animationData = g_AnimationData.getDataByName(name);

    initalize();
}

void Animation::initalize()
{
    if (m_animationData == nullptr)
    {
        throw std::runtime_error("m_animationData == nullptr");
    }

    m_spriteIDList = &m_animationData->SpriteIDList;

    if (m_spriteIDList == nullptr)
    {
        throw std::runtime_error("m_spriteIDList == nullptr");
    }

    if (m_spriteIDList->size() == 0)
    {
        throw std::runtime_error("m_spriteIDList->size() == 0");
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

        tb::SpriteID spriteID = m_spriteIDList->at(m_currentFrame);

        m_sprite.setID(spriteID);

        m_clock.restart();
    }
}

tb::Sprite* Animation::getSprite()
{
    return &m_sprite;
}

tb::SpriteID Animation::getSpriteID()
{
    return m_sprite.getID();
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
