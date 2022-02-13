#ifndef TIBIA_LIGHT_HPP
#define TIBIA_LIGHT_HPP

#include <SFML/Graphics.hpp>

#include "tb/Tibia.hpp"
#include "tb/Utility.hpp"

namespace tb
{

class Light : public sf::Sprite
{

public:

    Light::Light()
    {
        setTexture(tb::Textures::lights);

        setSize(0);

        setColor(tb::Colors::light);
    }

    void setSize(unsigned int size)
    {
        if (size > tb::Lights::numLights - 1)
        {
            size = tb::Lights::numLights;
        }

        m_size = size;

        setTextureRect(sf::IntRect(0, size * tb::Lights::size.y, tb::Lights::size.x, tb::Lights::size.y));

        setOrigin(tb::Lights::size.x / 2, tb::Lights::size.y / 2);
    }

    unsigned int getSize()
    {
        return m_size;
    }

    void setColorbyId(unsigned int id)
    {
        auto lightColorIt = tb::UMaps::lightColors.find(id);

        if (lightColorIt != tb::UMaps::lightColors.end())
        {
            setColor(lightColorIt->second);
        }
        else
        {
            setColor(tb::Colors::light);
        }
    }

private:

    unsigned int m_size;

}; // class Light

} // namespace tb

#endif // TIBIA_LIGHT_HPP
