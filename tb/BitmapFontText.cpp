#include "tb/BitmapFontText.h"

namespace tb
{

BitmapFontText::BitmapFontText()
{
    //
}

BitmapFontText::~BitmapFontText()
{
    //
}

bool BitmapFontText::setText(tb::BitmapFont* bitmapFont, const std::string& text, const sf::Color& color)
{
    if (bitmapFont == nullptr)
    {
        g_Log.write("ERROR: bitmapFont == nullptr\n");
        return false;
    }

    m_bitmapFont = bitmapFont;

    m_text = text;

    m_color = color;

    m_vertexList.clear();
    m_vertexList.reserve(text.size() * 4);

    m_textLineList.clear();
    m_textLineList.reserve(m_numTextLinesToReserve);

    const std::uint32_t numGlyphs = tb::Constants::BitmapFonts::NumGlyphs;

    const std::uint32_t textureSizeX = bitmapFont->getTexture()->getSize().x;

    const std::uint32_t glyphSizeX = bitmapFont->getGlyphSize().x;
    const std::uint32_t glyphSizeY = bitmapFont->getGlyphSize().y;

    const std::int32_t characterSpace = bitmapFont->getCharacterSpace();
    const std::int32_t characterHeight = bitmapFont->getCharacterHeight();

    std::uint32_t textX = 0;
    std::uint32_t textY = 0;

    std::uint32_t textXMax = 0;
    std::uint32_t textYMax = 0;

    std::int32_t lineHeight = characterHeight + m_paddingY;

    std::uint32_t lineIndex = 0;
    std::string lineText = "";
    std::vector<sf::Vertex*> lineVertexPointerList;
    lineVertexPointerList.reserve(text.size() * 4);

    for (std::size_t i = 0; i < text.size(); i++)
    {
        char character = text[i];

        // new line
        if (character == '\n')
        {
            tb::BitmapFontText::TextLine_t textLine;
            textLine.Index = lineIndex;
            textLine.Text = lineText;
            textLine.Rect.left = 0.0f;
            textLine.Rect.top = static_cast<float>(textY);
            textLine.Rect.width = static_cast<float>(textX);
            textLine.Rect.height = static_cast<float>(lineHeight);
            textLine.VertexPointerList = lineVertexPointerList;
            m_textLineList.push_back(textLine);

            lineText = "";
            lineVertexPointerList.clear();

            textX = 0;
            textY += lineHeight;

            if (textYMax < textY)
            {
                textYMax = textY;
            }

            continue;
        }
        else
        {
            lineIndex++;
            lineText.push_back(character);
        }

        const std::uint32_t asciiValue = static_cast<unsigned char>(text[i]);

        // skip unused characters
        if (asciiValue >= numGlyphs)
        {
            continue;
        }

        const std::uint32_t u = asciiValue % (textureSizeX / glyphSizeX);
        const std::uint32_t v = asciiValue / (textureSizeX / glyphSizeX);

        sf::Vertex vertex[4];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY));
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY));
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY + glyphSizeY));
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY + glyphSizeY));

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, v       * glyphSizeY));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, v       * glyphSizeY));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, (v + 1) * glyphSizeY));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, (v + 1) * glyphSizeY));

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;

        m_vertexList.push_back(vertex[0]);
        m_vertexList.push_back(vertex[1]);
        m_vertexList.push_back(vertex[2]);
        m_vertexList.push_back(vertex[3]);

        lineVertexPointerList.push_back(&m_vertexList.back() - 3);
        lineVertexPointerList.push_back(&m_vertexList.back() - 2);
        lineVertexPointerList.push_back(&m_vertexList.back() - 1);
        lineVertexPointerList.push_back(&m_vertexList.back());

        const std::int32_t characterWidth = bitmapFont->getCharacterWidthList()->at(asciiValue);

        textX += characterWidth + characterSpace;

        if (textXMax < textX)
        {
            textXMax = textX;
        }
    }

    const float textWidth  = static_cast<float>(textXMax);
    const float textHeight = static_cast<float>(textYMax);

    sf::Vector2f position = getPosition();

    m_rect.left   = position.x;
    m_rect.top    = position.y;
    m_rect.width  = textWidth;
    m_rect.height = textHeight;

    // text alignment
    for (auto& textLine : m_textLineList)
    {
        float offsetX = 0.0f;

        if (m_textJustifyType == tb::TextJustifyType::Center)
        {
            offsetX = m_rect.left + ((m_rect.width - textLine.Rect.width) / 2.0f);
        }
        else if (m_textJustifyType == tb::TextJustifyType::Right)
        {
            offsetX = m_rect.left + m_rect.width - textLine.Rect.width;
        }

        for (auto& vertexPointer : textLine.VertexPointerList)
        {
            vertexPointer->position.x += offsetX;
        }
    }

    return true;
}

tb::BitmapFont* BitmapFontText::getBitmapFont()
{
    return m_bitmapFont;
}

std::vector<sf::Vertex>* BitmapFontText::getVertexList()
{
    return &m_vertexList;
}

sf::FloatRect BitmapFontText::getRect()
{
    return m_rect;
}

std::string* BitmapFontText::getText()
{
    return &m_text;
}

sf::Color BitmapFontText::getColor()
{
    return m_color;
}

std::int32_t BitmapFontText::getPaddingY()
{
    return m_paddingY;
}

void BitmapFontText::setPaddingY(std::int32_t paddingY)
{
    m_paddingY = paddingY;
}

tb::TextJustifyType BitmapFontText::getTextJustifyType()
{
    return m_textJustifyType;
}

void BitmapFontText::setTextJustifyType(tb::TextJustifyType textJustifyType)
{
    m_textJustifyType = textJustifyType;
}

void BitmapFontText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_bitmapFont->getTexture();

    target.draw(&m_vertexList[0], m_vertexList.size(), sf::Quads, states);
}

}
