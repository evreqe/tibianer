#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

namespace tb
{

class BitmapFont
{

public:

    BitmapFont();

    bool load(const std::string& texture, sf::Vector2u glyphSize, const std::vector<unsigned int>* glyphWidthList, unsigned int glyphSpace = 0);

    sf::VertexArray* getVertexArray();
    sf::Texture* getTexture();
    sf::Vector2u* getGlyphSize();
    std::vector<unsigned int>* getGlyphWidthList();
    unsigned int getGlyphSpace();

private:

    sf::VertexArray m_vertexArray;
    sf::Texture m_texture;
    sf::Vector2u m_glyphSize;
    std::vector<unsigned int> m_glyphWidthList;

    unsigned int m_numGlyphs = 96;

    unsigned int m_glyphSpace = 0;

};

}
