#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/Log.h"

#include "tb/BitmapFont.h"

namespace tb
{

class BitmapFontText : public sf::Drawable, public sf::Transformable
{

public:

    BitmapFontText();
    ~BitmapFontText();

    bool setText(tb::BitmapFont* bitmapFont, const std::string& text, const sf::Color& textColor, bool isCentered = false);

    sf::VertexArray* getVertexArray();

    tb::BitmapFont* getBitmapFont();

private:

    sf::VertexArray m_vertexArray;

    tb::BitmapFont* m_bitmapFont = nullptr;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}
