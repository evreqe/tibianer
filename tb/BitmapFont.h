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

    bool load(const std::string& fileName, const sf::Vector2u& glyphSize, const float textHeight, const std::vector<unsigned int>* glyphWidthList, unsigned int glyphSpace = 0);

    sf::VertexArray* getVertexArray();
    sf::Texture* getTexture();
    sf::Vector2u getGlyphSize();
    float getTextHeight();
    std::vector<unsigned int>* getGlyphWidthList();
    unsigned int getGlyphSpace();

private:

    sf::VertexArray m_vertexArray;
    sf::Texture m_texture;
    sf::Vector2u m_glyphSize;
    float m_textHeight = 0.0f;
    std::vector<unsigned int> m_glyphWidthList;

    unsigned int m_glyphSpace = 0;

    const unsigned int m_numGlyphs = 96;

};

}
