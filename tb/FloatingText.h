#pragma once

/*
#ifndef TIBIA_FLOATINGTEXT_HPP
#define TIBIA_FLOATINGTEXT_HPP

#include <vector>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "tb/Tibia.hpp"
#include "tb/Utility.hpp"
#include "tb/BitmapFont.hpp"
#include "tb/BitmapFontText.hpp"
#include "tb/DrawableAndTransformable.hpp"

namespace tb
{

class FloatingText : public tb::DrawableAndTransformable
{

public:

    void setText(tb::BitmapFont& bitmapFont, sf::Vector2u tileCoords, int z, std::string text, sf::Color textColor)
    {
        m_texture = bitmapFont.getTexture();

        m_z = z;

        m_textPosition = static_cast<sf::Vector2f>(tileCoords);

        m_textPosition.x += tb::TILE_SIZE / 2;
        //m_textPosition.y += tb::TILE_SIZE / 2;

        m_bitmapFontText.setText(&bitmapFont, text, textColor, true);
        m_bitmapFontText.setPosition(m_textPosition);
    }

    int getZ()
    {
        return m_z;
    }

    void update(sf::Time timeDelta)
    {
        if (m_distanceMoved < (tb::TILE_SIZE * 2))
        {
            float startY = m_textPosition.y;

            m_textPosition.y -= (tb::FloatingTextData::speed / 2.0f) * timeDelta.asSeconds();

            m_distanceMoved += startY - m_textPosition.y;

            //std::cout << "distance moved: " << m_distanceMoved << std::endl;
        }

        m_bitmapFontText.setPosition(m_textPosition);
    }

    sf::Clock* getClock()
    {
        return &m_clock;
    }

private:

    sf::Texture* m_texture;

    int m_z;

    tb::BitmapFontText m_bitmapFontText;

    sf::Vector2f m_textPosition;

    sf::Clock m_clock;

    float m_distanceMoved = 0.0f;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = m_texture;

        target.draw(m_bitmapFontText, states);
    }

}; // class FloatingText

} // namespace tb

#endif // TIBIA_FLOATINGTEXT_HPP
*/