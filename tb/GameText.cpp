#include "tb/GameText.h"

namespace tb
{

GameText::GameText()
{
    //
}

GameText::~GameText()
{
    //
}

bool GameText::setText(tb::BitmapFont* bitmapFont, const sf::Vector2u& tileCoords, tb::ZAxis_t z, const std::string& text, const sf::Color& textColor, bool isCentered)
{
    if (bitmapFont == nullptr)
    {
        g_Log.write("ERROR: nullptr\n");
        return false;
    }

    m_texture = bitmapFont->getTexture();

    m_tileCoords = tileCoords;

    m_z = z;

    m_text = text;

    m_textColor = textColor;

    m_textList.clear();

    boost::split(m_textList, text, boost::is_any_of("\n"));

    sf::Vector2f textPosition = static_cast<sf::Vector2f>(tileCoords);

    const unsigned int textHeight = bitmapFont->getGlyphSize().y;

    m_bitmapFontTextList.clear();
    m_bitmapFontTextList.reserve(m_textList.size());

    for (auto& textValue : m_textList)
    {
        tb::BitmapFontText bitmapFontText;

        bitmapFontText.setText(bitmapFont, textValue, textColor, isCentered);

        bitmapFontText.setPosition(textPosition);

        textPosition.y = textPosition.y + (static_cast<float>(textHeight) + 1.0f);

        m_bitmapFontTextList.push_back(bitmapFontText);
    }

    return true;
}

sf::Vector2u GameText::getTileCoords()
{
    return m_tileCoords;
}

tb::ZAxis_t GameText::getZ()
{
    return m_z;
}

std::string GameText::getText()
{
    return m_text;
}

sf::Color* GameText::getTextColor()
{
    return &m_textColor;
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