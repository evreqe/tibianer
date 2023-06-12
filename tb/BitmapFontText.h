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

    bool setText(tb::BitmapFont* bitmapFont, const std::string& text, const sf::Color& color);

    tb::BitmapFont* getBitmapFont();

    std::vector<sf::Vertex>* getVertexList();

    sf::FloatRect getRect();

    std::string* getText();

    sf::Color getColor();

    int getPaddingY();
    void setPaddingY(int paddingY);

private:

    tb::BitmapFont* m_bitmapFont = nullptr;

    std::vector<sf::Vertex> m_vertexList;

    sf::FloatRect m_rect;

    std::string m_text;

    sf::Color m_color;

    int m_paddingY = 1;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}
