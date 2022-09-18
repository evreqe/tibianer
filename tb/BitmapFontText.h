#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/BitmapFont.h"

namespace tb
{

class BitmapFontText : public sf::Drawable, public sf::Transformable
{

public:

    BitmapFontText();
    ~BitmapFontText();

    void setText(tb::BitmapFont* bf, std::string text, sf::Color textColor, bool isCentered = false);

    sf::VertexArray* getVertexArray();

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertexArray;

    tb::BitmapFont* m_bitmapFont = nullptr;

};

}
