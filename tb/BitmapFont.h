#pragma once

#include "common.h"

#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class BitmapFont
{

public:

    BitmapFont();
    ~BitmapFont();

    bool load(const std::string& fileName, const sf::Vector2u& glyphSize, int characterSpace, int characterHeight, std::vector<int>* characterWidthList);

    sf::VertexArray* getVertexArray();
    sf::Texture* getTexture();
    sf::Vector2u getGlyphSize();
    int getCharacterSpace();
    int getCharacterHeight();
    std::vector<int>* getCharacterWidthList();

private:

    sf::VertexArray m_vertexArray;
    sf::Texture m_texture;
    sf::Vector2u m_glyphSize;
    int m_characterSpace = 0;
    int m_characterHeight = 1;
    std::vector<int> m_characterWidthList;

    const unsigned int m_numGlyphs = 96;

};

}
