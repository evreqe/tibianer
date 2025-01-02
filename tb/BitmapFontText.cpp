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

    const std::uint32_t numVertices = static_cast<std::uint32_t>(text.size() * m_numVertexPerGlyph);

    m_vertexList.clear();
    m_vertexList.reserve(numVertices);

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
    lineVertexPointerList.reserve(text.size() * m_numTextLinesToReserve);

    for (std::size_t i = 0; i < text.size(); i++)
    {
        char character = text[i];

        // new line
        if (character == '\n')
        {
            tb::BitmapFontText::TextLine_t textLine;
            textLine.Index = lineIndex;
            textLine.Text = lineText;
            textLine.Rect.position.x = 0.0f;
            textLine.Rect.position.y = static_cast<float>(textY);
            textLine.Rect.size.x = static_cast<float>(textX);
            textLine.Rect.size.y = static_cast<float>(lineHeight);
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

        const std::uint32_t textU = asciiValue % (textureSizeX / glyphSizeX);
        const std::uint32_t textV = asciiValue / (textureSizeX / glyphSizeX);

        sf::Vertex vertex[m_numVertexPerGlyph];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY));
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY));
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY + glyphSizeY));
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY + glyphSizeY));
        vertex[4].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY));
        vertex[5].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY + glyphSizeY));

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(textU       * glyphSizeX, textV       * glyphSizeY));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((textU + 1) * glyphSizeX, textV       * glyphSizeY));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(textU       * glyphSizeX, (textV + 1) * glyphSizeY));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(textU       * glyphSizeX, (textV + 1) * glyphSizeY));
        vertex[4].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((textU + 1) * glyphSizeX, textV       * glyphSizeY));
        vertex[5].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((textU + 1) * glyphSizeX, (textV + 1) * glyphSizeY));

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;
        vertex[4].color = color;
        vertex[5].color = color;

        m_vertexList.push_back(vertex[0]);
        m_vertexList.push_back(vertex[1]);
        m_vertexList.push_back(vertex[2]);
        m_vertexList.push_back(vertex[3]);
        m_vertexList.push_back(vertex[4]);
        m_vertexList.push_back(vertex[5]);

        lineVertexPointerList.push_back(&m_vertexList.back() - 5);
        lineVertexPointerList.push_back(&m_vertexList.back() - 4);
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

    m_rect.position = getPosition();

    m_rect.size.x = textWidth;
    m_rect.size.y = textHeight;

    // text alignment
    for (auto& textLine : m_textLineList)
    {
        float offsetX = 0.0f;

        if (m_textJustifyType == tb::TextJustifyType::Center)
        {
            offsetX = m_rect.position.x + ((m_rect.size.x - textLine.Rect.size.x) / 2.0f);
        }
        else if (m_textJustifyType == tb::TextJustifyType::Right)
        {
            offsetX = m_rect.position.x + m_rect.size.x - textLine.Rect.size.x;
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

    target.draw(&m_vertexList[0], m_vertexList.size(), sf::PrimitiveType::Triangles, states);
}

}
