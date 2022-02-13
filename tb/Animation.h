#ifndef TIBIA_ANIMATION_HPP
#define TIBIA_ANIMATION_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "tb/Tibia.hpp"
#include "tb/Thing.hpp"
#include "tb/Sprite.hpp"

namespace tb
{

class Animation : public tb::Thing
{

public:

    typedef std::shared_ptr<tb::Animation> Ptr;
    typedef std::vector<tb::Animation::Ptr> List;

    Animation::Animation(int tileX, int tileY, int z, int id, int numFrames)
    {
        setTileCoords(tileX, tileY);
        setPosition(sf::Vector2f(tileX, tileY));

        setZ(z);

        setId(id);

        setNumFrames(numFrames);

        setFrameTime(tb::AnimationTimes::default);

        m_clock.restart();
    }

    void setId(int id)
    {
        m_id = id;

        m_sprite.setId(m_id);

        m_flags = tb::UMaps::spriteFlags[m_id];

        m_numRepeat = 0;

        if
        (
            id == tb::Animations::fire[0]        ||
            id == tb::Animations::electricity[0]
        )
        {
            setNumRepeat(1);
        }
    }

    int getId()
    {
        return m_id;
    }

     tb::SpriteFlags_t getFlags()
    {
        return m_flags;
    }

    void setFlags( tb::SpriteFlags_t flags)
    {
        m_flags = flags;
    }

    void setNumFrames(int numFrames)
    {
        m_numFrames = numFrames;

        m_currentFrame = 0;
    }

    int getNumFrames()
    {
        return m_numFrames;
    }

    void advanceFrame()
    {
        sf::Time timeElapsed = m_clock.getElapsedTime();

        if (timeElapsed.asSeconds() >= m_frameTime)
        {
            m_currentFrame++;

            if (m_currentFrame > m_numFrames - 1)
            {
                if (m_numRepeat > 0)
                {
                    m_currentFrame = 0;

                    m_numRepeat--;
                }
                else
                {
                    setIsReadyForErase(true);
                    return;
                }
            }

            m_sprite.setId(m_id + m_currentFrame);

            m_clock.restart();
        }
    }

    int getCurrentFrame()
    {
        return m_currentFrame;
    }

    void setNumRepeat(int numRepeat)
    {
        m_numRepeat = numRepeat;
    }

    int getNumRepeat()
    {
        return m_numRepeat;
    }

    void setFrameTime(float time)
    {
        m_frameTime = time;
    }

    float getFrameTime()
    {
        return m_frameTime;
    }

    void update()
    {
        updateTileCoords();

        int drawOffset = getDrawOffset() * tb::THING_DRAW_OFFSET;

        setPosition(getTileX() - drawOffset, getTileY() - drawOffset);

        advanceFrame();
    }

private:

    int m_id;

    tb::SpriteFlags_t m_flags;

    tb::Sprite m_sprite;

    int m_numFrames;

    int m_currentFrame;

    float m_frameTime;

    int m_numRepeat;

    sf::Clock m_clock;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(m_sprite, states);
    }

}; // class Animation

} // namespace tb

#endif // TIBIA_ANIMATION_HPP
