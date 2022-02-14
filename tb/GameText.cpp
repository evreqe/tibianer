#include "tb/GameText.h"

namespace tb
{

GameText::GameText()
{
    //
}

void GameText::setText(tb::BitmapFont& bitmapFont, sf::Vector2u tileCoords, tb::ZAxis_t z, const std::string& text, sf::Color textColor, bool isCentered)
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

tb::ZAxis_t GameText::getZ()
{
    return m_z;
}

sf::Vector2u GameText::getTilePosition()
{
    return m_tilePosition;
}

std::string GameText::getText()
{
    return m_text;
}

sf::Color* GameText::getTextColor()
{
    return &m_textColor;
}

unsigned int GameText::getNumTextLines()
{
    return m_numTextLines;
}

std::vector<std::string>* GameText::getTextList()
{
    return &m_textList;
}

sf::Clock* GameText::getClock()
{
    return &m_clock;
}

void GameText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_texture;

    for (const auto& bitmapFontText : m_bitmapFontTextList)
    {
        target.draw(bitmapFontText, states);
    }
}

}