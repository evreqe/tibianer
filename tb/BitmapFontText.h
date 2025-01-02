#pragma once

#include "common.h"

#include "tb/Log.h"

#include "tb/BitmapFont.h"

namespace tb
{

class BitmapFontText : public sf::Drawable, public sf::Transformable
{

public:

    BitmapFontText();
    ~BitmapFontText();

    struct TextLine_t
    {
        std::uint32_t Index = 0;
        std::string Text;
        sf::FloatRect Rect;
        std::vector<sf::Vertex*> VertexPointerList;
    };

    bool setText(tb::BitmapFont* bitmapFont, const std::string& text, const sf::Color& color);

    tb::BitmapFont* getBitmapFont();

    std::vector<sf::Vertex>* getVertexList();

    sf::FloatRect getRect();

    std::string* getText();

    sf::Color getColor();

    std::int32_t getPaddingY();
    void setPaddingY(std::int32_t paddingY);

    tb::TextJustifyType getTextJustifyType();
    void setTextJustifyType(tb::TextJustifyType textJustifyType);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

    tb::BitmapFont* m_bitmapFont = nullptr;

    std::vector<sf::Vertex> m_vertexList;

    static const std::uint32_t m_numVertexPerGlyph = 6;

    sf::FloatRect m_rect;

    std::string m_text;

    sf::Color m_color;

    std::int32_t m_paddingY = 1;

    tb::TextJustifyType m_textJustifyType = tb::TextJustifyType::Left;

    std::vector<tb::BitmapFontText::TextLine_t> m_textLineList;

    const std::uint32_t m_numTextLinesToReserve = 8;

};

}
