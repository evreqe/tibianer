#pragma once

#include <vector>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"
#include "tb/BitmapFont.hpp"
#include "tb/BitmapFontText.hpp"

namespace tb
{

class GameText : public sf::Drawable, public sf::Transformable
{

public:

    void setText(tb::BitmapFont& bitmapFont, sf::Vector2u tileCoords, tb::ZAxis_t z, const std::string& text, sf::Color textColor, bool isCentered = true)
    {
        m_texture = bitmapFont.getTexture();

        m_tilePosition = tileCoords;

        m_z = z;

        m_text = text;

        m_textColor = textColor;

        m_numTextLines = 0;

        m_textList.clear();

        boost::split(m_textList, text, boost::is_any_of("\n"));

        m_numTextLines = m_textList.size();

        sf::Vector2f textPosition = static_cast<sf::Vector2f>(tileCoords);

        const unsigned int textHeight = bitmapFont.getGlyphSize()->y;

        m_bitmapFontTextList.clear();

        for (auto& textValue : m_textList)
        {
            tb::BitmapFontText bitmapFontText;

            bitmapFontText.setText(&bitmapFont, textValue, textColor, isCentered);

            bitmapFontText.setPosition(textPosition);

            textPosition.y = textPosition.y + static_cast<float>(textHeight) + 1;

            m_bitmapFontTextList.push_back(bitmapFontText);
        }
    }

    tb::ZAxis_t getZ() const
    {
        return m_z;
    }

    sf::Vector2u getTilePosition() const
    {
        return m_tilePosition;
    }

    std::string getText() const
    {
        return m_text;
    }

    sf::Color* getTextColor()
    {
        return &m_textColor;
    }

    unsigned int getNumTextLines() const
    {
        return m_numTextLines;
    }

    std::vector<std::string>* getTextList()
    {
        return &m_textList;
    }

    sf::Clock* getClock()
    {
        return &m_clock;
    }

private:

    sf::Texture* m_texture = nullptr;

    sf::Vector2u m_tilePosition;

    std::string m_text;

    sf::Color m_textColor;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    int m_type = 0; // ?

    unsigned int m_numTextLines = 0;

    std::vector<std::string> m_textList;

    std::vector<tb::BitmapFontText> m_bitmapFontTextList;

    sf::Clock m_clock;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();

        states.texture = m_texture;

        for (const auto& bitmapFontText : m_bitmapFontTextList)
        {
            target.draw(bitmapFontText, states);
        }
    }

};

}